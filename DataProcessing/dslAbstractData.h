#ifndef dslAbstractDataH
#define dslAbstractDataH
#include <memory>
#include "dslAxes.h"
#include "dslDataProcessProperties.h"
#include "dslDataProperties.h"
#include "dslFile.h"
#include "dslMatrix.h"
#include "dslObject.h"
#include "dslShowDataPart.h"
#include "DataExporter.h"
#include "dslAxes.h"

namespace dsl
{

using namespace std;
template <class T>
class mtkData;

//class mtkAxes;
class mtkLimits;

template <class T>
class mtkAbstractData : public DSLObject
{
    public:
        /*** Internal data representation ***/
        mtkMatrix<T>                 mTheData;

      public :
                                    /*** Constructors and destructors ***/
                                    mtkAbstractData(int rSize = 0, int cSize = 0);
        virtual                    ~mtkAbstractData() = 0;

        virtual const T&            Element(int row, int col) const;
        virtual T&                  Element(int row, int col);

                                    /*** Div functions ***/
        bool                        Add(const mtkData<T>& addMe);
        bool                        MergeRows(const mtkData<T>& addMe);
        bool                        MergeCols(const mtkData<T>& addMe);
        int                         RSize() const;
        int                         GetRowDimSize() const;
        int                         CSize() const;
        int                         GetColDimSize() const;

        void                        SetSizeOfRowBlock(int rBlocksize);
        int                         GetRowBlockSize();
        void                        SetSizeOfColBlock(int cBlocksize);
        int                         GetColBlockSize();
        void                        GetProjections();
        void                        ZeroAll();
        void                        ZeroMatrix();

        /*** "Size" functions ***/
        virtual bool                Resize(int newRSize, int nCSize);
        bool                        AddRows(int nrOfNewRows);
        bool                        AddCols(int nrOfNewCols);
        bool                        ResizeRowDim(int newRSize);
        bool                        ResizeRowDim(int start, int end);
        bool                        ResizeColDim(int newCSize);
        bool                        ResizeColDim(int start, int end);
        virtual void                Transpose();

        /*** overloaded operators ***/
        virtual T&                     operator()(int row, int col) const;

        bool                         IsAllocated(){return mTheData.IsAllocated();}
        mtkMatrix<T>*                 GetMatrix(){return &mTheData;}
        mtkMatrix<T>*                 GetData(){return &mTheData;}
        void                           SetRowDimSize(int rSize);
        void                           SetColDimSize(int cSize);

        mtkDataProperties*          GetProperties(){return &mDataProperties;}
        mtkDataProcessProperties*   GetProcProps(){return this->mProcessingProperties;}

        mtkAxes*                       GetXAxis(){return mColAxis;}
        mtkAxes*                       GetColAxis();

        mtkAxes*                     GetYAxis(){return mRowAxis;}
        mtkAxes*                     GetRowAxis(){return mRowAxis;}
        mtkData<T>*                 GetRowProjection();
        mtkData<T>*                 GetColProjection();

        //File handling
  //      File*                     GetFile();

        //FileFormat
        void                         SetFileFormat(const FILE_FORMAT& fFormat);
        FILE_FORMAT                 GetFileFormat();

        //FileName
        string                      GetFullFileName(){return mFile.GetNameAndPath();}
        string                      GetFileName();
        string                      GetFilePath();
        void                           SetFile(const string& newPF);
        void                           SetFileName(const string& name);
        void                         SetFilePath(const string& newPath);

        //DataFormat
        void                         SetDataFormat(const DATA_FORMAT& format);
        DATA_FORMAT                   GetDataFormat();

        //Changes
        bool                         IsModified();
        void                         IsModified(const bool& is);

        int                          GetCurrentSlice(){return mCurrentSlice;}
        void                         SetCurrentSlice(int slice);

        //Moved from mtkData
        T                           GetValueInRowAtAxisValue(int row, double AxisValue);
        T                           GetSumOfPoints(int row, double AxisPosLeft, double AxisPosRight);
        T                           GetSumOfPoints(int row, const mtkLimits *Limits);
        int                         GetNrOfPointsInIntervall(double from, double to);
        void                        Fill();
        void                        FillRandom();

        //When visualizing
        int                         GetCurrentRow(){return mCurrentRow;}
        void                        SetCurrentRow(int row){mCurrentRow = row;}
        int                         GetCurrentCol(){return mCurrentCol;}
        void                        SetCurrentCol(int col){mCurrentCol = col;}
        DATA_DIMENSION                GetActiveDimension(){return mActiveDim;}
        void                        SetActiveDimension(const DATA_DIMENSION& dim);
        short                       GetNrOfDimensions();
        int                         GetNrOfSlicesInDim(const DATA_DIMENSION& dim);
        void                        SetShowDataPart(const mtkShowDataPart& part);
        mtkShowDataPart             GetShowDataPart(){return mShowDataPart;}
		
