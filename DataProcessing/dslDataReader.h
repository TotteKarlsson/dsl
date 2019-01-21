#ifndef dslDataReaderH
#define dslDataReaderH
#include "dslData.h"
#include "DataExporter.h"

namespace dsl
{

template <class T>
class mtkDataReader : public DSLObject
{
    public:
                                mtkDataReader(mtkData<T> *mtkData);
                                mtkDataReader(mtkData<T>& mtkData);
                               ~mtkDataReader();
        bool                    Read(const File& file);
        virtual bool            Read(const string& fileName, const DATA_FORMAT& format = dfMoleculix, const FILE_FORMAT& fType = ffASCII);
        bool                    Reload();
        void                    AssignData(mtkData<T> *data){mData = data;}

    protected:
        mtkData<T>*             mData;
        bool                    mtkFormat(fstream& inF,             const FILE_FORMAT& = ffASCII);
        bool                    mtkDouble(fstream& inF,             const FILE_FORMAT& = ffASCII);
        bool                    mtkComplex(fstream& inF,            const FILE_FORMAT& = ffASCII);
        bool                    ReadMTKHeader(fstream& inF,         const FILE_FORMAT&);
        bool                    ReadMTKFooter(fstream& inF,         const FILE_FORMAT&);
        bool                    ReadMTKRowAxis(fstream& inF,        const FILE_FORMAT&);
        bool                    ReadMTKColAxis(fstream& inF,        const FILE_FORMAT&);
        bool                    ReadMTKFormattedData(fstream& inF,  const FILE_FORMAT&);
        bool                    ReadMTKFormattedData(fstream& inF,  const FILE_FORMAT&, const DATA_FORMAT& format);

