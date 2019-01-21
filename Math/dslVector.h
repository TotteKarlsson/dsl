#ifndef dslVectorH
#define dslVectorH
#include <complex>
#include <fstream>
#include <iostream>
#include "dslMathUtils.h"
#include "dslAbstractVector.h"

namespace dsl
{

using std::ostream;
using std::istream;
using std::fstream;
using std::cout;
using std::complex;

DSL_MATH complex<double>*           vectorCpx(long nl, long nh);
DSL_MATH void                       free_vectorCpx(complex<double> *v, long nl, long nh);
DSL_MATH void                       swap1(complex<double> *in, int Size);
DSL_MATH void                       swap2(complex<double> *in, int Size);
DSL_MATH void                       swap3(complex<double> *in, int Size);

DSL_MATH void                       undo_swap1(complex<double> *in, int Size);
DSL_MATH void                       undo_swap2(complex<double> *in, int Size);
DSL_MATH void                       undo_swap3(complex<double> *in, int Size);


//The Vector class should be renamed to Array
template <class T> class dslMatrix;

template <class T>
class dslVector : public dslAbstractVector<T>
{
    public:
                                                dslVector();
                                                dslVector(int e);
                                                dslVector(int s, int e);
                                                dslVector(const dslVector<T> &In);
        virtual                                 ~dslVector();

        dslVector<T>&                           operator = (const dslVector<T> &rightVec);
        dslVector<T>&                           operator = (double *dblVec);
        dslVector<T>                            operator + (dslVector<T> &rightVec);
        dslVector<T>                            operator - (dslVector<T> &rightVec);
        T                                       operator * (dslVector<T> &Vec);

        T                                       DotProduct(dslVector<T> *VecR);
        T                                       AngleTo(dslVector<T> *VecR);
        T                                       ProjOn(dslVector<T> *VecR);
        T                                       Magnitude();
        void                                    Normalize();
        void                                    Normalize(double Norm);
        void                                    RotateAroundZ(double angle);
        void                                    Fill();
        void                                    Zero();
        //void                                    ToFile(const char *fileName);

