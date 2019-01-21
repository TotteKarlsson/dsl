#ifndef dslMatrixH
#define dslMatrixH
//#include <complex>
//#include <fstream>
//#include <ostream>
#include "dslAbstractMatrix.h"
#include "dslMathExporter.h"
#include <iostream>
namespace dsl
{

//extern "C" {
//#include ".\..\dslCSource\Meschach\matrix2.h"
//#include ".\..\dslCSource\Meschach\zmatrix2.h" //This is Meschach complex matrix functions
//};

template <class T> class dslVector;
using std::cout;
//using std::ostream;
using std::fstream;
using std::ios;
//using std::complex;
//using std::abs;
//typedef std::complex<double> cpx;

template <class T>
class dslMatrix : public dslAbstractMatrix<T>
{
    public:
											  dslMatrix(int rsz=0, int csz=0);
											  dslMatrix(const dslMatrix<T> &In);
											 ~dslMatrix();
		virtual dslMatrix<T>&                 operator=(const dslMatrix<T>& b);
		virtual const dslMatrix<T>            operator*(const dslMatrix<T>& b);
		virtual const dslMatrix<T>            operator*(const dslMatrix<T>& b) const;
		const dslMatrix<T>                    operator+(const dslMatrix<T>& b) const; //??????
		const dslMatrix<T>                    operator+(const dslMatrix<T>& b);
		const dslMatrix<T>                    operator-(const dslMatrix<T>& b);
		const dslMatrix<T>                    operator-(const dslMatrix<T>& b) const;

		//Seems that friends has to be explicitly instantiated??
//		friend const dslMatrix<T>             operator*(const dslMatrix<T>& Rmat, const T& rVal);
//
//		friend const dslMatrix<T>             operator*(const T& rVal, const dslMatrix<T>& Rmat);
//
//		friend const dslMatrix<T>             operator*(const dslMatrix<T>& Rmat, int rVal);
//		friend const dslMatrix<T>             operator*(int rVal, const dslMatrix<T>& Rmat);
//
//		friend const dslMatrix<T>             operator*(const dslMatrix<T>& Rmat, double rVal);
//		friend const dslMatrix<T>             operator*(double rVal, const dslMatrix<T>& Rmat);
//		friend dslVector<T>                      operator*(const dslMatrix<T> &Mat, const dslVector<T> &Vec);

		const dslMatrix<T>                    DP(const dslMatrix<T> &Second);           /*** Direct product ***/
		const T                               SP(const dslMatrix<T> &Second);           /*** Scalar product ***/
		void                                  CC();                                     /*** Complex conjugate ***/
		//void                                  GetEigenValues(dslVector<T> &vec);
		//void                                  GetEigenSystem(dslMatrix< complex<double> > &Diagonal, dslMatrix< complex<double> > &Eigenvectors);
		//void                                  GetInverse(dslMatrix<T> &Inverse);
		T                                     GetTrace();
		//dslMatrix<T>                          GetInverse();
		const dslMatrix<T>                    GetTranspose() const;
		const dslMatrix<T>                    GetCC() const;             /*** Complex conjugate ***/
		//const dslMatrix<T>                    GetAdjoint() const;
		dslMatrix<T>                          GetCol(int i);
		void                                  Fill();
		int                                   Size();
		void                                  MakeUnity();
		void                                  Show();
		void                                  MatToFile(char *fileName);
		
