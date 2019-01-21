#ifndef dslAbstractMatrixH
#define dslAbstractMatrixH
#include "dslException.h"
#include "dslObject.h"
#include "dslUtils.h"

namespace dsl
{

template <class T>
class dslAbstractMatrix : public DSLObject
{
    public:
                                    dslAbstractMatrix(int rsz = 0, int csz = 0);
        virtual                     ~dslAbstractMatrix() = 0;
        bool                        IsAllocated(){return mIsAllocated;}
        virtual T&                  operator()(int row, int col) const;
        T*                          operator[](int row) const;
        bool                        Create(const int rsz, const int csz);
        bool                        ReSize(int rsz, int csz);
        bool                        ReSizeRowDim(int newRowSize);
        bool                        ReSizeColDim(int newColSize);
        int                         GetRowSize() const {return mRowSize;}
        int                         GetColSize() const {return mColSize;}
        void                        Transpose();
        //T                         GetCol(int i);
        int                         GetDimension(){return mRowSize*mColSize;}
        void                        Zero();
        int*                        GetRowSizeRef(){return &mRowSize;}
        int*                        GetColSizeRef(){return &mColSize;}

    protected:
        unsigned int                mRowSize;
        unsigned int                mColSize;
        T**                         mMatrix;
        bool                        mIsAllocated;
        bool                        mIsDiagonalMatrix;
        bool                        mIsUnityMatrix;

        /*** Memory functions ***/

        void                        FreeMatrix();               /* free The matrix allocated by allocatematrix */
        void                        FreeMatrix(T **);           /* free a matrix allocated by allocatematrix */

