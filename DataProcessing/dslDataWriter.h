#ifndef dslDataWriterH
#define dslDataWriterH
#include <string.h>
#include "dslData.h"
#include "DataExporter.h"

namespace dsl
{

template <class T>
class mtkDataWriter : public DSLObject
{
    public:
                                        mtkDataWriter(mtkData<T> *mtkData);
        void                            AssignData(mtkData<T> *data){mData = data;}
        bool                            WriteMTKHeader(fstream& outF, const FILE_FORMAT& type);
        bool                            Write(const string& fileName, const FILE_FORMAT& type = ffASCII, const DATA_FORMAT& format = dfNone);
        bool                            mtkFormat(const string& file, const FILE_FORMAT& type = ffASCII);
//        bool                            mtkDouble(const string& file, const FILE_FORMAT& type = ffASCII);
//        bool                            mtkComplex(const string& file, const FILE_FORMAT& type = ffASCII);
//        bool                            mtkReal(const string& file, const FILE_FORMAT& type = ffASCII);
//        bool                            mtkImaginary(const string& file, const FILE_FORMAT& type = ffASCII);

        /***Projections ***/
        //void                            RowProjectionToFile(const string& file);
        //void                            RowProjectionToFile(int Offset, int Increment, char* file);
        //void                            ColProjectionToFile(const string &file);

        //Rows
        //void                            RowToFile(int row, const char* File);
        //void                            RealRowToFile(int row, const char* File);
        //void                            RowsToFile(const string &filename);
        //void                            RealRowsToFile(const string &fileName);
        //void                            RealRowsToFile(int Offset, int Increment, const char* fileName);
        //void                            RealRowBlockToFile(const int &blocknumber, const char* FileName);
        //void                            RealRowBlockToFile(int first, int last, const char* FileName);

        //Columns
//        void                            ImagRowsToFile(const string& File);
        //void                            ColToFile(int col, const char* File);
        //void                            ColsToFile(const char* FileName);
        //void                            RealColToFile(int col,const char* File);
        //void                            RealColsToFile(const char* File);
        //void                            RealColsToFile(int Offset, int Increment, const char* fileName);

        /***Axes ***/
        //void                            AxesToFile(const char* File);
        //void                            T2AxesToFile(const char* fileName);
        //void                            T1AxesToFile(const char* fileName);
        //void                            IncrementToFile(const char* fileName);
        ////////////////
        //void                            SetOutputType(const FILE_FORMAT& type){SetFileType(type);}
        bool                            WriteAxes(){return writeAxis;}
        void                            WriteAxes(const bool& what){writeAxis = what;}
        string                          GetAsString();
        string                          GetDataHeader();
        string                          GetRowAxesAsString();
        string                          GetFormattedData(const FILE_FORMAT& fFormat = ffASCII);
		
    protected:
        mtkData<T>                        *mData;
        bool                            writeAxis; //have to implement this

        bool                            WriteMTKRowAxis(ostream& outF, const FILE_FORMAT&  type);
        bool                            WriteMTKFormattedData(fstream& outF, const FILE_FORMAT& type);
        bool                            WriteMTKFormattedData(fstream& outF, const DATA_FORMAT& format, const FILE_FORMAT& type);
        bool                            WriteMTKSubFormat(fstream& outF, const DATA_FORMAT& format, const FILE_FORMAT& type);
        bool                            mtkDataSection(fstream& fileS, const FILE_FORMAT& type);

//        bool                            mtkRealDataSection(fstream& fileS, const FILE_FORMAT& type);
//        bool                            mtkImaginaryDataSection(fstream& fileS, const FILE_FORMAT& type);