	protected:
		//void                                  eigval_tqli(double d[], double e[], int n);
		//void                                  eigval_tred2(double **a, int n, double d[], double e[]);
};

//////////////////////////////////////////////////////////////////////////////////
//DSL_MATH ostream& operator<<(ostream &stream, const dslMatrix< double > &out);
//DSL_MATH ostream& operator<<(ostream &stream, const dslMatrix< complex<double> > &out);
//////////////////////////////////////////////////////////////////////////////////

//Utility functions
template <class T>
const dslMatrix<T> exp(const dslMatrix<T>& Rmat);

template <class T>
const T Tr(const dslMatrix<T>& mat);

template <class T>
dslMatrix<T>::dslMatrix(int rsz,int csz) 
: dslAbstractMatrix<T>(rsz, csz)
{}

template <class T>
dslMatrix<T>::~dslMatrix()
{
    if(this->mIsAllocated)
    {
        this->FreeMatrix();
    }
}

template <class T>
int dslMatrix<T>::Size()
{
    return this->mRowSize;
}

template <class T>
dslMatrix<T>::dslMatrix(const dslMatrix<T> &In)
{
    //Copy Constructor
      this->Create(In.mRowSize, In.mColSize);

      for(unsigned int row = 1; row <this->mRowSize +1; row++)
    {
        for(unsigned int col = 1; col < this->mColSize +1; col++)
        {
               this->mMatrix[row][col] = In[row][col];
        }
    }
}

/*** "Get" functions***/
template <class T>
dslMatrix<T> dslMatrix<T>::GetCol(int Col)
{
    dslMatrix<T>  temp(this->mRowSize,1);
      for(unsigned int row = 1; row <this->mRowSize + 1; row++)
        temp(row,1) = this->mMatrix[row][Col];
      return temp;
}

template <class T>
T dslMatrix<T>::GetTrace()
{
    T temp = 0;
      for(unsigned int row = 1; row < this->mRowSize + 1; row++)
        temp += this->mMatrix[row][row];
      return temp;
}

template <class T>
const T Tr(const dslMatrix<T>& mat)
{
    T temp = 0;
      for(unsigned int row = 1; row < mat.GetRowSize() + 1; row++)
        temp += mat(row,row);
      return temp;
}

template <class T>
const dslMatrix<T> exp(const dslMatrix<T>& Rmat)
{
    /*** Observe that the matrix has o be diagonal before applying this function! ***/
      dslMatrix<T> temp(Rmat.GetRowSize(), Rmat.GetColSize());
      for(unsigned int row = 1; row < Rmat.GetRowSize() + 1; row++)
        temp(row,row) = exp( Rmat(row,row) );

      return temp;
}

template <class T>
const dslMatrix<T> dslMatrix<T>::GetTranspose() const
{
    dslMatrix<T> TempMat(this->mColSize,this->mRowSize);

      //Copy original matrix into the Transposed one
      for(unsigned int Rows = 1 ; Rows < this->mRowSize + 1; Rows++)
        for(unsigned int Cols = 1; Cols < this->mColSize + 1; Cols++)
              TempMat[Cols][Rows] = this->mMatrix[Rows][Cols];

      return TempMat;
}

template <class T>
const dslMatrix<T> dslMatrix<T>::GetCC() const
{
    dslMatrix<T> TempMat;
      TempMat = *this;
      TempMat.CC();
      return TempMat;
}

template <class T>
void dslMatrix<T>::CC()
{
    /*** on non-complex numbers the complex conjugate has no effect ***/
}

template <class T>
void dslMatrix<T>::Fill()
{
      if(!this->mIsAllocated)
      {
          return;
      }

      int i = 1;
    for(unsigned int r = 1; r<this->mRowSize + 1 ; r++)
    {
        for(unsigned int c = 1; c<this->mColSize + 1 ; c++)
        {
            this->mMatrix[r][c] = i++;
        }
    }
    this->mIsDiagonalMatrix = false;
}

template <class T>
void dslMatrix<T>::Show()
{
      for(unsigned int row=1;row <this->mRowSize + 1;row++)
    {
        cout<<"\n";
        for(unsigned int col = 1; col < this->mColSize + 1; col++)
        {
              cout<<this->mMatrix[row][col];
              cout<<"\t";
        }
      }
      cout<<"\n........................\n";
}

template <class T>
void dslMatrix<T>::MakeUnity()
{
    if(this->mRowSize != this->mColSize)
    {
        //("Matrix is not square in MakeUnity Function..\n");
    }
      else
    {
        for(unsigned int r = 1; r < this->mRowSize + 1; r++)
        {
            for(unsigned int c = 1; c < this->mColSize + 1; c++)
            {
                this->mMatrix[r][c] = (r==c) ? 1 : 0;
            }
        }
        this->mIsDiagonalMatrix = true;
      }
}

template <class T>
void dslMatrix<T>::MatToFile(char *fileName)
{
//    std::fstream out;
//    out.open(fileName,ios::out);
//    out<<"#Dim: "<<this->mColSize<<"x"<<this->mRowSize<<"\n";
//    for(unsigned int row = 1; row < this->mRowSize + 1; row++)
//    {
//        out<<"\n";
//        for(unsigned int col = 1; col < this->mColSize + 1; col++)
//        {
//              out<< this->mMatrix[row][col];
//              out<<"\t";
//        }
//    }
//    out.close();
}

template <class T>
dslMatrix<T>& dslMatrix<T>::operator = (const dslMatrix<T> &mat2)
{
    if(this->mRowSize != mat2.mRowSize || this->mColSize != mat2.mColSize)
    {
           this->Create(mat2.mRowSize, mat2.mColSize);    //Resize
    }

    if(!this->mMatrix || !this->IsAllocated())
    {
        return *this;
    }

      for(unsigned int row = 1; row < this->mRowSize + 1; row++)
    {
        for(unsigned int col = 1; col < this->mColSize + 1; col++)
        {
               this->mMatrix[row][col] = mat2(row,col);
        }
    }
      return *this;
}

template <class T>
const dslMatrix<T> dslMatrix<T>::operator*(const dslMatrix<T> &rMat)
{
    if(this->mColSize != rMat.mRowSize)
    {
        cout<<"Matrix product not defined, incompatible sizes..\n";
        return *this;
      }

      dslMatrix<T> temp(this->mRowSize,rMat.mColSize);
      T tempVal = 0;
      for(unsigned int row1 = 1; row1 < this->mRowSize + 1; row1++)
    {
        for(unsigned int rescol = 1; rescol < rMat.mColSize + 1; rescol++)
        {
              for(unsigned int col1 = 1; col1 < this->mColSize + 1; col1++)
            {
                tempVal = this->mMatrix[row1][col1]*rMat.mMatrix[col1][rescol] + tempVal;
              }
              temp.mMatrix[row1][rescol] = tempVal;
              tempVal = 0;
        }
      }
      return temp;
}

template <class T>
const dslMatrix<T> dslMatrix<T>::operator*(const dslMatrix<T> &rMat) const
{
    if(this->mColSize != rMat.mRowSize)
    {
        cout<<"Matrix product not defined, incompatible sizes..\n";
        return *this;
      }

      dslMatrix<T> temp(this->mRowSize,rMat.mColSize);
      T tempVal = 0;

      for(unsigned int row1 = 1; row1 < this->mRowSize + 1; row1++)
    {
        for(unsigned int rescol = 1; rescol < rMat.mColSize + 1; rescol++)
        {
              for(unsigned int col1 = 1; col1 < this->mColSize + 1; col1++)
            {
                tempVal = this->mMatrix[row1][col1]*rMat.mMatrix[col1][rescol] + tempVal;
              }
              temp.mMatrix[row1][rescol] = tempVal;
              tempVal = 0;
        }
      }
      return temp;
}

template <class T>
const dslMatrix<T> dslMatrix<T>::operator+(const dslMatrix<T> &b)
{
    dslMatrix<T> temp(b.mRowSize,b.mColSize);

      for(unsigned int row = 1; row < this->mRowSize + 1; row++)
        for(unsigned int col = 1; col < this->mColSize + 1; col++)
              temp.mMatrix[row][col] = this->mMatrix[row][col] + b.mMatrix[row][col];

  return temp;
}

template <class T>
const dslMatrix<T> dslMatrix<T>::operator+(const dslMatrix<T> &b) const
{
    dslMatrix<T> temp(b.mRowSize,b.mColSize);
    for(unsigned int row = 1; row < this->mRowSize + 1; row++)
        for(unsigned int col = 1; col < this->mColSize + 1; col++)
              temp.mMatrix[row][col] = this->mMatrix[row][col] + b.mMatrix[row][col];

      return temp;
}

template <class T>
const dslMatrix<T> dslMatrix<T>::operator-(const dslMatrix &b)
{
      dslMatrix<T> temp(b.mRowSize,b.mColSize);
      for(unsigned int row = 1; row < this->mRowSize + 1; row++)
        for(unsigned int col = 1; col < this->mColSize + 1; col++)
              temp.mMatrix[row][col] = this->mMatrix[row][col] - b.mMatrix[row][col];

      return temp;
}

template <class T>
const dslMatrix<T> dslMatrix<T>::operator-(const dslMatrix &b) const
{
      dslMatrix<T> temp(b.mRowSize,b.mColSize);
      for(unsigned int row = 1; row < this->mRowSize + 1; row++)
        for(unsigned int col = 1; col < this->mColSize + 1; col++)
              temp.mMatrix[row][col] = this->mMatrix[row][col] - b.mMatrix[row][col];

      return *this;
}

template <class T>
const dslMatrix<T> dslMatrix<T>::DP(const dslMatrix<T> &B)
{
    dslMatrix< T > C(this->mRowSize*B.mRowSize, this->mColSize*B.mColSize);
        for(unsigned int pos1 = 0, row = 1;  row < this->mRowSize + 1; row++, pos1 += B.mRowSize)
              for(unsigned int pos2 = 0, col = 1; col < this->mColSize + 1; col++, pos2 += B.mColSize)
                for(unsigned int rowB = 1;  rowB < B.mRowSize + 1; rowB++)
                      for(unsigned int colB = 1; colB < B.mColSize + 1; colB++)
                        C(pos1 + rowB,pos2 + colB) = this->mMatrix[row][col] * B(rowB,colB);
      return C;
}

template <class T>
const T dslMatrix<T>::SP(const dslMatrix<T> &B)
{
      T Scalar = 0;
      for(unsigned int row = 1;  row < this->mRowSize + 1; row++)
        for(unsigned int col = 1; col < this->mColSize + 1; col++)
              Scalar  += this->mMatrix[row][col]*B(row,col);

      return Scalar;
}

//Friends does not work as expected?
// template <class T>
// const dslMatrix<T> operator*(const T &scalar, const dslMatrix<T>& Rmat){
//
//  dslMatrix<T> temp(Rmat.mRowSize,Rmat.mColSize);
//  for(unsigned int row=1;row < Rmat.mRowSize + 1;row++)
//      for(unsigned int col=1;col<Rmat.mColSize + 1;col++)
//        temp.mat[row][col] = Rmat.mat[row][col]*scalar;
//
//  return temp;
// }

template <class T>
const dslMatrix<T> operator*(const dslMatrix<T>& Rmat, const T& scalar)
{
    dslMatrix<T> temp(Rmat.mRowSize,Rmat.mColSize);
      for(unsigned int row=1;row < Rmat.mRowSize + 1;row++)
          for(unsigned int col=1;col<Rmat.mColSize + 1;col++)
            temp.mMatrix[row][col] = Rmat.mMatrix[row][col]*scalar;

      return temp;
}

}
#endif