    protected:
        int                         mCurrentRow;
        int                         mCurrentCol;
        int                         mCurrentSlice;
        DATA_DIMENSION                 mActiveDim;
        mtkShowDataPart                mShowDataPart;

        mtkDataProperties             mDataProperties;
        File                     mFile;

        mtkAxes                    *mRowAxis;
        mtkAxes                    *mColAxis;
        mtkData<T>                    *mRowProjection;
        mtkData<T>                    *mColProjection;
		
    private:
        bool                         AllocateRowProjection();
        bool                         AllocateColProjection();
};

template <class T>
mtkAbstractData<T>::mtkAbstractData(int rsz, int csz)
:
mTheData(rsz, csz),
mShowDataPart(sdpReal),
mDataProperties(mTheData.GetRowSizeRef(), mTheData.GetColSizeRef()),
//mFile(""),
mRowProjection(nullptr),
mColProjection(nullptr),
mCurrentSlice(1),
mCurrentRow(1),
mCurrentCol(1),
mActiveDim(rowDimension)
{
       mTheData.Create(mDataProperties.rowDimSize, mDataProperties.colDimSize);
       mTheData.Zero();

    mRowAxis = new mtkAxes(rsz);
    mColAxis = new mtkAxes(csz);

    mRowAxis->Fill();
    mColAxis->Fill();

    mShowDataPart.reset();
    mShowDataPart.set(sdpReal, true);
}

template <class T>
inline mtkAbstractData<T>::~mtkAbstractData()
{
    delete mRowAxis;
    delete mColAxis;
    delete mRowProjection;
    delete mColProjection;
}

template <class T>
mtkAxes* mtkAbstractData<T>::GetColAxis()
{
    return mColAxis;
}

template <class T>
void mtkAbstractData<T>::SetShowDataPart(const mtkShowDataPart& part)
{
    mShowDataPart = part;
}

template <class T>
bool mtkAbstractData<T>::Add(const mtkData<T>& addMe)
{
    //check size of mTheData matrices
    int rSize = RSize(), cSize = CSize();
    if(addMe.RSize() != rSize)
    {
        Log(lDebug3)<<"wrong size of mTheData";
        return false;
    }

    if(addMe.CSize() != cSize)
    {
        Log(lDebug3)<<"wrong size of mTheData";
        return false;
    }

    for(int i = 1; i < rSize + 1; i++)
    {
        for(int j = 1; j < cSize + 1; j++)
        {
            Element(i,j) = Element(i,j) + addMe.Element(i,j);
        }
    }

    return true;
}

template <class T>
bool mtkAbstractData<T>::MergeRows(const mtkData<T>& mergeMe)
{
    //check size of mTheData matrices
    int cSize = CSize();
    if(mergeMe.CSize() != cSize)
    {
        Log(lDebug3)<<"Incompatible size of mTheData in merge function";
        return false;
    }

    //How many rows are we mergin in?
    int nrOfNewRows = mergeMe.RSize();
    this->AddRows(nrOfNewRows);

    for(int k = 1, i = (RSize() - nrOfNewRows) + 1; i < RSize() + 1; i++, k++)
    {
        for(int j = 1; j < cSize + 1; j++)
        {
            Element(i,j) = mergeMe.Element(k,j);
        }
    }

    return true;
}

template <class T>
bool mtkAbstractData<T>::MergeCols(const mtkData<T>& mergeMe)
{
    //check size of mTheData matrices
    int rSize =RSize();
    if(mergeMe.RSize() != rSize)
    {
        Log(lDebug3)<<"Incompatible size of mTheData in merge function";
        return false;
    }
    //How many cols are we mergin in?
    int nrOfNewCols = mergeMe.CSize();
    this->AddCols(nrOfNewCols);

    for(int j = 1; j < rSize + 1; j++)
    {
        for(int colToMerge = 1, i = (CSize() - nrOfNewCols) + 1; i < CSize() + 1; i++, colToMerge++)
        {
            Element(j, i) = mergeMe.Element(j, colToMerge);
        }
    }

    return true;
}

template <class T>
inline T& mtkAbstractData<T>::operator()(int row, int col) const
{
    return mTheData(row,col);
}

template <class T>
inline const T& mtkAbstractData<T>::Element(int row, int col) const
{
    return mTheData(row,col);
}

template <class T>
inline T& mtkAbstractData<T>::Element(int row, int col)
{
    return mTheData(row,col);
}

template <class T>
inline int mtkAbstractData<T>::RSize() const
{
    return mDataProperties.rowDimSize;
}

template <class T>
inline int mtkAbstractData<T>::GetRowDimSize() const
{
    return mDataProperties.rowDimSize;
}

template <class T>
inline void mtkAbstractData<T>::SetRowDimSize(int newRSize)
{
    mDataProperties.rowDimSize = newRSize;
}

template <class T>
inline int mtkAbstractData<T>::CSize() const
{
    return mDataProperties.colDimSize;
}

template <class T>
inline int mtkAbstractData<T>::GetColDimSize() const
{
    return mDataProperties.colDimSize;
}

template <class T>
inline void mtkAbstractData<T>::SetColDimSize(int newCSize)
{
    mDataProperties.colDimSize = newCSize;
}

template <class T>
void mtkAbstractData<T>::SetCurrentSlice(int slice)
{
    mCurrentSlice = slice;
    switch(mActiveDim)
    {
        case Dim1:      mCurrentRow = slice;    break;
        case Dim2:      mCurrentCol = slice;    break;
        default:
        break;
    }
}

template <class T>
int mtkAbstractData<T>::GetNrOfSlicesInDim(const DATA_DIMENSION& dim)
{
    switch(dim)
    {
        case Dim1:      return RSize();
        case Dim2:      return CSize();
        default:        return 0;
    }
}

template <class T>
void mtkAbstractData<T>::SetActiveDimension(const DATA_DIMENSION& dim)
{
    //When active dimension changes, the mCurrentSlice will change too..
    mActiveDim = dim;
    switch(mActiveDim)
    {
        case Dim1:      mCurrentSlice = mCurrentRow; break;
        case Dim2:      mCurrentSlice = mCurrentCol; break;
    }
}

template <class T>
short mtkAbstractData<T>::GetNrOfDimensions()
{
    short dimNr = 0;
    if(CSize() > 0)
    {
        dimNr++;
    }
    if(RSize() > 1)
    {
        dimNr++;
    }
    return dimNr;
}

template <class T>
inline int mtkAbstractData<T>::GetRowBlockSize()
{
    return mDataProperties.rowBlockSize;
}

template <class T>
inline int mtkAbstractData<T>::GetColBlockSize()
{
    return mDataProperties.colBlockSize;
}

template <class T>
mtkData<T>* mtkAbstractData<T>::GetRowProjection()
{
    if(!mRowProjection)
    {
        if(AllocateRowProjection())
        {
          return mRowProjection;
        }
        else
        {
            mRowProjection = nullptr;
        }
    }
    return mRowProjection;
}

template <class T>
mtkData<T>* mtkAbstractData<T>::GetColProjection()
{
    if(!mColProjection)
    {
        if(AllocateColProjection())
        {
            return mColProjection;
        }
    }
    else
    {
        mColProjection = nullptr;
    }
    return mColProjection;
}

template <class T>
bool mtkAbstractData<T>::AllocateRowProjection()
{
    if(mRowProjection)
    {
        delete mRowProjection;
        mRowProjection = nullptr;
    }

    try
    {
        mRowProjection = new mtkData<T>(1, RSize());
        mRowProjection->GetRowAxis()->SetAxis(mRowAxis);
    }
    catch(...)
    {
        return false;
    }
    return true;
}

template <class T>
bool mtkAbstractData<T>::AllocateColProjection()
{
    if(mColProjection)
    {
        delete mColProjection;
        mColProjection = nullptr;
    }

    try
    {
        mColProjection = new mtkData<T>(1, CSize());
        mColProjection->GetColAxis()->SetAxis(mColAxis);
    }catch(...)
    {
        return false;
    }
    return true;
}

template <class T>
bool mtkAbstractData<T>::Resize(int NewRowSize, int NewColSize)
{
    if(!ResizeRowDim(NewRowSize))
    {
        return false;
    }

    if(!ResizeColDim(NewColSize))
    {
        return false;
    }

    return true;
}

template <class T>
bool mtkAbstractData<T>::ResizeRowDim(int newRowSize)
{
    if(newRowSize == mDataProperties.rowDimSize)
    {
        return true;
    }
    else
    {
        int oldRowSize = mDataProperties.rowDimSize;

        if(!IsAllocated())
        {
            //We need "something to work with
            bool result1 = mTheData.Create(newRowSize, 1);
            bool result2 = mRowAxis->Resize(newRowSize);
            return result1 && result2;
        }

        mtkMatrix<T> tempMat(mDataProperties.rowDimSize, mDataProperties.colDimSize);

        //First Copy everything
        if(oldRowSize < newRowSize)
        {
            tempMat = mTheData;
        }
        else //oldRowSize is larger than new one (shrinking matrix..)
        {
            for(int j = 1; j < newRowSize + 1; j++)
            {
                for(int i = 1;i < mDataProperties.colDimSize + 1; i++)
                {
                    tempMat(j,i) = mTheData(j,i);
                }
            }
        }

        /*** Resize Row Dimension ***/
        if(!mTheData.Create(newRowSize, mDataProperties.colDimSize))
        {
            return false;
        }
        mTheData.Zero();
        mDataProperties.rowDimSize = newRowSize;

        //copy Back
        if(oldRowSize < newRowSize)
        {
            for(int j = 1; j < oldRowSize + 1; j++)
            {
                for(int i = 1; i < mDataProperties.colDimSize + 1; i++)
                {
                    mTheData(j,i)=tempMat(j,i);
                }
            }
        }

        if(oldRowSize > newRowSize)
        {
            for(int j = 1; j < newRowSize + 1; j++)
            {
                for(int i = 1; i < mDataProperties.colDimSize + 1; i++)
                {
                    mTheData(j,i)=tempMat(j,i);
                }
            }
        }
        mCurrentSlice = 1;
    }

    return mRowAxis->Resize(newRowSize) ? true : false;
}

template <class T>
bool mtkAbstractData<T>::AddRows(int nrOfNewRows)
{
    return ResizeRowDim(RSize() + nrOfNewRows);
}

template <class T>
bool mtkAbstractData<T>::AddCols(int nrOfNewCols)
{
    return ResizeColDim(CSize() + nrOfNewCols);
}

template <class T>
bool mtkAbstractData<T>::ResizeRowDim(int Start, int End)
{
    /*** This is a cut ***/
    int newColSize = End - Start + 1;

    /*** A temporary matrix ***/
    mtkMatrix<T> tempMat(mDataProperties.rowDimSize,(End-Start) +1);

    for(int i=1 ;i<mDataProperties.rowDimSize +1;i++)
    {
        for(int j=Start;j<End +1;j++)
        {
            tempMat(i,j-Start +1)=mTheData(i,j);
        }
    }

    /*** Resize Row Dimension ***/
    if(!mTheData.Create(mDataProperties.rowDimSize,newColSize))
    {
        return false;
    }
    mDataProperties.colDimSize = newColSize;
    mTheData.Zero();

    /*** Copy Back ***/
    for(int j=1;j<mDataProperties.rowDimSize +1;j++)
    {
        for(int i=1 ;i<mDataProperties.colDimSize +1;i++)
        {
            mTheData(j,i) = tempMat(j,i);
        }
    }

    return true;
}

template <class T>
bool mtkAbstractData<T>::ResizeColDim(int newColSize)
{
    if(newColSize == mDataProperties.colDimSize)
    {
        return true;
    }
    else
    {
        int oldColSize = mDataProperties.colDimSize;

        if(!IsAllocated())
        {
            //We need "something to work with
            return mTheData.Create(1, newColSize);
        }

        mtkMatrix<T> tempMat;

        //First copy Everything
        if(oldColSize < newColSize)
        {
            tempMat.ReSize(mDataProperties.rowDimSize, oldColSize);
            tempMat = mTheData;
        }
        else
        {
            tempMat.ReSize(mDataProperties.rowDimSize, newColSize);
            for(int j = 1; j < mDataProperties.rowDimSize + 1; j++)
            {
                for(int i = 1; i < newColSize + 1; i++)
                {
                    tempMat[j][i] = mTheData(j,i);
                }
            }
        }

        /*** Resize Col Dimension ***/
        if(!mTheData.Create(mDataProperties.rowDimSize, newColSize))
        {
            return false;
        }
        mTheData.Zero();
        mDataProperties.colDimSize = newColSize;

        //Copy Everything Back
        if(oldColSize < newColSize)
        {
            for(int j = 1; j < mDataProperties.rowDimSize + 1; j++)
            {
                for(int i = 1;i < oldColSize + 1; i++)
                {
                    mTheData(j,i) = tempMat(j,i);
                }
            }
        }

        if(oldColSize > newColSize)
        {
            for(int j = 1; j < mDataProperties.rowDimSize + 1; j++)
            {
                for(int i = 1; i < newColSize + 1; i++)
                {
                    mTheData(j,i) = tempMat(j,i);
                }
            }
        }
    }

    return (!mColAxis->Resize(newColSize)) ? false : true;
}

template <class T>
bool mtkAbstractData<T>::ResizeColDim(int start, int end)
{
    /*** This is a cut ***/
    int newRSize = end - start +1;

    /*** A temporary matrix ***/
    mtkMatrix<T> tempMat(newRSize,mDataProperties.colDimSize);

    for(int i = 1 ;i < mDataProperties.colDimSize + 1; i++)
    {
        for(int j = start;j < end + 1; j++)
        {
            tempMat(j - start+1, i) = mTheData(j,i);
        }
    }


    /*** Resize Col Dimension ***/
    if(!mTheData.Create(newRSize,mDataProperties.colDimSize))
    {
        return false;
    }
    mDataProperties.rowDimSize = newRSize;
    mTheData.Zero();

    /*** Copy Back ***/
    for(int j = 1; j < mDataProperties.colDimSize + 1; j++)
    {
        for(int i = 1; i < mDataProperties.rowDimSize + 1; i++)
        {
            mTheData(i,j) = tempMat(i,j);
        }
    }

    return true;
}

template <class T>
void mtkAbstractData<T>::SetSizeOfRowBlock(int rowblocksize)
{
    mDataProperties.rowBlockSize =  rowblocksize;
}

template <class T>
void mtkAbstractData<T>::SetSizeOfColBlock(int colblocksize)
{
    mDataProperties.colBlockSize =  colblocksize;
}

template <class T>
void mtkAbstractData<T>::ZeroAll()
{
    mTheData.Zero();
}

template <class T>
void mtkAbstractData<T>::Transpose()
{

    mTheData.Transpose();
    int tmp = mDataProperties.rowDimSize;
    mDataProperties.rowDimSize = mDataProperties.colDimSize;
    mDataProperties.colDimSize = tmp;
}

template <class T>
void mtkAbstractData<T>::SetFileName(const string& newName)
{
    mFile.SetFileName(newName);
}

template <class T>
void mtkAbstractData<T>::SetFilePath(const string& newPath)
{
    mFile.SetPath(newPath);
}

template <class T>
void mtkAbstractData<T>::SetFile(const string& newPF)
{
    mFile.SetFileName(newPF);
}

//template <class T>
//File* mtkAbstractData<T>::GetFile()
//{
//    return &mFile;
//}

template <class T>
string mtkAbstractData<T>::GetFileName()
{
    return mFile.GetFileName();
}

template <class T>
string mtkAbstractData<T>::GetFilePath()
{
    return mFile.GetPath();
}

template <class T>
void mtkAbstractData<T>::SetDataFormat(const DATA_FORMAT& format)
{
    mFile.SetDataFormat(format);
}

template <class T>
DATA_FORMAT    mtkAbstractData<T>::GetDataFormat()
{
    return mFile.GetDataFormat();
}

template <class T>
void mtkAbstractData<T>::SetFileFormat(const FILE_FORMAT& fFormat)
{
    mFile.SetFileFormat(fFormat);
}

template <class T>
FILE_FORMAT mtkAbstractData<T>::GetFileFormat()
{
    return mFile.GetFileFormat();
}

//template <class T>
//File* mtkAbstractData<T>::GetOriginalFile()
//{
//    return &mOriginalFileInfo;
//}
//
//template <class T>
//DATA_FORMAT   mtkAbstractData<T>::GetOriginalDataFormat()
//{
//    return mOriginalFileInfo->DataFormat();
//}
//
//template <class T>
//FILE_FORMAT mtkAbstractData<T>::GetOriginalFileFormat()
//{
//    return mOriginalFileInfo->FileFormat();
//}
//
//template <class T>
//void mtkAbstractData<T>::SetOriginalDataFormat(const DATA_FORMAT& format)
//{
//    mOriginalFileInfo.SetDataFormat(format);
//}
//
//template <class T>
//void mtkAbstractData<T>::SetOriginalFileFormat(const FILE_FORMAT& format)
//{
//    mOriginalFileInfo.SetFileFormat(format);
//}
//
//template <class T>
//void mtkAbstractData<T>::SetOriginalFile(const string& fName)
//{
//    mOriginalFileInfo.SetFileName(fName);
//}

template <class T>
bool mtkAbstractData<T>::IsModified()
{
    return mDataProperties.isModified;
}

template <class T>
void mtkAbstractData<T>::IsModified(const bool& is)
{
    mDataProperties.isModified = is;
}

}
#endif
