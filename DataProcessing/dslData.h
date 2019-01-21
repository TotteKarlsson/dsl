#ifndef dslDataH
#define dslDataH
#include <complex>
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <string>
#include <vector>
#include "DataExporter.h"
//#include "dslLimits.h"
#include "dslLogger.h"
#include "dslAbstractData.h"
#include "dslDataProcessProperties.h"
#include "dslProcessProperties.h"
#include "dslStringUtils.h"

namespace dsl
{

using namespace std;

template <class T>
class mtkData : public mtkAbstractData<T>
{
    public:
        mtkDataProcessProperties                mProcPar;
                                                mtkData(int rszi = 0, int csz = 0);
                                                ~mtkData();
        mtkData<T>*                             GetData(){return this;}

        //void                                  SetData(const mtkData<T>* NewData);
        bool                                    Copy(mtkData<T>* NewData, bool copyFileInfo = true);
        void                                    Fill();
        void                                    FillRandom();

        T                                       GetValueInRowAtAxisValue(int row, double AxisValue);
        T                                       GetSumOfPoints(int row, double AxisPosLeft, double AxisPosRight);
        T                                       GetSumOfPoints(int row, const mtkLimits *Limits);
        int                                     GetNrOfPointsInIntervall(double from, double to);

        void                                    operator += (const mtkData<T>& addMe);
        T                                       GetNorm(){return mTheNorm;}
        void                                    SetNorm(const T& Norm){mTheNorm = Norm;}

        mtkProcessProperties*                   GetColProcessProperties();
        mtkProcessProperties*                   GetRowProcessProperties();

    private:
        T                                       mTheNorm;
};

typedef mtkData< int >                          mtkIntData;
typedef mtkData< double >                       mtkDoubleData;
typedef mtkData< complex<double> >              mtkComplexData;

ostream& operator<<(ostream& stream, const mtkIntData& theData);
ostream& operator<<(ostream& stream, const mtkDoubleData& theData);
ostream& operator<<(ostream& stream, const mtkComplexData& theData);

template <class T>
mtkData<T>::mtkData(int rsz, int csz)
:
mtkAbstractData<T>(rsz,csz),
mProcPar()
{}

template <class T>
mtkData<T>::~mtkData()
{
//    delete mProcPar;
}

template<class T>
void mtkData< T >::operator+=(const mtkData< T >& addMe)
{
    //check size of data matrices
    //Resize data if the one to add has larger dimensions...
    int rSize = this->RSize();
    int cSize = this->CSize();
    if(addMe.RSize() > rSize)
    {
        rSize = addMe.RSize();
    }

    if(addMe.CSize() > cSize)
    {
        cSize = addMe.CSize();
    }

    this->Resize(rSize, cSize);

    for(unsigned int i = 1; i < rSize + 1; i++)
    {
        for(unsigned int j = 1; j < cSize + 1; j++)
        {
              this->Element(i,j) = this->Element(i,j) + addMe.Element(i,j);
        }
    }
}

template <class T>
bool mtkData<T>::Copy(mtkData<T>* NewData, bool copyFileInfo)
{
    /*** Copy New data ***/
    if(this->RSize() != NewData->RSize())
    {
        if(!this->ResizeRowDim( NewData->RSize() ))
        {
            Log(lError)<<"Memory allocation error in mtkData Copy function: ResizeRowDim";
            return false;
        }
    }

    if(this->CSize() != NewData->CSize())
    {
        if(!this->ResizeColDim(NewData->CSize()))
        {
            Log(lError)<<"Memory allocation error in mtkData Copy function: ResizeColDim";
            return false;
        }
    }

    this->mTheData = *(NewData->GetMatrix());
    this->mColAxis->SetAxis(NewData->GetColAxis());
    this->mRowAxis->SetAxis(NewData->GetRowAxis());

    if(copyFileInfo)
    {
        this->mFile     = NewData->GetFile();    //Copy file info separetely
    }
    return true;
}

//template <class T>
//void mtkData<T>::SetData(const mtkData<T>* NewData)
//{
//    CopyData(NewData);
//}


template <class T>
void mtkData<T>::Fill()
{
    this->mTheData.Fill();
      this->mColAxis->Fill();
      this->mRowAxis->Fill();
}

template <class T>
int mtkData<T>::GetNrOfPointsInIntervall(double from, double to)
{
    int fromIndex     = this->GetColAxis()->GetAxisIndexAtAxisValue(from);
      int toIndex     = this->GetColAxis()->GetAxisIndexAtAxisValue(to);

      if(fromIndex >= toIndex)
        return 0;

      //Number of datapoints in intervall
      return toIndex - fromIndex + 1;
}

template <class T>
T mtkData<T>::GetSumOfPoints(int row, double AxisPosLeft, double AxisPosRight)
{
      int LeftStart, RightEnd;
      T Sum = 0;

      /*** First, find the limits in "integer coordinates" ***/
      LeftStart = this->mColAxis->GetAxisIndexAtAxisValue(AxisPosLeft);
      RightEnd = this->mColAxis->GetAxisIndexAtAxisValue(AxisPosRight);

      for(int i  = LeftStart; i < RightEnd + 1; i++)
        Sum += this->mTheData[row][i];

      return Sum;
}

template <class T>
T mtkData<T>::GetSumOfPoints(int row, const mtkLimits *Limits)
{
      T Sum = 0;
      /*** First, find the limits in "integer coordinates" ***/
      int LeftStart = this->mColAxis->GetAxisIndexAtAxisValue(Limits->GetLeft());
      int RightEnd  = this->mColAxis->GetAxisIndexAtAxisValue(Limits->GetRight());

      for(int i  = LeftStart; i < RightEnd + 1; i++)
        Sum += this->mTheData[row][i];

      return Sum;
}

template <class T>
T mtkData<T>::GetValueInRowAtAxisValue(int row, double AxisValue)
{
      /*** First find nearest element to AxisValue ***/
      double diff_start = fabs(this->mColAxis->Element(1) - AxisValue);
    int Position = 1;

      for(unsigned int i  = 2; i < this->CSize(); i++)
    {
        double diff = fabs(this->mColAxis->Element(i) - AxisValue);
        if(diff < diff_start)
        {
              Position = i;
        }
        diff_start = diff;
      }
      return this->mTheData[row][Position];
}

template <class T>
mtkProcessProperties* mtkData<T>::GetColProcessProperties()
{
    return mProcPar.GetColDimProperties();
}

template <class T>
mtkProcessProperties* mtkData<T>::GetRowProcessProperties()
{
    return mProcPar.GetRowDimProperties();
}

}
#endif
