#pragma hdrstop
#include <fstream>
#include <cmath>
#include "dslAxes.h"


namespace dsl
{

dslAxes::dslAxes(int Size) 
: 
dslVector<double>(Size),
mLabel(""),
mOffset(0),
mIncrement(1),
mSW(0),
mIsEvenlySpaced(true)
{}

dslAxes::~dslAxes()
{}

double dslAxes::GetOffset()
{
    return (Size()) ?  vec[1] : 0;
}

double dslAxes::GetIncrement()
{
    switch(Size())
    {
        case 0:
            mIncrement = 0;
        break;
        case 1:
            mIncrement = vec[1];
        break;
        default:
            mIncrement = vec[2]-vec[1];
        break;
    }

  return mIncrement;
}

dslAxes& dslAxes::operator = (const dslAxes &rAxis)
{
    /*** Update Axis attributes ***/
    this->mIncrement         = rAxis.mIncrement;
    this->mSW                 = rAxis.mSW;
    this->mLabel            = rAxis.mLabel;
    this->mOffset            = rAxis.mOffset;
    this->mIsEvenlySpaced    = rAxis.mIsEvenlySpaced;

    /*** Check Size ***/
    if(Size() != rAxis.Size())
    {
        Create(rAxis.Size());
    }

    for(int index = mStartIndex; index < mEndIndex +1; index++)
    {
        vec[index] = rAxis.Element(index);
    }

    return *this;
}

void dslAxes::SetLabel(const char *Text)
{
    mLabel = Text;
}

void dslAxes::SetAxis(dslAxes* NAxis)
{
    /*** Use this one if dealing with pointers ***/
      if(Size() != NAxis->Size())
    {
        Create(NAxis->Size());
    }

      for(int index = mStartIndex; index < mEndIndex +1; index++)
    {
        SetElement(index) = NAxis->Element(index);
    }
      //Update();
}

void dslAxes::Cut(int mStartIndex, int mEndIndex)
{
    /*** This is a cut ***/
    int newSize = mEndIndex -mStartIndex +1;
    /*** A temporary vector ***/
    dslVector<double> tempVec(1, (mEndIndex-mStartIndex) +1);

    for(int j=mStartIndex;j<mEndIndex +1;j++)
    {
        tempVec[j-mStartIndex+1] = vec[j];
    }

    /*** Resize Dimension ***/
    Create(1,newSize);

    Zero();
    /*** Copy Back ***/
    for(int i=1 ;i<mEndIndex +1;i++)
    {
        vec[i] = tempVec[i];
    }
    Update();
}

void dslAxes::Fill()
{
      dslVector<double>::Fill();
      Update();
}

void dslAxes::Update()
{
      double mOffset = GetOffset();
      mIncrement = GetIncrement();

      for(int i = 1; i < Size() + 1; i++)
    {
        vec[i] = mOffset + (i-1)*mIncrement;
    }


    mSW  = (Size()) ? fabsl(vec[1])+fabsl(vec[ Size() ]) : 0.0;
      mIsEvenlySpaced = true;
}

void dslAxes::ReFill()
{
      double mOffset = GetOffset();

      mIncrement         = GetIncrement();
      for(int i = 1; i < Size()+1; i++)
    {
        vec[i] = mOffset + (i-1)*mIncrement;
    }

      mSW = fabsl(vec[1]) + fabsl(vec[ Size() ]);
      mIsEvenlySpaced = true;
}

double dslAxes::GetMax()
{
      double max = -10e30,temp;
      for(int Col = 1;Col < Size() + 1; Col++)
    {
        temp = vec[Col];
        if(temp > max)
        {
              max = temp;
        }
      }
      return max;
}

double dslAxes::GetMin()
{
      double min = 10e30;
      for(int Col = 1; Col < Size() + 1; Col++)
    {
        double temp = vec[Col];
        if(temp < min)
        {
              min = temp;
        }
      }
      return min;
}

void dslAxes::SetOffset(double Value)
{
    mOffset = Value;
}

void dslAxes::SetIncrement(double Value)
{
      mIncrement = Value;
      for(int i = 1; i < Size()+1; i++)
    {
        vec[i] = mOffset+(i-1)*mIncrement;
    }
      mIsEvenlySpaced = true;
}

void dslAxes::SetNormalized()
{
      double Norm = Size();
      for(int i = 1; i < Size()+1; i++)
    {
        vec[i] = double(i/Norm);
    }
}

int dslAxes::GetAxisIndexAtAxisValue(double axisValue)
{
      //Check if axisValue is within the range. If outside return max or min..
      if(axisValue <= vec[1])
    {
        return 1;
    }

      if(axisValue >= vec[Size()])
    {
        return Size();
    }

      int axisIndex = 1;
      mIncrement = GetIncrement();

      while( (axisValue - vec[axisIndex]) > mIncrement/2.)
    {
        axisIndex++;
    }
      return axisIndex;
}

void dslAxes::SetAxis(double offsetValue, double incrementValue)
{
      mIncrement = incrementValue;
      mOffset = offsetValue;
      for(int i = 1; i < Size()+1; i++)
    {
        vec[i] = mOffset + (i-1)*mIncrement;
    }

      mSW = fabsl(vec[1])+fabsl(vec[ Size() ]);
      mIsEvenlySpaced = true;
}

/*** Functions not inline ***/
ostream &operator<<(ostream &stream, dslAxes &out)
{
      int k = 0;
      stream<<out.mLabel<<" has the dimension:"<<out.Size()<<"\n";
      for(int i = out.mStartIndex; i<out.mEndIndex+1;i++)
    {
        stream<<out[i]<<"\t";
        k++;
        if(k > 10)
        {
              k = 0;
              stream<<"\n";
        }
      }
      stream<<"\n";
      return stream;
}

void dslAxes::SaveToFile(const char *fileName)
{
      std::fstream out;
      out.open(fileName, std::ios::out);
      out<<*this;
      out.close();
}

}