        bool                    GetMTKHeader(fstream& inF, string& header, const FILE_FORMAT& fType);
        DATA_FORMAT             GetDataFormat(fstream& inF, const FILE_FORMAT& fType);
        bool                    ProcessMTKHeader(string& str, int& rSize, int& cSize, DATA_FORMAT& dFormat);
};

typedef mtkDataReader< complex<double> > mtkComplexDataReader;

template <class T>
mtkDataReader<T>::mtkDataReader(mtkData<T> *data)
:
mData(data)
{}

template <class T>
mtkDataReader<T>::mtkDataReader(mtkData<T> &data)
:
mData(&data)
{}

template <class T>
mtkDataReader<T>::~mtkDataReader()
{ }

template <class T>
bool mtkDataReader<T>::Read(const File& file)
{
    return Read(file.GetNameAndPath());
}

template <class T>
bool mtkDataReader<T>::Read(const string& fileNS, const DATA_FORMAT& dFormat, const FILE_FORMAT& fFormat)
{
    if(fileNS.size() > 1)
    {
        mData->GetFile()->SetFileName(fileNS);
    }

    bool fExists = dsl::fileExists(mData->GetFile());
    bool readSuccess;
    if(!fExists)
    {
        return false;
    }

    //If the file is open, close it
    if(mData->GetFile()->IsOpen())
    {
        mData->GetFile()->Close();
    }

    switch(dFormat)
    {
        case dfUnknown://try all
//        case dfDouble:
//        case mtkIMAGINARY:
        case dfComplex:
        case dfMoleculix:
            if(mData->GetFile()->Open(fFormat))
            {
                readSuccess =  mtkFormat(mData->GetFile()->Stream(), fFormat);
                mData->GetFile()->Close();
            }
            else
            {
                readSuccess = false;
            }
        break;

        default:
            readSuccess = false;
        break;
    }
    return readSuccess;
}

template <class T>
bool mtkDataReader<T>::mtkFormat(fstream& inF, const  FILE_FORMAT& fFormat)
{
  //mtkFormat has the subformats dfDouble, mtkINTEGER and dfComplex

    if(!inF)
    {
        return false;
    }
   /*** Check subDataformat on first line***/
    if(!ReadMTKHeader(inF, fFormat))
    {
        return false;
    }

    if(!ReadMTKRowAxis(inF, fFormat))
    {
        return false;
    }
    switch(mData->GetDataFormat())
    {
        case dfDouble:     return mtkDouble(inF, fFormat);
        case dfComplex:    return mtkComplex(inF, fFormat);
    }

    return false;
}

template <class T>
bool mtkDataReader<T>::ReadMTKHeader(fstream& inF, const FILE_FORMAT& fFormat)
{
    if(!inF)
    {
        return false;
    }

    int cSize, rSize;
    string headerS;
    DATA_FORMAT   dFormat;
    if(!GetMTKHeader(inF, headerS, fFormat))
    {
        return false;
    }

    if(!ProcessMTKHeader(headerS, rSize, cSize, dFormat))
    {
      return false;
    }
    mData->SetDataFormat(dFormat);

    if(!mData->Resize(rSize, cSize))
    {
      return false;
    }
    return true;
}

template <class T>
bool mtkDataReader<T>::GetMTKHeader(fstream& inF, string& headerS, const FILE_FORMAT& fFormat)
{
    if(!inF)
    {
        return false;
    }
    int  bufSize = 50;
    char *trash = new char[bufSize];
    switch(fFormat)
    {
        case ffASCII:
            inF.getline(trash, bufSize);
            headerS = trash;
            delete [] trash;
        return true;

        case ffBINARY:
        try
        {
            char ch = 's';
            while(ch)
            {
                inF.read((char *) &ch, 1);
                if(ch != '\0')
                {
                    headerS += ch;
                }
                if(inF.eof())
                {
                    break;
                }
            }
            if(headerS.empty())
            {
                throw(dsl::DSLException("Could not read mtkHeader"));
            }
        }
        catch(...)
        {
            //LogMessage(e.msg());
            return false;
        }
        //catch(...)
        //{
        //    return false;
        //}
      return true;
    }

  return false;
}

template <class T>
bool mtkDataReader<T>::ProcessMTKHeader(string& str, int& rSize, int& cSize, DATA_FORMAT& dFormat)
{
    rSize = atoi(str.c_str());
    str = str.erase(0, str.find_first_of('x')+1);
    cSize = atoi(str.c_str());
    int mtkStart = str.find("mtk");
    if(mtkStart < 0)
    {
        return false;
    }

    str = str.erase(0, mtkStart);
    dFormat = strToDataFormat(str);
    if(dFormat == dfUnknown)
    {
        return false;
    }
    return true;
}

template <class T>
bool mtkDataReader<T>::ReadMTKRowAxis(fstream& inF, const FILE_FORMAT& fileFormat)
{
      /*** Second row is the Row Axes ***/
      if(!inF)
      {
          return false;
    }

    double val = 0;
    switch(fileFormat)
    {
        case ffASCII:
            for(int row = 1; row < mData->RSize() + 1; row++)
            {
                  inF>>val;
                  mData->GetRowAxis()->SetElement(row) = val;
            }
              mData->GetRowAxis()->Update();
      return true;

      case ffBINARY:
          for(int row = 1; row < mData->RSize() + 1; row++)
        {
              inF.read((char *) &(val), sizeof(val));
              mData->GetRowAxis()->SetElement(row) = val;
        }
        mData->GetRowAxis()->Update();
      return true;
    }

    return false;
}

template <class T>
bool mtkDataReader<T>::ReadMTKFooter(fstream& inF, const FILE_FORMAT&)
{
      if(inF)
      {
        return true;
      }
      return false;
}

template <class T>
DATA_FORMAT   mtkDataReader<T>::GetDataFormat(fstream& inF, const FILE_FORMAT& fFormat)
{
    if(inF)
    {
        string str = GetMTKHeader(inF, fFormat);
        str = str.erase(0,str.find_first_of('m'));
        return dfNone; //TODO: fix mtkStringToDataFormat(str);
      }
      return dfUnknown;
}


template <class T>
bool mtkDataReader<T>::Reload()
{
    string fName = mData->GetFile()->GetNameAndPath();
    return (mData)? Read(fName) : false;
}

template<class T>
bool mtkDataReader<T>::mtkDouble(fstream& inF, const FILE_FORMAT& fFormat)
{
    if(inF)
    {
        if(!ReadMTKFormattedData(inF, fFormat))
        {
            return false;
        }
        if(!ReadMTKFooter(inF, fFormat))
        {
            return false;
        }
        //We have succesfully read the data
        mData->GetRowAxis()->Update();
        mData->GetColAxis()->Update();
        return true;
    }
    return false;
}

template<class T>
bool mtkDataReader<T>::mtkComplex(fstream& /*inF*/, const FILE_FORMAT& /*fFormat*/)
{
    return false;
}

template<> inline
bool mtkDataReader< complex<double> >::mtkComplex(fstream& inF, const  FILE_FORMAT& fFormat)
{
    if(inF)
      {
        if(!ReadMTKFormattedData(inF, fFormat))
        {
            return false;
        }
        if(!ReadMTKFooter(inF, fFormat))
        {
            return false;
        }
        //We have succesfully read the data
        mData->GetRowAxis()->Update();
        mData->GetColAxis()->Update();
        return true;
      }
      return false;
}

template <class T>
bool mtkDataReader<T>::ReadMTKFormattedData(fstream& inF, const FILE_FORMAT& type)
{
    if(!inF)
    {
        return false;
    }

    double val = 0;
    switch(type)
    {
        case ffASCII:
            for(int col = 1; col < mData->CSize() + 1; col++)
            {
                  (inF)>> val;
                  mData->GetColAxis()->SetElement(col) = val;
                  for(int row = 1; row < mData->RSize() + 1; row++)
                  {
                    inF>>mData->mTheData(row,col);
                }
            }
          return true;

        case ffBINARY:
            for(int col = 1; col < mData->CSize() + 1; col++)
            {
                  inF.read((char *) &val, sizeof(val));
                  mData->GetColAxis()->SetElement(col) = val;
                  for(int row = 1; row < mData->RSize() + 1; row++)
                {
                    T nr;
                    inF.read((char *) &nr, sizeof(nr));
                    mData->mTheData(row,col) = nr;
                  }
            }
          return true;
    }

  return false;
}

template <class T>
bool mtkDataReader< T >::ReadMTKFormattedData(fstream& inF, const FILE_FORMAT& fType, const DATA_FORMAT& subFormat)
{
    double nr = 10;
    inF >> nr;
    if(inF)
      {
        double nr;
        switch(subFormat)
        {
            case dfDouble:
            switch(fType)
            {
                case ffASCII:
                      for(int col = 1; col < mData->CSize() + 1; col++)
                    {
                          inF>>nr;
                          mData->GetColAxis()->SetElement(col) = nr;
                          for(int Row = 1; Row < mData->RSize() + 1; Row++)
                        {
                            inF>>nr;
                            mData->Element(Row,col) = complex<double>(nr,0);
                          }
                    }
                  break;
                  case ffBINARY:
                    for(int col = 1; col < mData->CSize() + 1; col++)
                    {
                          inF.read((char *) &nr, sizeof(nr));
                          mData->GetColAxis()->SetElement(col) = nr;
                          for(int Row = 1; Row < mData->RSize() + 1; Row++)
                        {
                            inF.read((char *) &nr, sizeof(nr));
                            mData->Element(Row,col) = complex<double>(nr,0);
                          }
                    }
              break;
            }
        break;
        }
        mData->SetOriginalDataFormat(subFormat);
         return true;
    }
    return false;
}

//template<> inline
//bool mtkDataReader< complex<double> >::mtkDouble(fstream& inF, const FILE_FORMAT& fFormat)
//{
//    if(inF)
//    {
//        if(!ReadMTKFormattedData(inF, fFormat, dfDouble))
//        {
//            return false;
//        }
//        if(!ReadMTKFooter(inF, fFormat))
//        {
//            return false;
//        }
//        //We have succesfully read the mTheData
//        mData->GetRowAxis()->Update();
//        mData->GetColAxis()->Update();
//
//        return true;
//    }
//    return false;
//}

}
#endif