        bool                            WriteMTKFooter(fstream& outF, const FILE_FORMAT& type);
        //void                            FormatFileName(string fileName);
        string                          GetHeaderA();
        string                          GetHeaderB();
        string                          GetHeaderString();
};

typedef mtkDataWriter< complex<double> >     mtkComplexDataWriter;
//template class mtkDataWriter<double>;
//template class mtkDataWriter< complex<double> >;


//Specialize these
//template<class T> bool mtkDataWriter<T>::mtkComplex(const string& fileN, const FILE_FORMAT& type){return false;}
//template<class T> bool mtkDataWriter<T>::mtkReal(const string& fileN, const FILE_FORMAT& type){return false;}
//template<class T> bool mtkDataWriter<T>::mtkImaginary(const string& fileN, const FILE_FORMAT& type){return false;}

//template <class T>
//bool mtkDataWriter< T >::mtkComplex(const string& fileN, const FILE_FORMAT& type)
//{
//
//      string fileName = (fileN.empty()) ? mData->GetFileName() : fileN;
//
//      fstream *out = OpenFile(fileName.c_str(), type, mtkOut);
//      if(out)
//    {
//        WriteMTKHeader(*out, type);
//        WriteMTKRowAxis(*out, type);
//        WriteMTKFormattedData(*out, type);
//        WriteMTKFooter(*out, type);
//        CloseFile(out);
//        return true;
//      }
//      return false;
//}

template <class T>
bool mtkDataWriter< T >::Write(const string& fileN, const FILE_FORMAT& fformat, const DATA_FORMAT& saveAs)
{
    string fName;
    DATA_FORMAT   dFormat;
    FILE_FORMAT fFormat;

    if(fileN.empty())
    {
        fName = mData->GetFileName();
    }
    else
    {
        fName = fileN;
        mData->SetFileName(fName);
    }

    if(saveAs == dfNone)
    {
        dFormat = mData->GetDataFormat();
    }
    else
    {
        dFormat = saveAs;
        mData->SetDataFormat(dFormat);
    }

    if(fformat == ffUnkown)
    {
        fFormat = mData->GetFileFormat();
    }
    else
    {
        fFormat = fformat;
        mData->SetFileFormat(fFormat);
    }

    switch(dFormat)
    {
        case dfMoleculix:    return mtkFormat(fileN, fFormat);
        //case dfDouble:    return mtkDouble(fileN, fFormat);
        //case dfComplex:   return mtkComplex(fileN, fFormat);
//        case dfDouble:      return mtkReal(fileN, fFormat);
//        case mtkIMAGINARY: return mtkImaginary(fileN, fFormat);
        default:           return false;
    }
}

template <class T>
bool mtkDataWriter< T >::WriteMTKFormattedData(fstream& fileS, const DATA_FORMAT& format, const FILE_FORMAT& type)
{
      //double val;
      //complex<double> nr;
      if(fileS)
    {
        return WriteMTKSubFormat(fileS, format, type);
    }
      return false;
}

template <class T>
mtkDataWriter<T>::mtkDataWriter(mtkData<T> *data) : mData(data)
{
    writeAxis = true;
}

template <class T>
string mtkDataWriter< T >::GetHeaderB()
{
      switch(mData->GetDataFormat())
    {
        case dfMoleculix:
        case dfComplex:    return string(dataFormatToStr(dfComplex));
//        case dfDouble:       return string(DataFormatToStr(dfDouble));
//        case mtkIMAGINARY:  return string(DataFormatToStr(mtkIMAGINARY));
      }
      return string();
}

template <class T>
string mtkDataWriter< T >::GetHeaderString()
{
    return string(GetHeaderA() + GetHeaderB());
}

//template < class T>
//bool mtkDataWriter< T >::mtkDouble(const string& fileName, const FILE_FORMAT& type)
//{
//    return false;
//}

template <class T>
bool mtkDataWriter< T >::mtkFormat(const string& file, const FILE_FORMAT& fFormat)
{
    mData->GetFile()->SetFileName(file);

    if(mData->GetFile()->Open(fFormat, mtkOut))
    {
        if(!WriteMTKHeader(mData->GetFile()->Stream(), fFormat))
        {
            mData->GetFile()->Close();
            return false;
        }
        if(!WriteMTKRowAxis(mData->GetFile()->Stream(), fFormat))
        {
            mData->GetFile()->Close();
            return false;
        }
        if(!WriteMTKFormattedData(mData->GetFile()->Stream(), fFormat))
        {
            mData->GetFile()->Close();
            return false;
        }
        if(!WriteMTKFooter(mData->GetFile()->Stream(), fFormat))
        {
            mData->GetFile()->Close();
            return false;
        }
        if(!mData->GetFile()->Close())
        {
            return false;
        }
        return true; // Everything went OK
    }
    return false;
}

template <class T>
string mtkDataWriter< T >::GetHeaderA()
{
    string str = toString(mData->RSize()).c_str();
    str += "x";
    str += dsl::toString(mData->CSize());
    str += " ";
    return str;
}

template <class T>
string mtkDataWriter<T>::GetAsString()
{
    string data_string;
    //First the header
    data_string = GetDataHeader();

    //then the Row axis 2nd dim axes
    data_string = data_string + '\n' + GetRowAxesAsString();

    //Then the actual data
    data_string = data_string + '\n' + GetFormattedData(ffASCII);
    return data_string;
}

template <class T>
string mtkDataWriter<T>::GetDataHeader()
{
    return GetHeaderString();
}

template <class T>
string mtkDataWriter<T>::GetRowAxesAsString()
{
    string axes;
    axes = "";
    for(int row = 1; row < mData->RSize() + 1; row++)
    {
        axes = axes + "\t" + toString(mData->GetRowAxis()->Element(row));
    }
    return axes;
}

template <class T>
bool mtkDataWriter< T >::WriteMTKFormattedData(fstream& outF, const FILE_FORMAT& fFormat)
{
    double val;
    T nr;
    if(outF)
    {
        switch(fFormat)
        {
            case ffASCII:
                for(int col = 1; col < mData->CSize() + 1; col++)
                {
                      if(writeAxis)
                    {
                        outF<<"\n"<<mData->GetColAxis()->Element(col);
                    }
                      for(int row = 1; row < mData->RSize() + 1; row++)
                    {
                        outF<<"\t"<<mData->mTheData(row,col);
                    }
                }
              return true;

              case ffBINARY:
                for(int col = 1; col < mData->CSize() + 1; col++)
                {
                      if(writeAxis)
                    {
                        val = mData->GetColAxis()->Element(col);
                        outF.write((char *) &val, sizeof(val));
                      }
                    for(int row = 1; row < mData->RSize() + 1; row++)
                    {
                        nr = mData->Element(row,col);
                        outF.write((char *) &nr, sizeof(nr));
                    }
                }
                  return true;
        }
    }
    return false;
}

template <class T>
bool mtkDataWriter<T>::WriteMTKFooter(fstream& outF, const FILE_FORMAT& fFormat)
{
      if(outF)
    {
        switch(fFormat)
        {
            case ffASCII:
            case ffBINARY:
            default:
                return true;
        }
    }
      return false;
}

//template < class T>
//bool mtkDataWriter< T >::mtkReal(const string& fileN, const FILE_FORMAT& fFormat)
//{
//      string fileName = (fileN.empty()) ? mData->GetFileName() : fileN;
//
//    //Switch the type of mTheData temporarily to dfDouble
//    DATA_FORMAT   origFormat = mData->GetDataFormat();
//    mData->SetDataFormat(dfDouble);
//
//    fstream *outStream = OpenFile(fileName.c_str(), fFormat, mtkOut);
//    WriteMTKHeader(*outStream, fFormat);
//    if(writeAxis)
//    {
//        WriteMTKRowAxis(*outStream, fFormat);
//    }
//
//    WriteMTKFormattedData(*outStream, dfDouble, fFormat);
//    WriteMTKFooter(*outStream, fFormat);
//    CloseFile(outStream);
//    mData->SetDataFormat(origFormat);
//    return true;
//}

//template <class T>
//bool mtkDataWriter< T >::mtkImaginary(const string& fileN, const FILE_FORMAT& fFormat)
//{
//      string fileName = (fileN.empty()) ? mData->GetFileName() : fileN;
//
//    fstream *outStream = OpenFile(fileName.c_str(), fFormat, mtkOut);
//
//    //Switch the type of mTheData temporarily to mtkIMAGINARY
//    DATA_FORMAT   origFormat = mData->GetDataFormat();
//    mData->SetDataFormat(mtkIMAGINARY);
//
//    WriteMTKHeader(*outStream, fFormat);
//    WriteMTKRowAxis(*outStream, fFormat);
//    WriteMTKFormattedData(*outStream, mtkIMAGINARY, fFormat);
//    WriteMTKFooter(*outStream, fFormat);
//    CloseFile(outStream);
//    mData->SetDataFormat(origFormat);
//    return true;
//}

template <class T>
bool mtkDataWriter< T >::WriteMTKSubFormat(fstream& outF, const DATA_FORMAT& format, const FILE_FORMAT& type)
{
      if(!outF)
    {
        return false;
    }
//    switch(format)
    {
//        case dfDouble:
//            mtkRealDataSection(outF, type);
//            return true;
//
//        case mtkIMAGINARY:
//            mtkImaginaryDataSection(outF, type);
//            return true;

//        default:
            mtkDataSection(outF, type);
            return true;
      }
}

template <class T>
bool mtkDataWriter<T>::mtkDataSection(fstream& fileS, const FILE_FORMAT& type)
{
    return false;
}

template <class T>
string mtkDataWriter<T>::GetFormattedData(const FILE_FORMAT& fFormat)
{
    double val;
    stringstream data_str;
    T nr;
    switch(fFormat)
    {
        case ffASCII:
            for(int col = 1; col < mData->CSize() + 1; col++)
            {
                if(writeAxis)
                {
                    data_str<<"\n"<<mData->GetColAxis()->Element(col);
                }

                for(int row = 1; row < mData->RSize() + 1; row++)
                {
                    data_str<<"\t"<<mData->mTheData(row,col);
                }
            }
            return data_str.str();

          case ffBINARY:
            for(int col = 1; col < mData->CSize() + 1; col++)
            {
                if(writeAxis)
                {
                    val = mData->GetColAxis()->Element(col);
                    data_str.write((char *) &val, sizeof(val));
                }
                for(int row = 1; row < mData->RSize() + 1; row++)
                {
                    nr = mData->Element(row,col);
                    data_str.write((char *) &nr, sizeof(nr));
                }
            }
            return data_str.str();
          default:
        return gEmptyString;
    }
}


//template<> inline
//bool mtkDataWriter< complex<double> >::mtkComplex(const string& fileN, const FILE_FORMAT& type)
//{
//
//      string fileName = (fileN.empty()) ? mData->GetFileName() : fileN;
//
//      fstream *out = OpenFile(fileName.c_str(), type, mtkOut);
//      if(out)
//    {
//        WriteMTKHeader(*out, type);
//        WriteMTKRowAxis(*out, type);
//        WriteMTKFormattedData(*out, type);
//        WriteMTKFooter(*out, type);
//        CloseFile(out);
//        return true;
//      }
//      return false;
//}

//template <class T>
//bool mtkDataWriter<T>::WriteMTKFormattedData(fstream& outF, const FILE_FORMAT& fFormat)
//{
//     double val;
//     T nr;
//    if(outF)
//    {
//        switch(fFormat)
//        {
//            case ffASCII:
//                for(int col = 1; col < mData->CSize() + 1; col++)
//                {
//                      if(writeAxis)
//                    {
//                        outF<<"\n"<<mData->GetColAxis()->Element(col);
//                    }
//                      for(int row = 1; row < mData->RSize() + 1; row++)
//                    {
//                        outF<<"\t"<<mData->mTheData(row,col);
//                    }
//                }
//              return true;
//
//              case ffBINARY:
//                for(int col = 1; col < mData->CSize() + 1; col++)
//                {
//                      if(writeAxis)
//                    {
//                        val = mData->GetColAxis()->Element(col);
//                        outF.write((char *) &val, sizeof(val));
//                      }
//                    for(int row = 1; row < mData->RSize() + 1; row++)
//                    {
//                        nr = mData->Element(row,col);
//                        outF.write((char *) &nr, sizeof(nr));
//                    }
//                }
//                  return true;
//        }
//    }
//    return false;
//}
//

//template <class T>
//void mtkDataWriter<T>::FormatFileName(string fileName)
//{
//    mtkRemoveExtension(fileName);
//      fileName += ".mtk";
//}
//
//template <class T>
//void mtkDataWriter<T>::ColsToFile(const char* fileName)
//{
//    fstream out;
//    out.open(fileName,ios::out);
//
//    out<<mData->RSize()<<"x"<<mData->CSize();
//    /*** Write out labels for each Row ***/
//    for(int row = 1;row < mData->RSize() + 1;row++)
//    {
//         out<<"\t"<<mData->GetRowAxis()->Element(row);
//    }
//
//    for(int col=1;col < mData->CSize() + 1;col++)
//    {
//        out<<"\n"<<mData->GetColAxis()->Element(col);
//        for(int row=1;row < mData->RSize() + 1;row++)
//        {
//            out<<"\t"<<mData->mTheData(row,col);
//        }
//    }
//    out.close();
//}
//
//template <class T>
//void mtkDataWriter<T>::RealRowToFile(int rowNr,const char* fileName)
//{
//    int col;
//    fstream outFile;
//    outFile.open(fileName,ios::out);
//
//    for(col=1;col<mData->CSize()+1;col++)
//    {
//         outFile<<mData->GetColAxis()->Element(col)<<"\t"<<real(mData->mTheData(rowNr,col))<<"\n";
//    }
//    outFile.close();
//}
//
//template <class T>
//void mtkDataWriter<T>::RealRowsToFile(const string& fileName)
//{
//    remove(fileName.c_str());
//    fstream out;
//    out.open(fileName.c_str(),ios::out);
//    //  out<<mData->RSize()<<"x"<<mData->CSize();
//
//    /*** Write out labels for each Row ***/
//       if(mData->RSize() >1)
//    {
//         for(int row = 1;row < mData->RSize() + 1;row++)
//        {
//            out<<"\t"<<mData->GetRowAxis()->Element(row);
//        }
//           out<<"\n";
//       }
//
//    for(int col=1;col < mData->CSize() + 1;col++)
//    {
//         out<<mData->GetColAxis()->Element(col);
//        for(int row=1;row < mData->RSize() + 1;row++)
//        {
//             out<<"\t"<<real(mData->mTheData(row,col));
//        }
//        out<<"\n";
//       }
//    out.close();
//}
//
//template <class T>
//void mtkDataWriter<T>::RealColsToFile(const char* fileName)
//{
//    int row,col;
//    fstream out;
//    out.open(fileName,ios::out);
//
//      //    out<<"Col Axis\t"<<"Cols: "<<1<<" -> "<<ColDimSize<<"\n";
//    for(row=1;row < mData->RSize()+ 1;row++)
//    {
//        out<<mData->GetRowAxis()->Element(row)<<"\t";
//          for(col=1;col< mData->CSize() + 1;col++)
//        {
//            out<<real(mData->mTheData(row,col))<<"\t";
//        }
//        out<<"\n";
//    }
//      out.close();
//}
//
//template <class T>
//void mtkDataWriter<T>::ColProjectionToFile(const string& FileName)
//{
//    fstream out;
//    int col;
//    out.open(FileName.c_str(),ios::out);
//
//    out<<"Dim = "<<mData->CSize()<<"\n";
//    for(col=1;col<mData->CSize()+1;col++)
//    {
//        out << mData->GetColAxis()->Element(col)<<"\t"<<real(mData->ColProjection->Element(col))<<"\n";
//    }
//
//    out.close();
//}
//
//template <class T>
//void mtkDataWriter<T>::RowProjectionToFile(const string &FileName)
//{
//      fstream out;
//      int row;
//      out.open(FileName.c_str(),ios::out);
//
//      out<<"#Dim = "<<mData->RSize()<<"\n";
//      for(row=1;row<mData->RSize()+1;row++)
//    {
//        out<<mData->GetRowAxis()->Element(row)<<"\t"<<real(mData->GetRowProjection()->Element(row))<<"\n";
//    }
//      out.close();
//}

//template <class T>
//void mtkDataWriter<T>::RealRowsToFile(int Offset, int Increment, const char* fileName)
//{
//    /*** This function writes the rows (real part) that resides in the datamatrix
//    based on the paramaters Offset and Increment. Offset is the first row (slice) to
//    be written and increment defines the following ones. For example, if one wants to
//    extract the 2,5,8,11 row in an mTheData set (called Sample) and write it to a file called
//    sample.dat write in program:
//
//        Sample.RealRowsToFile(2,3,"sample.dat")
//
//    This creates an file ("sample.dat") consisting of the slices 2,5,8 11 and corresponding axes(if the
//    datamatrix is larger the count continues) written as columns. The axis is the first column.
//      ***/
//
//    fstream out;
//    out.open(fileName,ios::out);
//    int row,col;
//
//    for(col=1;col<mData->CSize()+1;col++)
//    {
//         out<<mData->GetColAxis()->Element(col)<<"\t";
//        for(row=Offset;row<mData->RSize()+1;row+=Increment)
//        {
//            out<<real(mData->mTheData(row,col));
//            if((row+Increment)<mData->RSize()+1)/*** Don't put a tab after the last element ***/
//            {
//                out<<"\t";
//            }
//        }
//        out<<"\n";
//    }
//      out.close();
//}
//
//template <class T>
//void mtkDataWriter<T>::RealRowBlockToFile(int firstRow, int lastRow, const char* FileName)
//{
//    /*** Function that writes a block of rows to a file. The function starts to write
//         the first row with number "firstRow" and continues until the last row is written.
//         The first column is corresponding axis
//    ***/
//
//    fstream out;
//    out.open(FileName,ios::out);
//
//    for(int col=1;col<mData->CSize()+1;col++)
//    {
//        out<<mData->GetRowAxis()->Element(col)<<"\t";
//        for(int row=firstRow;row<lastRow+1;row+=1)
//        {
//            out<<real(mData->mTheData(row,col));
//            if(row<mData->RSize()+1)/*** Don't put a tab after the last element ***/
//            {
//                out<<"\t";
//            }
//        }
//        out<<"\n";
//    }
//      out.close();
//}

//template <class T>
//void mtkDataWriter<T>::RowToFile(int rowNr, const char* fileName)
//{
//    fstream out;
//    out.open(fileName,ios::out);
//
//    out<<"Row nr "<<rowNr<<"\n";
//    for(int col=1;col<mData->CSize()+1;col++)
//    {
//        out<<mData->GetColAxis()->Element(col)<<"\t"<<mData->mTheData(rowNr,col)<<"\n";
//    }
//
//    out.close();
//}
//
//template <class T>
//void mtkDataWriter<T>::RealColToFile(int colNr, const char* fileName)
//{
//    fstream out;
//    out.open(fileName,ios::out);
//
//    out<<"RowDim = "<<mData->RSize()<<"\nColDim = "<<mData->CSize()<<"\n";
//       out<<"\t"<<mData->GetColAxis()->Element(colNr)<<"\n";
//
//    for(int row=1;row <mData->RSize()+1;row++)
//    {
//         out<<"\n"<<mData->GetRowAxis()->Element(row);
//        out<<"\t"<<real(mData->mTheData(row,colNr));
//    }
//    out.close();
//}

//template <class T>
//void mtkDataWriter<T>::IncrementToFile(const char* FileName)
//{
//    ofstream IncrFile;
//    IncrFile.open(FileName);
//    if(!IncrFile)
//    {
//        cout<<"Could not open file: "<<FileName<<"\n";
//    }
//    else
//    {
//        IncrFile<<"t1Start Value = "<<mData->GetRowAxis()->GetOffset()<<"\n";
//        IncrFile<<"Experiment increment = "<<mData->GetRowAxis()->GetIncrement()<<"\n";
//        IncrFile.close();
//    }
//}

//template <class T>
//void mtkDataWriter<T>::RowsToFile(const string &fileName)
//{
//    fstream out;
//    out.open(fileName.c_str(),ios::out);
//
//    out<<mData->RSize()<<"x"<<mData->CSize();
//    /*** Write out labels for each Row ***/
//    for(int row = 1;row < mData->RSize() + 1;row++)
//    {
//        out<<"\t"<<mData->GetRowAxis()->Element(row);
//    }
//
//     for(int col=1;col < mData->CSize() + 1;col++)
//    {
//        out<<"\n"<<mData->GetColAxis()->Element(col);
//            for(int row=1;row < mData->RSize() + 1;row++)
//            {
//                out<<"\t"<<mData->mTheData(row,col);
//            }
//    }
//    out.close();
//}



//template <class T>
//bool mtkDataWriter<T>::WriteMTKSubFormat(fstream& outF, const DATA_FORMAT& format, const FILE_FORMAT& type)
//{
//    return false;
//}
//
//

template <class T>
bool mtkDataWriter< T >::WriteMTKRowAxis(std::ostream& outF, const FILE_FORMAT& fFormat)
{
      if(outF)
    {
        switch(fFormat)
        {
              case ffASCII:
                for(int row = 1; row < mData->RSize() + 1; row++)
                {
                      outF<<"\t"<<mData->GetRowAxis()->Element(row);
                }
                  return true;

              case ffBINARY:
                for(int row = 1; row < mData->RSize() + 1; row++)
                {
                      double val = mData->GetRowAxis()->Element(row);
                      outF.write((char *) &(val), sizeof(val));
                }
              return true;
        }
      }
      return false;
}


template <class T>
bool mtkDataWriter< T >::WriteMTKHeader(fstream& outF, const FILE_FORMAT& fFormat)
{
    string str;
    char *cstr;
    if(outF)
    {
        switch(fFormat)
        {
              case ffASCII:
                outF<<GetHeaderString()<<"\n";
              return true;

              case ffBINARY:
                str = GetHeaderString();
                cstr = new char[str.size() + 1];
                strcpy(cstr, str.c_str());

                outF.write((char *) cstr, strlen(cstr) + 1);
                if(outF.rdstate())
                {
                    throw(dsl::DSLException("Could not write mtkHeader"));
                }


              return true;
        }
      }
      return false;
}

//template < class T >
//bool mtkDataWriter< T >::mtkRealDataSection(fstream& fileS, const FILE_FORMAT& type)
//{
////    if(!fileS.is_open())
////    {
////        return false;
////    }
////    double nr, val;
////    switch(type)
////    {
////        case ffASCII:
////            for(int col = 1; col < mData->CSize() + 1; col++)
////            {
////                if(writeAxis)
////                {
////                    fileS << "\n"<<mData->GetColAxis()->Element(col);
////                }
////                else
////                {
////                    if(col != 1)//Don't start with an empty line
////                    {
////                        fileS<<"\n";
////                    }
////                }
////
////                for(int row = 1; row < mData->RSize() + 1; row++)
////                {
////                    if(writeAxis == false)
////                    {
////                        if(row != 1 )
////                        {
////                            fileS<<"\t";
////                        }
////                    }
////                    else
////                    {
////                        fileS<<"\t";
////                    }
////                    fileS<<real(mData->Element(row,col));
////                }
////            }
////            return true;
////
////        case ffBINARY:
////            for(int col = 1; col < mData->CSize() + 1; col++)
////            {
////                if(writeAxis)
////                {
////                    val = mData->GetColAxis()->Element(col);
////                    fileS.write((char *) &val, sizeof(val));
////                }
////                for(int row = 1; row < mData->RSize() + 1; row++)
////                {
////                    nr = real(mData->Element(row,col));
////                    fileS.write((char *) &nr, sizeof(nr));
////                }
////            }
////            return true;
////    }
////
////      return false;
//}
//

}
#endif