	private:
};

typedef dslVector< complex<double> > CpxVec;

//istream& operator>>(istream &stream, dslVector< double > *out);
//istream& operator>>(istream &stream, dslVector< double > &out);
//istream& operator>>(istream &stream, dslVector< complex<double> > *out);
//istream& operator>>(istream &stream, dslVector< complex<double> > &out);

ostream& operator<<(ostream &stream, dslVector< double > *out);
ostream& operator<<(ostream &stream, dslVector< double > &out);
ostream& operator<<(ostream &stream, dslVector< complex<double> > *out);
ostream& operator<<(ostream &stream, dslVector< complex<double> > &out);

template <class T>
inline dslVector<T>::dslVector()
{
    this->mIsArrayAllocated = false;
}

template <class T>
inline dslVector<T>::dslVector(int last)
{
    this->mIsArrayAllocated = false;
    this->mStartIndex = 1;
    this->mEndIndex = last;
    this->Create(this->mStartIndex,this->mEndIndex);
}

template <class T>
inline dslVector<T>::dslVector(int first, int last)
{
    this->mIsArrayAllocated = false;
    this->mStartIndex = first;
    this->mEndIndex     = last;
    this->Create(this->mStartIndex, this->mEndIndex);
}

template <class T>
dslVector<T>::~dslVector()
{
    if(this->mIsArrayAllocated)
    {
        this->vec = this->vec + this->mStartIndex - 1;
        delete[] this->vec;
        this->mIsArrayAllocated = false;
    }
}

//template <class T>
//void dslVector<T>::ToFile(const char *fileName)
//{
//    fstream out;
//    out.open(fileName, ios::out);
//    out<<this;
//    out.close();
//}

template <class T>
void dslVector<T>::Fill()
{
    for(unsigned int index = this->mStartIndex; index < this->mEndIndex + 1; index++)
      {
        this->vec[index] = index;
      }
}

template <class T>
void dslVector<T>::Zero()
{
      for(unsigned int r = this->mStartIndex; r < this->mEndIndex + 1; r++)
      {
        this->vec[r] =  0.0;
      }
}

template <class T>
void dslVector<T>::Normalize()
{
    int index;
    double NORM,max;

    for(index = this->mStartIndex; index < this->mEndIndex + 1; index++)
    {
        if(abs(real(this->vec[index])) > abs(real(max)))
        {
            max = real(this->vec[index]);
        }
    }

    NORM = fabs(max);
    if(real(NORM))
    {
        for(index = 1; index < this->mEndIndex + 1; index++)
        {
          this->vec[index] = this->vec[index]/NORM;
        }
    }
    else
    {
        cout<<"Tried to Normalize with 0 !!\n";
    }
}

template <class T>
void dslVector<T>::Normalize(double Norm)
{
  for(unsigned int index = 1; index < this->mEndIndex + 1; index++)
    this->vec[index]=this->vec[index]/Norm;
}

template <class T>
dslVector<T> dslVector<T>::operator-(dslVector<T> &rightVec)
{
  if(this->mStartIndex != rightVec.mStartIndex)
    {
        //dslError("Incompatible size in operator = (dslVector &)");
    }

  dslVector<T> temp(this->mStartIndex,this->mEndIndex);

  for(unsigned int index = this->mStartIndex; index < this->mEndIndex + 1; index++)
    temp[index] = this->vec[index] - rightVec[index];

  return temp;
}

template <class T>
dslVector<T>::dslVector(const dslVector<T> &In)
{
  this->mIsArrayAllocated = false;
  this->Create(In.mStartIndex,In.mEndIndex);
  for(unsigned int index = this->mStartIndex; index < this->mEndIndex + 1; index++)
    this->vec[index] = In.vec[index];
}

//template < >
//dslVector< complex<double> >& dslVector< complex<double> >::operator=(double *dblVec){
// /*** Function that copies a double vec into a vec. The fuctions design is
//    such the first element in the dblVec is copied to the Real part of the first complex<double>
//    element in the complex<double> vector. The second element in the dblVec is copied into the Imaginary part of the first
//    complex<double> element, and so on... ***/
//
//      int k = 0;
//      for(unsigned int index = mStartIndex; index < this->mEndIndex +1; index+=1){
//              this->vec[index] = complex<double> (dblVec[index+k], dblVec[index+1 +k]);
//              k++;
//      }
//      return *this;
// }

template <class T>
dslVector<T>& dslVector<T>::operator=(double *dblVec)
{
  for(unsigned int index = this->mStartIndex; index < this->mEndIndex + 1; index += 1)
    this->vec[index] = dblVec[index];

  return *this;
}

template <class T>
dslVector<T>& dslVector<T>::operator = (const dslVector<T>  &rightVec)
{
  /*** Check Size ***/
  //if(this == &rightVec) return *this;
  //if(mStartIndex != rightVec.mStartIndex)
  //  dslError("Incompatible size in operator = (dslVector &)");

  for(unsigned int index = this->mStartIndex; index < this->mEndIndex + 1; index++)
    this->vec[index] = rightVec.vec[index];
  return *this;
}

template <class T>
dslVector<T> dslVector<T>::operator+(dslVector<T> &rightVec)
{
  if(this->mStartIndex != rightVec.mStartIndex)
  {
    //dslError("Incompatible size in operator = (dslVector &)");
  }
  dslVector<T> temp(this->mStartIndex,this->mEndIndex);
  for(unsigned int index = this->mStartIndex; index < this->mEndIndex + 1; index++)
    temp[index] = this->vec[index] + rightVec[index];

  return temp;
}

template <class T>
T dslVector<T>::operator*(dslVector<T> &rightVec)
{
  /*** The scalar product for two vectors ***/
  T temp = 0;
  for(unsigned int index = this->mStartIndex; index < this->mEndIndex + 1; index++)
    temp += this->vec[index]*rightVec[index];
  return temp;
}

template <class T>
T dslVector<T>::DotProduct(dslVector<T> *VecR)
{
   /*** The scalar product for two vectors ***/
  T temp = 0;
  for(unsigned int index = this->mStartIndex; index < this->mEndIndex + 1; index++)
    temp += this->vec[index]*VecR->Element(index);
  return temp;
}

template <class T>
T dslVector<T>::AngleTo(dslVector<T> *VecR)
{
   /*** Return the Angle betweem two vectors ***/
  return cos(DotProduct(VecR)/(Magnitude()*VecR->Magnitude()));
}

template <class T>
T dslVector<T>::ProjOn(dslVector<T> *VecR)
{
  /*** Return "Projection" (A magnitude)***/
  T Angle = AngleTo(VecR);
  return abs(Magnitude()*cos(Angle));
}

//dslVector dslVector::operator = (CpxMat &MatCpx){
///*** This operator, with a matrix on the right allows
//    copying if the matrix has only one column (i.e a column vector).
//    That occurs especially if one wants to extract a column (or row) from some
//    matrix with the matrix function GetCol (or GetRow)(See dslMatrixCPX). This overloaded operator
//    allows one to conviently store the resulting Col (or row) in a complex<double> vector.
//    If the operator are called when the matrix is not of a one column or one row form
//    the function returns an error....***/
//
//      /*** Check Size ***/
//      if(MatCpx.cSize != 1)
//       dslError("Wrong matrix size in 'dslVector operator=(TKMATCPX ..).");
//
//      if(MatCpx.rSize != this->mEndIndex)
//       dslError("Wrong matrix size in 'dslVector operator=(TKMATCPX ..).");
//
//      for(unsigned int index = mStartIndex; index < this->mEndIndex +1; index++)
//              this->vec[index] = MatCpx(index,1);
//      return *this;
//};

template <class T>
T dslVector<T>::Magnitude()
{
    /*** This function calculates the Magnitude of the vector. This is
      done as taking the square root of the sum of the absolute value of all vector
      elemens. i.e : Sqrt( |elem1^2|+|elem2^2|....|elemn^2|) ***/
      T val = 0;;
      for(unsigned int index = this->mStartIndex; index < this->mEndIndex + 1; index++)
    {
        val += pow(this->vec[index],2);
    }

      return sqrt(val);
}

template <class T>
void dslVector<T>::RotateAroundZ(double angle)
{
    dslVector tempv(3);
    if(this->Size() != 3)
    {
        //dslError("Can't rotate this vector..");
    }
    double angle_rad = angle*gPi/180;

    tempv[1] = cos(angle_rad)*this->vec[1] - sin(angle_rad)*this->vec[2];
    tempv[2] = sin(angle_rad)*this->vec[1] + cos(angle_rad)*this->vec[2];
    tempv[3] = this->vec[3];

    for(unsigned int index = 1; index < 4; index++)
    {
        this->vec[index] = tempv[index];
    }
};

}
#endif