	private:
        T**                         AllocateMatrix(int rows, int cols);
};

template <class T>
dslAbstractMatrix<T>::dslAbstractMatrix(int rsz, int csz)
:
mRowSize(rsz),
mColSize(csz),
mMatrix(nullptr),
mIsAllocated(false),
mIsDiagonalMatrix(false),
mIsUnityMatrix(false)
{
    if(mRowSize && mColSize)
    {
        mMatrix = AllocateMatrix(mRowSize, mColSize);
        Zero();
    }
}

template <class T>
dslAbstractMatrix<T>::~dslAbstractMatrix()
{
    if(mIsAllocated)
    {
        FreeMatrix();
    }
}

template <class T>
bool dslAbstractMatrix<T>::Create(const int rowsize, const int colsize)
{
    if(mIsAllocated)
    {
         FreeMatrix();
    }

    if(rowsize > 0 && colsize > 0)
    {
        mMatrix = AllocateMatrix(rowsize, colsize);
    }

    return mMatrix ? true : false;
}

template <class T>
void dslAbstractMatrix<T>::Zero()
{
    if(mMatrix)
    {
        for(unsigned int r = 1; r < mRowSize + 1; r++)
        {
              for(unsigned int c = 1; c < mColSize + 1; c++)
            {
                mMatrix[r][c] = (T) 0;
            }
        }
    }
}

template <class T>
bool dslAbstractMatrix<T>::ReSize(int rsz, int csz)
{
    if(mIsAllocated)
    {
        FreeMatrix();
    }

    mMatrix = AllocateMatrix(rsz, csz);
    return mMatrix ? true : false;
}

///*** Allocations Functions ***/
template <class T>
T** dslAbstractMatrix<T>::AllocateMatrix(int rowSize, int colSize)
{
    unsigned int theRSize = !rowSize ? 1:rowSize;
    unsigned int theCSize = !colSize ? 1:colSize;

    /*** allocate a T matrix with subscript range m[1..mRowSize][1..mColSize] ***/
    T** m;
    try
    {    /* allocate pointers to rows */
        size_t nrOfBytes = (size_t) (theRSize+1)*sizeof(T*);
        m = (T**) malloc(nrOfBytes);
        if(!m)
        {
            throw(dsl::DSLException("Could not allocate pointers to rows"));
        }
    }
    catch(...)
    {
        m = nullptr;
        return m;
    }

    try
    {    /* allocate rows and set pointers to them */
        size_t nrOfBytes = (theRSize*theCSize + 1)*sizeof(T);
        m[1] = (T*) malloc(nrOfBytes);

        if(!m[1])
        {
            throw(dsl::DSLException("Could not allocate matrix rows"));
        }

        for(unsigned int i = 1 + 1; i <= theRSize; i++)
        {
            m[i] = m[i-1] + theCSize;
        }

        mRowSize = rowSize;
        mColSize = colSize;
        mIsAllocated = true;
        return m;
    }
    catch(...)
    {
        free((T*) m[1]);
        free((T**) m);
        m = nullptr;
        return m;
    }
}

template <class T>
void dslAbstractMatrix<T>::FreeMatrix()
{
    FreeMatrix(mMatrix);
}

template <class T>
void dslAbstractMatrix<T>::FreeMatrix(T** m)
{
    /* free a T matrix allocated by matrixCpx() */
    free((char*) m[1]);
    free((char*) m);
    m = nullptr;
    mIsAllocated = false;
    mRowSize = mColSize = 0;
}

template <class T>
void dslAbstractMatrix<T>::Transpose()
{
    T **TempMat;
    int oldRowSize = mRowSize;
    int    oldColSize = mColSize;

    //Allocate a "transposed" matrix
    TempMat = AllocateMatrix(oldColSize, oldRowSize);

    //Copy original matrix into the Transposed one
    for(unsigned int Rows = 1 ; Rows < mRowSize + 1; Rows++)
        for(unsigned int Cols = 1; Cols < mColSize + 1; Cols++)
            TempMat[Cols][Rows] = mMatrix[Rows][Cols];

    //Create a new matrix
    Create(oldColSize, oldRowSize);    //Observe that mRowSize and mColSize will
                                    //be swapped after this call!
    //Copy temp into new one
    for(unsigned int Rows = 1 ; Rows < mRowSize + 1; Rows++)
        for(unsigned int Cols = 1; Cols < mColSize + 1; Cols++)
            mMatrix[Rows][Cols] = TempMat[Rows][Cols];

    //Deallocate temp
    FreeMatrix(TempMat);
}

template <class T>
bool dslAbstractMatrix<T>::ReSizeRowDim(int newrSize)
{
    int oldrSize = mRowSize;
    T **tempmat = AllocateMatrix(oldrSize,mColSize);

    //Copy old Matrix into a temp MAtrix
    for(long index1=1;index1<mRowSize+1;index1++)
        for(long index2=1;index2<mColSize+1;index2++)
            tempmat[index1][index2] = mMatrix[index1][index2];

     //Create a new matrix
     Create(newrSize,mColSize);

    //Copy Back
    if(oldrSize<newrSize)
    {
        for(long index1 = 1; index1 < oldrSize + 1; index1++)
            for(long index2 = 1; index2 < mColSize + 1; index2++)
                mMatrix[index1][index2] = tempmat[index1][index2];
     }

     if(oldrSize > newrSize)
     {
        for(long index1 = 1; index1 < newrSize + 1; index1++)
            for(long index2 = 1;index2 < mColSize + 1; index2++)
                mMatrix[index1][index2] = tempmat[index1][index2];
     }
     FreeMatrix(tempmat);
     return true;
}

template <class T>
bool dslAbstractMatrix<T>::ReSizeColDim(int newcSize)
{
    int oldcSize = mColSize;
    T **tempmat = AllocateMatrix(mRowSize,oldcSize);

    for(long index1 = 1; index1 < mRowSize + 1; index1++)
        for(long index2 = 1; index2 < mColSize + 1; index2++)
            tempmat[index1][index2] = mMatrix[index1][index2];

    //Create new matrix
     Create(mRowSize,newcSize);

    //Copy Back
    if(oldcSize < newcSize)
    {
        for(long index1=1;index1<mRowSize+1;index1++)
            for(long index2=1;index2<oldcSize+1;index2++)
                mMatrix[index1][index2] = tempmat[index1][index2];
     }

     if(oldcSize > newcSize)
     {
        for(long index1=1;index1<mRowSize+1;index1++)
            for(long index2=1;index2<newcSize+1;index2++)
                mMatrix[index1][index2] = tempmat[index1][index2];
     }
     FreeMatrix(tempmat);
     return true;
}

template <class T>
T& dslAbstractMatrix<T>::operator()(int row, int col) const
{
    /*** Put a number or get a number into/from the matrix ***/
    #ifdef TKDEBUG
    if(row > mRowSize+1)
    {
        cout<<"To Big Row index in dslAbstractMatrix!\n";
        TKPause();
    }
    if(col > mColSize+1)
    {
        cout<<"To Big Col index in dslAbstractMatrix!\n";
        TKPause();
    }
    #endif

    return mMatrix[row][col];
}

template <class T>
T* dslAbstractMatrix<T>::operator[](int row) const
{
    /*** return a pointer to a T vector ***/
    #ifdef TKDEBUG
    if(row > mRowSize + 1)
    {
        cout<<"To Big Row index in dslAbstractMatrix!\n";
        TKPause();
    }
    #endif
    return mMatrix[row];
}

}
#endif
