#ifndef dslDataProcessH
#define dslDataProcessH
#include "dslMathUtils.h"
#include "dslData.h"
#include "dslLogger.h"
#include "dslStringUtils.h"
#include "dslException.h"

namespace dsl
{

//using namespace dsl;
template <class T>
class mtkDataProcess : public DSLObject
{
      public:
                                mtkDataProcess(mtkData<T>* data);
                                //mtkDataProcess(mtkData<T>& data);
                               ~mtkDataProcess();
        void                     AssignData(mtkData<T>* data){mData = data;}
        void                    ReadProcPar(char *File);
        void                    PhaseData(const mtkPhasing& phaseParameters);
        void                    PhasingFirstOrder(double Offset, double Phase);
        T                       GetMax();
        T                       GetMin();
        T                       GetMaxValue(int rStart, int cStart);
        pair<int, T>            GetMaxValue();
        T                        GetMean();

        void                    MultiplyBy(double val);
        void                    DivideBy(double val);
        void                    MultiplyBy(const complex<double>& val);
        void                    MultiplyFirstPointInRowsBy(double Val = 0.5);
        void                    MultiplyFirstPointInColsBy(double Val = 0.5);
        void                    MultiplyRowBy(int Row,double val);
        void                    ZeroFillInColDim(int newColSize);
        void                    ZeroFillInRowDim(int newRowSize);
        void                    ZeroFillInColDim();/*** Use values from file ***/
        void                    ZeroFillInRowDim();
        T                         Normalize();
        bool                    NormalizeData();
        bool                    Normalize(double NORM);
        bool                    NormalizeRows();
        void                    Transpose();
        void                    RepeatSegInRowToEnd(int row,int lower_bound, int upper_bound);
        //void                    RepeatSegmentInRowsToEnd(int lower_bound, int upper_bound);
        //void                    RepeatSegInColToEnd(int col, int lower_bound, int upper_bound);
        //void                    RepeatSegmentInColsToEnd(int lower_bound, int upper_bound);
        void                    DCOffsetCorrection();
        void                    DCOffsetCorrection(double lLimit, double rLimit);

        void                    InterPolateInRow(int row = 1);
        void                    InterPolateNPointsInRow(int N = 1, int row = 1);
        //void                    InterPolateColumn(int N = 1, int row = 1);
        void                    InterPolateNPointsInIntervallInRow(int N, double from, double to, int row = 1);
        void                    Shift(int row, int pts);

        /*** FFT's ***/
        void                    fftAlongRows();
        void                    fftAlongRow(int row);
        void                    CMXfftAlongRows();
        void                    IfftInT2Dim();
        void                    NRfftInT2Dim();
        void                    NRIfftInT2Dim();
        void                    fftAlongCols();
        void                    CosfftAlongCols();
        void                    IfftInT1Dim();
        void                    NRfftInT1Dim();
        void                    NRIfftInT1Dim();
        void                    CosTransformInT1Dim();
        void                    CosTransformInT2Dim();

        bool                    MagnitudeInT2Rows();
        bool                    MagnitudeInRow(int RowNumber);
        void                    AbsValueInT2Row(int RowNumber);
        void                    LBInColDim(double val);
        void                    LBInRowDim(double val);
        void                    LBInColDim();   /*** Use values from file ***/
        void                    LBInRowDim();
        void                    LBInRowandColDim(double valT2,double valT1);
        void                    ExtractProjections();
        void                    ExtractRowProjection();
        void                    ExtractRowProjection(int Start, int End, int incr);
        void                    ExtractRowProjection(const mtkVector<int>* vec);
        void                    ExtractColProjection();
        void                    ExtractColProjection(int Start, int End, int incr);
        void                    ExtractColProjection(const mtkVector<int>* vec);
        void                    SetXRange(double XStart, double XEnd);
        void                    CutInRowDimension(int Left,int Right);

    protected:
                                mtkData<T> *mData;
};

typedef mtkDataProcess< complex<double> > mtkComplexDataProcessor;

template <class T>
mtkDataProcess<T>::mtkDataProcess(mtkData<T> *data)
:
mData(data)
{}

//template <class T>
//mtkDataProcess<T>::mtkDataProcess(mtkData<T> &data)
//:
//mData(&data)
//{}
//
template <class T>
mtkDataProcess<T>::~mtkDataProcess(){}

template <class T>
void mtkDataProcess<T>::InterPolateNPointsInRow(int N, int row)
{
    //This function do linear interpolation between each point in a data row
    //the function places N points between each pair of original points
    int oldRowSize =mData->RSize();
    int oldColSize =mData->CSize();
    int newColSize = oldColSize + (oldColSize - 1) * N;

    //Copy Original data to a temporary
    mtkData< complex<double> > tempData(1, oldColSize);

    for(unsigned int i = 1; i < oldColSize + 1; i++)
    {
        tempData(1, i)                             = mData->Element(row, i);
        tempData.GetColAxis()->SetElement(i)     = mData->GetColAxis()->Element(i);
    }

    mData->Resize(oldRowSize, newColSize);

    //Interpolate N points in each segment
    T P1, P2;
    T *newPts = new T[N];
    int newPtNr = 1;
    for(unsigned int pNr = 1; pNr < tempData.CSize(); pNr++)
    {
        P1 = real(tempData.Element(row, pNr));
        P2 = real(tempData.Element(row, pNr + 1));

        //Calculate new points
        LinearInterPolateNPoints(N, P1, P2, newPts);

        mData->Element(row, newPtNr++) = P1;
        //Fill the data vector with the new points..
        for(int iP = 0; iP < N; iP++)
        {
            mData->Element(row, newPtNr++) = newPts[iP];
        }
    }
    mData->Element(row, newPtNr) = P2;
    //Adjust axis
    mData->GetColAxis()->SetAxis(tempData.GetColAxis()->GetOffset(), tempData.GetColAxis()->GetIncrement()/(N+1));
    mData->IsModified(true);
}

template <class T>
void mtkDataProcess<T>::InterPolateInRow(int row)
{
    int oldRowSize = mData->RSize();
    int oldColSize = mData->CSize();
    int newColSize = oldColSize*2 - 1;

    mData->Resize(oldRowSize, newColSize);
    for(unsigned int oldColIndex = oldColSize, newColIndex = oldColSize*2 - 1; oldColIndex > 0; oldColIndex--, newColIndex-=2)
    {
        mData->Element(row, newColIndex) = mData->Element(row, oldColIndex);
        mData->Element(row, newColIndex - 1) = 0;
    }

    //Interpolate the point between two points
    T val1, val2, res;
    for(unsigned int ColIndex = 2; ColIndex < newColSize + 1; ColIndex += 2)
    {
        val2 = mData->Element(row, ColIndex + 1);
        val1 = mData->Element(row, ColIndex - 1);
        res = (val2 - val1)/2.0 + val1;
        mData->Element(row, ColIndex) = res;
    }

    //Adjust axis
    mData->GetColAxis()->SetAxis(mData->GetColAxis()->GetOffset(), mData->GetColAxis()->GetIncrement()/2.);
    mData->IsModified(true);
}

template <class T>
void mtkDataProcess<T>::ReadProcPar(char *File)
{
  //mData->mProcPar.ProcFileName = File;
  mData->mProcPar.Read(File);
}

template <class T>
void mtkDataProcess<T>::MultiplyBy(double val)
{
    for(unsigned int Row = 1; Row < mData->RSize() + 1; Row++)
    {
        for(unsigned int Col = 1; Col < mData->CSize() + 1; Col++)
        {
              mData->mTheData(Row,Col) = mData->mTheData(Row,Col)*val;
        }
    }
}

template<> inline
void mtkDataProcess< complex<double> >::MultiplyBy(const complex<double>&  val)
{
    for(unsigned int Row = 1; Row < mData->RSize() + 1; Row++)
        for(unsigned int Col = 1; Col < mData->CSize() + 1; Col++)
              mData->mTheData(Row,Col) = mData->mTheData(Row,Col)*val;
}

template <class T>
void mtkDataProcess<T>::DivideBy(double val)
{
      for(unsigned int Row = 1; Row < mData->RSize() + 1; Row++)
        for(unsigned int Col = 1; Col < mData->CSize() + 1; Col++)
              mData->mTheData(Row,Col) = mData->mTheData(Row,Col)/val;
}

template <class T>
void mtkDataProcess<T>::SetXRange(double XStart, double XEnd)
{
//    /*** Cut the mTheData in the x dimension, XStart and XEnd are Col axis vaules ***/
//    /*** Which indexes corresponds to XStart and XEnd ? ***/
//      int Left = mData->GetColAxis()->GetElementNrAtAxisValue(XStart);
//      int Right = mData->GetColAxis()->GetElementNrAtAxisValue(XEnd);
//      mData->ResizeRowDim(Left, Right);
//      mData->GetColAxis()->Cut(Left, Right);
}

template <class T>
void mtkDataProcess<T>::RepeatSegInRowToEnd(int Row, int LowerBound, int UpperBound)
{
    /*** Repeat the segment(UpperBound-LowerBound) until end of row.. ***/
      mtkData<T> TempRow(1, UpperBound - LowerBound+1);

      for(unsigned int Col = LowerBound; Col < UpperBound + 1; Col++)
        TempRow(1,Col) = mData->Element(Row,Col);

      int DataCol = UpperBound+1;
      while(DataCol < mData->CSize() +1)
    {
        for(unsigned int Col = 1; Col < UpperBound + 1; Col++)
        {
              mData->mTheData(Row,DataCol) = TempRow(1,Col);
              DataCol++;
              if(DataCol > mData->CSize())
                break;
        }
      }
}

template <class T>
void mtkDataProcess<T>::MultiplyRowBy(int row, double val)
{
    for(int Col = 1; Col < mData->CSize() + 1; Col++)
        mData->mTheData(row,Col) = mData->mTheData(row,Col)*val;
}

template <class T>
void mtkDataProcess<T>::LBInRowDim()
{
      LBInRowDim(mData->mProcPar.GetRowDimProperties()->EM);
}

template <class T>
void mtkDataProcess<T>::LBInRowDim(double val)
{
    errno = 0;
      try
    {
        for(int row = 1; row < mData->RSize() + 1; row++)
              for(int col = 1; col < mData->CSize() + 1; col++)
            {
                //        double temp = mData->GetColAxis()->Element(col);
                mData->mTheData(row,col) = mData->mTheData(row,col)* (::exp(-val*mData->GetColAxis()->Element(col)));
                if(errno)
                {
                      string error = toString(errno);
                      string msg = "Exception in LB in Row Dim. Error Nr: " + error + " aborting execution here.";
                      throw(dsl::Exception(msg.c_str()));
                }
              }
      }
    catch(const dsl::Exception& e)
    {
//        _fpreset();
        Log(lError)<<e.Message();
      }
}

//template<> inline
//void mtkDataProcess< complex<double> >::LBInRowDim(double val)
//{
//    errno = 0;
//      try
//    {
//        for(int row = 1; row < mData->RSize() + 1; row++)
//              for(int col = 1; col < mData->CSize() + 1; col++)
//            {
//                //        double temp = mData->GetColAxis()->Element(col);
//                mData->mTheData(row,col) = mData->mTheData(row,col)*exp(-val*mData->GetColAxis()->Element(col));
//                if(errno)
//                {
//                      string error = dsl::toString(errno);
//                      string msg = "Exception in LB in Row Dim. Error Nr: " + error + " aborting execution here.";
//                      throw(Exception(msg.c_str()));
//                }
//              }
//      }
//    catch(const Exception& e)
//    {
//        _fpreset();
//        LogMessage(e.msg());
//      }
//}

template <class T>
void mtkDataProcess<T>::LBInColDim()
{
//    LBInColDim(mData->mProcPar.LBInColDim);
}

//template <class T>
//void mtkDataProcess<T>::LBInColDim(double val)
//{
//      errno = 0;
//      try
//    {
//        for(int col = 1; col < mData->CSize() + 1; col++)
//              for(int row = 1; row < mData->RSize() + 1; row++)
//            {
//                double temp = mData->GetRowAxis()->Element(row);
//                mData->mTheData(row,col) = mData->mTheData(row,col)*exp(-val*temp);
//                if(errno)
//                {
//                      string error = toString(errno);
//                      string msg = "Exception in LB in Col Dim. Error Nr: " + error + " aborting execution here.";
//                      throw(Exception(msg.c_str()));
//                }
//              }
//      }
//    catch(const Exception& e)
//    {
//        _fpreset();
//        LogMessage(e.msg());
//      }
//}

template <class T>
void mtkDataProcess<T>::MultiplyFirstPointInRowsBy(double Val)
{
      for(int row = 1; row < mData->RSize() + 1; row++)
        mData->mTheData(row,1) = mData->mTheData(row,1)*Val;
}

template <class T>
void mtkDataProcess<T>::MultiplyFirstPointInColsBy(double Val)
{
    for(int col = 1; col < mData->CSize() + 1; col++)
        mData->mTheData(1,col) = mData->mTheData(1,col)*Val;
}

template <class T>
void mtkDataProcess<T>::ZeroFillInRowDim(int newRowSize)
{
      if(newRowSize > mData->RSize())
    {
        mData->ResizeRowDim(newRowSize);
        mData->GetRowAxis()->Resize(newRowSize);
        mData->GetRowAxis()->Update();
      }
}

template <class T>
void mtkDataProcess<T>::ZeroFillInRowDim()
{
//      if(mData->mProcPar.ZeroFillInRowDim>mTheData->RSize())
//    {
//        mData->ResizeRowDim(mData->mProcPar.ZeroFillInRowDim);
//        mData->GetRowAxis()->Resize(mData->mProcPar.ZeroFillInRowDim);
//        mData->GetRowAxis()->Update();
//      }
}

template <class T>
void mtkDataProcess<T>::ZeroFillInColDim(int newColSize)
{
      if(newColSize > mData->CSize())
    {
        mData->ResizeColDim(newColSize);
        mData->GetColAxis()->Resize(newColSize);
        mData->GetColAxis()->Update();
      }
}

template <class T>
void mtkDataProcess<T>::ZeroFillInColDim()
{
      /*** Means that we have to change the size in the Col Dimension ***/
      if(mData->mProcPar.mColDimProc->ZeroFill > mData->CSize())
    {
//        mData->ResizeColDim(mData->mProcPar.ZeroFillInColDim);
//        mData->GetColAxis()->Resize(mData->mProcPar.ZeroFillInColDim);
//        mData->GetColAxis()->Update();
      }
}

template <class T>
T mtkDataProcess<T>::GetMax()
{
      /*** This routine finds the maximum absolute value in the
      whole mTheData-matrix.  ***/
      T max,temp;

      if(mData->RSize() && mData->CSize())
      {
        max = mData->mTheData(1, 1);
      }

    //  long index;
      for(int Row = 1; Row < mData->RSize() + 1; Row++)
      {
        for(int Col = 1; Col < mData->CSize() + 1; Col++)
        {
              temp = mData->mTheData(Row,Col);
            if(fabs(real(temp)) > fabs(real(max)))
            {
                max = temp;
                //index = Col;
            }
        }
      }
      return max;
}

template <class T>
T mtkDataProcess<T>::GetMin()
{
      /*** This routine finds the maximum absolute value in the
      whole mTheData-matrix.  ***/
      T min,temp;

      if(mData->RSize() && mData->CSize())
      {
        min = mData->mTheData(1, 1);
      }

    //  long index;
      for(int Row = 1; Row < mData->RSize() + 1; Row++)
      {
        for(int Col = 1; Col < mData->CSize() + 1; Col++)
        {
              temp = mData->mTheData(Row,Col);
            if(fabs(real(temp)) < fabs(real(min)))
            {
                min = temp;
            }
        }
      }
      return min;
}

template <class T>
pair<int, T> mtkDataProcess<T>::GetMaxValue()
{
      /*** This routine finds the maximum absolute value in the
      whole mTheData-matrix.  ***/
    pair<long, T> val;
    T max,temp;

    if(mData->RSize() && mData->CSize())
    {
        val.second = mData->mTheData(1, 1);
        val.first = 1;
    }

    for(int Row = 1; Row < mData->RSize() + 1; Row++)
    {
        for(int Col = 1; Col < mData->CSize() + 1; Col++)
        {
              temp = mData->mTheData(Row,Col);
            if(fabs(real(temp)) > fabs(real(val.second)))
            {
                val.second = temp;
                val.first = Col;
            }
        }
    }
    return val;
}

template <class T>
T mtkDataProcess<T>::GetMean()
{
  /*** This routine calculates the mean of all mTheData in the whole matrix  ***/
  T mean = 0;

    for(int Row = 1; Row < mData->RSize() + 1; Row++)
      {
        for(int Col = 1; Col < mData->CSize() + 1; Col++)
        {
              mean += mData->mTheData(Row,Col);
        }
      }

      mean = real(mean) /( mData->RSize() * mData->CSize());
      return mean;
}

template <class T>
T mtkDataProcess<T>::GetMaxValue(int rStart, int cStart)
{
      /*** This routine finds the maximum absolute value in the
      whole mTheData-matrix.  ***/
      T max = 0;
      T temp = 0;
      if(mData->RSize() && mData->CSize())
      {
        max = mData->mTheData(1, 1);
      }

      for(int Row = rStart; Row < mData->RSize() + 1; Row++)
      {
        for(int Col = cStart; Col < mData->CSize() + 1; Col++)
        {
              temp = mData->mTheData(Row,Col);
              if(fabs(real(temp)) > fabs(real(max)))
                max = temp;
        }
      }
      return max;
}


template <class T>
bool mtkDataProcess<T>::NormalizeData()
{
    /*** This routine finds the maximum absolute value in the
          whole mTheData-matrix. Every entry in the daa-matrix is then
          divided by this number. Making the maximum point being 1
    ***/
    T NORM, max = 0, temp;
    for(int Row = 1;Row < mData->RSize() + 1;Row++)
    {
        for(int Col = 1;Col < mData->CSize() + 1;Col++)
        {
            temp=mData->mTheData(Row,Col);
            if(abs(temp) > abs(max))
                max=temp;
        }
    }

    NORM = std::fabs( (double) real(max));
    for(int Row = 1; Row < mData->RSize() + 1; Row++)
    {
        for(int Col = 1; Col < mData->CSize() + 1; Col++)
        {
             mData->mTheData(Row,Col) = mData->mTheData(Row,Col)/NORM;
        }
    }
    return true;
}

template <class T>
T mtkDataProcess<T>::Normalize()
{
    /*** This routine finds the maximum absolute value in the
          whole mTheData-matrix. Every entry in the mTheData-matrix is then
          divided by this number. Making the maximum point being 1 ***/
    T max = 0, temp;
//    max = GetMaxValue();
//    if(fabs(real(max)))
//    {
//        mData->SetNorm(fabs(real(max)));
//        for(int Row = 1;Row < mData->RSize() + 1;Row++)
//        {
//            for(int Col = 1;Col < mData->CSize() + 1;Col++)
//            {
//                mData->Element(Row,Col)= mData->Element(Row,Col)/mData->GetNorm();
//            }
//        }
//
//        mData->GetColProcessProperties()->NormalizationFactor = fabs(real(mData->GetNorm()));
//        mData->GetColProcessProperties()->NormalizationFactor->Applied();
//    }
      return max;
}

template <class T>
bool mtkDataProcess<T>::Normalize(const double &NORM)
{
    /*** This routine divide each entry in the datamatrix with the
         input value of NORM
    ***/

    if(NORM == 0)
    {
        Log(lError)<<("Can't normalize mTheData by zero...");
        return false;
    }

    T Norm;
    Norm = NORM;
    for(int Row = 1;Row < mData->RSize() + 1;Row++)
    {
        for(int Col = 1;Col < mData->CSize() + 1;Col++)
        {
            mData->mTheData(Row,Col)= mData->mTheData(Row,Col)/Norm;
        }
    }

    mData->GetColProcessProperties()->NormalizationFactor = fabs(real(mData->GetNorm()));
    mData->GetColProcessProperties()->NormalizationFactor->Applied();
    return true;
}

template <class T>
bool mtkDataProcess<T>::NormalizeRows()
{
    /*** This routine finds the maximum absolute value in each row in the
         whole mTheData-matrix. Every mTheData-entry, in each specific row
         is then divided by this number. Making the maximum point in each row
         being equal to 1
    ***/

    T NORM,max=0,temp;
    for(int Row = 1; Row < mData->RSize() + 1; Row++)
    {
        for(int Col = 1; Col < mData->CSize() + 1; Col++)
        {
            temp = mData->mTheData(Row,Col);
            if(abs(temp) > abs(max)) max=temp;
        }

        NORM = abs(max);
        for(int Col = 1; Col < mData->CSize() + 1; Col++)
        {
            mData->mTheData(Row,Col)= mData->mTheData(Row,Col)/NORM;
        }
        mData->GetColProcessProperties()->NormalizationFactor = fabs(real(mData->GetNorm()));
        mData->GetColProcessProperties()->NormalizationFactor->Applied();
    }
    return true;
}

template <class T>
void mtkDataProcess<T>::Transpose()
{
    mData->Transpose();
    //Exchange axes
    mtkAxes temp(*(mData->GetRowAxis()));
    *mData->GetRowAxis() = *mData->GetColAxis();
    *mData->GetColAxis() = temp;
}

template<class T>
void mtkDataProcess< T >::ExtractProjections()
{
    ExtractRowProjection();
    ExtractColProjection();
}

//------------------------------- SPECIALIZATIONS
template <> inline
mtkDataProcess< complex<double> >::mtkDataProcess(mtkData< complex<double> > *data)
:
mData(data)
{}

template<> inline
void mtkDataProcess< complex<double> >::PhasingFirstOrder(double Offset, double Phase)
{
    complex<double>  I(0,1);
      for(int Row = 1; Row < mData->RSize() + 1; Row++)
    {
        for(int Col = 1; Col < mData->CSize() + 1; Col++)
        {
              if(Offset == 0)
            {
                mData->mTheData(Row,Col) = mData->mTheData(Row,Col)*std::exp(-I*(1. - mData->GetColAxis()->Element(Col)/10)*Phase);
            }
              else
            {
                mData->mTheData(Row,Col) = mData->mTheData(Row,Col)*std::exp(-I*(1. - mData->GetColAxis()->Element(Col)/Offset)*Phase);
            }
        }
    }
}

template<> inline
void mtkDataProcess< complex<double> >::PhaseData(const mtkPhasing& phaseParameters)
{
      complex<double>  I(0,1);
    if(phaseParameters.GetZeroOrderPhase())
    {
        //    double change = PhasePara->GetZeroOrderPhase() - Phase0SB->Position;
        //    PhasePara->GetZeroOrderPhase() = Phase0SB->Position;
        //    mData->Process->MultiplyBy(exp(-I*toRad(change)) );
        //    mData->Process->MultiplyBy(exp(-I*toRad(phaseParameters.GetZeroOrderPhase())) );
      }

      if(phaseParameters.GetFirstOrderPhase())
    {
        PhasingFirstOrder(phaseParameters.GetFirstOrderPhaseOffset(), phaseParameters.GetFirstOrderPhase());
    }
}

template<> inline
void mtkDataProcess< complex<double> >::DCOffsetCorrection()
{
    //Take the average of the last 5% of the fid.. and shift the whole fid with (-)that number
      //double realAverage, imagAverage;
      complex<double> temp = 0;

      double startAt = mData->CSize()*0.75;//based on 8% of the FID
      int NrOfPoints;
      for(int Row = 1; Row < mData->RSize() + 1; Row++)
    {
        NrOfPoints = 0;
        for(int Col = (int) startAt; Col < mData->CSize() + 1; Col++)
        {
              temp += mData->mTheData(Row,Col);
              NrOfPoints++;
        }
        temp = temp/(double) NrOfPoints;
        temp = temp * (-1.0);
        for(int Col = 1; Col < mData->CSize() + 1; Col++)
        {
              mData->mTheData(Row,Col) = mData->mTheData(Row,Col) + temp;
        }
        temp = 0;
      }
}

template<> inline
void mtkDataProcess< complex<double> >::DCOffsetCorrection(double lLimit, double rLimit)
{
    //Take the average of points between the limits
      complex<double> temp = 0;

      //Find at which index in the array these values are
      int startAt = mData->GetColAxis()->GetAxisIndexAtAxisValue(lLimit);
      int endAt = mData->GetColAxis()->GetAxisIndexAtAxisValue(rLimit);

      int NrOfPoints;
      for(int Row = 1; Row < mData->RSize() + 1; Row++)
    {
        NrOfPoints = 0;
        for(int Col = startAt; Col < endAt + 1; Col++)
        {
              temp += mData->mTheData(Row,Col);
              NrOfPoints++;
        }
        temp = temp/(double) NrOfPoints;
        temp = temp * (-1.0);
        for(int Col = 1; Col < mData->CSize() + 1; Col++)
        {
              mData->mTheData(Row,Col) = mData->mTheData(Row,Col) + temp;
        }
        temp = 0;
      }
}

template<> inline
void mtkDataProcess< complex<double> >::ExtractRowProjection()
{
      //Extract the full row projection
      for(int i = 1; i < mData->RSize() + 1; i++)
        for(int j = 1; j < mData->CSize() + 1; j++)
              mData->GetRowProjection()->mTheData(1,j) += mData->mTheData(i,j);
}

template<> inline
void mtkDataProcess< complex<double> >::ExtractRowProjection(const mtkVector<int> *vec)
{
      //Extract projection slices from vector
      mData->GetRowProjection()->ZeroAll();
      int sliceNr = 1;
      for(int i = 1; i < vec->Size() + 1; i++, sliceNr++)
        for(int j = 1; j < mData->RSize() + 1; j++)
              mData->GetRowProjection()->mTheData(1,j) += mData->mTheData(j, vec->Element(sliceNr));
}

template<> inline
void mtkDataProcess< complex<double> >::ExtractRowProjection(int start, int end, int incr)
{
      //Extract the full row projection
      int End = end;
      if(End > mData->CSize())
        End = mData->CSize();

    for(int i = start; i < End + 1; i+= incr)
        for(int j = 1; j < end + 1; j++)
              mData->GetRowProjection()->mTheData(1,j) += mData->mTheData(i,j);
}

template<> inline
void mtkDataProcess< complex<double> >::ExtractColProjection()
{}

template<> inline
void mtkDataProcess< complex<double> >::ExtractColProjection(const mtkVector<int> *vec)
{
      //Extract projection slices from vector
      int sliceNr = 1;
      mData->GetColProjection()->ZeroAll();

      for(int i = 1; i < vec->Size() + 1; i++, sliceNr++)
        for(int j = 1; j < mData->CSize() + 1; j++)
              mData->GetColProjection()->mTheData(1,j) += mData->mTheData(vec->Element(sliceNr), j);
}

template<> inline
void mtkDataProcess< complex<double> >::ExtractColProjection(int start, int end, int incr)
{}

template<> inline
void mtkDataProcess< complex<double> >::InterPolateNPointsInIntervallInRow(int nrOfNewPts, double from, double to, int row)
{
    //nrOfNewPts is the number of new mTheData points in each segment, where a segment is the space between
    //two original mTheData points
    //This function do linear interpolation between the points defined by from and to in mTheData row 'row'

    //Find the indexes for witch the from and to correspond to
    int fromIndex = mData->GetColAxis()->GetAxisIndexAtAxisValue(from);
    int toIndex = mData->GetColAxis()->GetAxisIndexAtAxisValue(to);

    if(fromIndex >= toIndex)
    {
        return;
    }

    //Number of datapoints in intervall
    const int nDataP = toIndex - fromIndex + 1;
    const int nrOfSegments = nDataP - 1;

    //Increase datasize to account for new, interpolated points.
    int oldRowSize = mData->RSize();
    int oldColSize = mData->CSize();
    int newColSize = oldColSize + nrOfSegments*nrOfNewPts;

    //Copy original mTheData
    mtkData< complex<double> > origData(1, oldColSize);
    for(int i = 1; i < oldColSize + 1; i++)
    {
        origData.Element(1, i) = mData->Element(row, i);
        origData.GetColAxis()->SetElement(i) = mData->GetColAxis()->Element(i);
    }

    //Interpolate N points between two points in the range.. copy the mTheData to a tempDSLObject first..
    mtkData< complex<double> > tempData(1,nDataP);
    int fIndex = fromIndex;
    for(int i = 1; i < nDataP + 1; i++)
    {
        tempData(1, i)                             = origData.Element(row, fIndex);
        tempData.GetColAxis()->SetElement(i)     = origData.GetColAxis()->Element(fIndex++);
    }

    mtkDataProcess< complex<double> > temp_process(&tempData);
    temp_process.InterPolateNPointsInRow(nrOfNewPts);

    mData->Resize(oldRowSize, newColSize);
    //insert the mTheData in the range
    for(int index = fromIndex, tempIndex = 1; index < (fromIndex + tempData.CSize()); index++, tempIndex++)
    {
        mData->Element(row, index) = tempData.Element(1, tempIndex);
        mData->GetColAxis()->SetElement(index) = tempData.GetColAxis()->Element(tempIndex);
    }

    //Copy last part of mTheData back
    for(int i = fromIndex + tempData.CSize(), j = toIndex + 1 ; i < newColSize + 1; i++, j++)
    {
        mData->Element(row, i) = origData.Element(1, j);
        mData->GetColAxis()->SetElement(i) = origData.GetColAxis()->Element(j);
    }

    mData->IsModified(true);
}

template<> inline
void mtkDataProcess< complex<double> >::Shift(int rowNr, int shiftNrOfPts)
{
    //This shifts the mTheData in rows, leaving the mTheData axis untouched
    //The shift is specified by pts. If pts = -2, the mTheData is left shifted by 2 pts, if + 2
    //the mTheData is right shifted by 2 points

    int shiftPts = shiftNrOfPts;

    //make a tempvector with the same column size as the mTheData
    mtkData< complex<double> > tempData(1, mData->CSize());

    //Copy shiftPts into tempData
    if(shiftPts > 0)
    {
        //Positive shift
        for(int j = 1, i = mData->CSize() - shiftPts + 1; i < mData->CSize() + 1; i++, j++)
        {
              tempData(1, j) = mData->Element(rowNr, i);
        }


        for(int colPtn = 1; colPtn < mData->CSize() - shiftPts + 1; colPtn++)
        {
              tempData(1, colPtn + shiftPts) = mData->Element(rowNr, colPtn);
        }

        for(int colPtn = 1; colPtn < mData->CSize() + 1; colPtn++)
        {
              mData->mTheData(rowNr, colPtn) = tempData.Element(1, colPtn);
        }
    }
    else
    {
        //negative shift
        shiftPts *= (-1); //Change sign
        for(int j = mData->CSize() - shiftPts + 1, i = 1; j < mData->CSize() + 1; i++, j++)
        {
              tempData(1, j) = mData->Element(rowNr, i);
        }

        for(int colPtn = 1; colPtn < mData->CSize() - shiftPts + 1; colPtn++)
        {
              tempData(1, colPtn) = mData->Element(rowNr, colPtn + shiftPts);
        }

        for(int colPtn = 1; colPtn < mData->CSize() + 1; colPtn++)
        {
              mData->mTheData(rowNr, colPtn) = tempData.Element(1, colPtn);
        }
    }

    mData->GetRowProcessProperties()->LeftShift += shiftPts;
    mData->GetRowProcessProperties()->LeftShift->Applied();
}

template<> inline
void mtkDataProcess< complex<double> >::fftAlongRows()
{
    mtkVector<double> temp(1,2* (mData->CSize()) );

    /*** Make a loop over rows ***/
      for(int row = 1; row < mData->RSize() + 1; row++)
      {
        cpx_to_real(mData->mTheData[row], temp, mData->CSize());
        mtkfour1(temp, mData->CSize(),+1);/*** NR function ***/
        real_to_cpx(temp, mData->mTheData[row], mData->CSize());
        swap1(mData->mTheData[row], mData->CSize());
        swap2(mData->mTheData[row], mData->CSize());
        swap3(mData->mTheData[row], mData->CSize());
      }
      //Construct corresponding axis
      double incr = mData->GetColAxis()->GetIncrement();
      mData->GetColAxis()->SetAxis(-1/(2*incr), 1./(mData->CSize()*incr));
}

template<> inline
void mtkDataProcess< complex<double> >::fftAlongRow(int row)
{
      mtkVector<double> temp(1,2* (mData->CSize()) );
    cpx_to_real( mData->mTheData[row], temp, mData->CSize());
    mtkfour1(temp, mData->CSize(),+1);/*** NR function ***/
    real_to_cpx(temp, mData->mTheData[row], mData->CSize());
    swap1(mData->mTheData[row], mData->CSize());
    swap2(mData->mTheData[row], mData->CSize());
    swap3(mData->mTheData[row], mData->CSize());

      //Construct corresponding axis
      double incr = mData->GetColAxis()->GetIncrement();
      mData->GetColAxis()->SetAxis(-1/(2*incr), 1./(mData->CSize()*incr));
}

template<> inline
bool mtkDataProcess< complex<double> >::MagnitudeInRow(int row)
{
    for(int col = 1; col < mData->CSize() + 1; col++)
    {
        double val =  real(mData->mTheData(row,col))*real(mData->mTheData(row,col)) + imag(mData->mTheData(row,col))*imag(mData->mTheData(row,col));
        if(val > 0)
        {
            mData->mTheData(row,col) = sqrt(val);
        }
        else
        {
            mData->mTheData(row,col) = 0;
        }
    }

    return true;
}

template<> inline
void mtkDataProcess< complex<double> >::CMXfftAlongRows()
{
    /*** The Axis created in this routine is reversed compared to previous routine ***/

      mtkVector<double> temp(1,2* (mData->CSize()));
    /*** Make a loop over rows ***/
      for(int row = 1; row < mData->RSize() + 1; row++)
    {
        cpx_to_real(mData->mTheData[row], temp, mData->CSize());
        mtkfour1(temp, mData->CSize(), +1);/*** NR function ***/
        real_to_cpx(temp, mData->mTheData[row], mData->CSize());
        swap1(mData->mTheData[row], mData->CSize());
        swap3(mData->mTheData[row], mData->CSize());
      }
      //Construct corresponding axis
      double incr = mData->GetColAxis()->GetIncrement();
      mData->GetColAxis()->SetAxis(-1/(2*incr), 1./(mData->CSize()*incr));
}

template<> inline
void mtkDataProcess< complex<double> >::NRfftInT2Dim()
{
      mtkVector<double> temp(1,2*mData->CSize());
      /*** Make a loop over rows ***/
      for(int row = 1;row < mData->RSize()+1;row++)
    {
        cpx_to_real(mData->mTheData[row],temp, mData->CSize());
        mtkfour1(temp, mData->CSize(),+1);/*** NR function ***/
        real_to_cpx(temp, mData->mTheData[row], mData->CSize());
      }
}

template<> inline
void mtkDataProcess< complex<double> >::IfftInT2Dim()
{
    mtkVector<double> temp(1,2*mData->CSize());
      /*** Make a loop over rows ***/
      for(int row = 1; row < mData->RSize() + 1; row++)
      {
        undo_swap3(mData->mTheData[row], mData->CSize());
        undo_swap2(mData->mTheData[row], mData->CSize());
        undo_swap1(mData->mTheData[row], mData->CSize());
        cpx_to_real(mData->mTheData[row],temp, mData->CSize());

        mtkfour1(temp, mData->CSize(),-1);/*** NR function ***/
        real_to_cpx(temp, mData->mTheData[row], mData->CSize());
      }
      //Multiply each point by 1/(Number of complex points)
    mtkDataProcess temp_process(mData);

      temp_process.MultiplyBy(double(1./double(mData->CSize())));

      //Construct corresponding axis
    //double incr = mData->AxisRowDim.GetIncrement();
    //mTheData->AxisOffset_row_dim = -1/(2*incr);
    //mTheData->AxisRowDim.SetIncrement(mData->AxisOffset_row_dim);
    //
    //double elem = mData->AxisOffset_row_dim;
    //for(int i=1;i<mTheData->CSize() +1;i++)
    //{
    //     mData->AxisRowDim[i]=elem;
    //     elem+=1./(mData->CSize()*incr);
    //}
}

template<> inline
void mtkDataProcess< complex<double> >::NRIfftInT2Dim()
{
    mtkVector<double> temp(1,2*mData->CSize());
      /*** Make a loop over rows ***/
      for(int row = 1;row < mData->RSize()+1;row++)
    {
        cpx_to_real(mData->mTheData[row],temp, mData->CSize());
        mtkfour1(temp, mData->CSize(),-1);/*** NR function ***/
        real_to_cpx(temp, mData->mTheData[row], mData->CSize());
      }

      //Multiply each point by 1/(Number of complex points)
    mtkDataProcess tempProc(mData);
      tempProc.MultiplyBy(double(1./double(mData->CSize())));
}

template<> inline
void mtkDataProcess< complex<double> >::fftAlongCols()
{

       mData->mTheData.Transpose();
       int tmp = mData->RSize();
       mData->SetRowDimSize(mData->CSize());
       mData->SetColDimSize(tmp);

      mtkVector<double> temp(1,2*mData->CSize());

      /*** Make a loop over rows, which are our old cols! ***/
      for(int row = 1;row < mData->RSize()+1;row++)
    {
        cpx_to_real(mData->mTheData[row],temp, mData->CSize());
        mtkfour1(temp, mData->CSize(),+1);/*** NR function ***/
        real_to_cpx(temp, mData->mTheData[row], mData->CSize());
        swap1(mData->mTheData[row], mData->CSize());
        swap2(mData->mTheData[row], mData->CSize());
        swap3(mData->mTheData[row], mData->CSize());
      }
      mData->mTheData.Transpose();
      tmp = mData->RSize();
      mData->SetRowDimSize(mData->CSize());
      mData->SetColDimSize(tmp);

      //Construct corresponding axis
      double incr = mData->GetRowAxis()->GetIncrement();
      mData->GetRowAxis()->SetAxis(-1/(2*incr), 1./(mData->RSize()*incr));
}

template<> inline
void mtkDataProcess< complex<double> >::CosfftAlongCols()
{
    int row,col;
    fftAlongCols();  //Not so nice should have a "Pure" Cos transform
    mtkMatrix< complex<double> > tempMat(mData->RSize(), mData->CSize());

    for(row = 1; row < mData->RSize() + 1; row++)
        for(col = 1; col < mData->CSize() + 1; col++)
              tempMat(row,col) = mData->mTheData(row, col);

    tempMat.Transpose();
    //Swap Rows
    for(row=1;row<tempMat.GetRowSize();row++)
        swap2(tempMat[row], tempMat.GetColSize());

    tempMat.Transpose();

    for(row=1;row < mData->RSize()+1;row++)
        for(col=1;col < mData->CSize()+1;col++)
              mData->mTheData(row,col) = mData->mTheData(row,col) + tempMat(row,col);
}

template<> inline
void mtkDataProcess< complex<double> >::NRfftInT1Dim()
{
    /*** This routine makes the NR fft ***/
      mData->mTheData.Transpose();
      int tmp = mData->RSize();
      mData->SetRowDimSize( mData->CSize() );
      mData->SetColDimSize( tmp );

      mtkVector<double> temp(1,2*mData->CSize());

      /*** Make a loop over rows, which are our old cols! ***/
      for(int row = 1;row < mData->RSize()+1;row++)
    {
        cpx_to_real(mData->mTheData[row],temp, mData->CSize());
        mtkfour1(temp, mData->CSize(),+1);/*** NR function ***/
        real_to_cpx(temp, mData->mTheData[row], mData->CSize());
      }
      mData->mTheData.Transpose();
      tmp = mData->RSize();
      mData->SetRowDimSize(mData->CSize());
      mData->SetColDimSize(tmp);
}

template<> inline
void mtkDataProcess< complex<double> >::IfftInT1Dim()
{
    mData->mTheData.Transpose();
    int tmp = mData->RSize();
    mData->SetRowDimSize( mData->CSize());
    mData->SetColDimSize(tmp);

    mtkVector<double> temp(1,2*mData->CSize());
    /*** Make a loop over rows ***/
    for(int row = 1;row < mData->RSize()+1;row++)
    {
         undo_swap3(mData->mTheData[row], mData->CSize());
         undo_swap2(mData->mTheData[row], mData->CSize());
         undo_swap1(mData->mTheData[row], mData->CSize());
         cpx_to_real(mData->mTheData[row],temp, mData->CSize());

         mtkfour1(temp, mData->CSize(),-1);/*** NR function ***/
         real_to_cpx(temp, mData->mTheData[row], mData->CSize());
    }
    //Multiply each point by 1/(Number of complex points)
    mtkDataProcess tempProc(mData);
    tempProc.MultiplyBy(double(1./double(mData->CSize())));
    mData->mTheData.Transpose();
    tmp = mData->RSize();
    mData->SetRowDimSize( mData->CSize() ) ;
    mData->SetColDimSize(tmp);
}

template<> inline
void mtkDataProcess< complex<double> >::NRIfftInT1Dim()
{
    mData->mTheData.Transpose();
    int tmp = mData->RSize();
    mData->SetRowDimSize( mData->CSize());
    mData->SetColDimSize( tmp);

    mtkVector<double> temp(1,2*mData->CSize());
    /*** Make a loop over rows ***/
    for(int row = 1;row < mData->RSize()+1;row++)
    {
        cpx_to_real(mData->mTheData[row],temp, mData->CSize());

         mtkfour1(temp, mData->CSize(),-1);/*** NR function ***/
        real_to_cpx(temp, mData->mTheData[row], mData->CSize());
    }
    //Multiply each point by 1/(Number of complex points)
    mtkDataProcess tempProc(mData);
    tempProc.MultiplyBy(double(1./double(mData->CSize())));

    mData->mTheData.Transpose();
    tmp = mData->RSize();
    mData->SetRowDimSize(mData->CSize());
    mData->SetColDimSize(tmp);
}

template<> inline
void mtkDataProcess< complex<double> >::CosTransformInT1Dim()
{
    int row,col;
      fftAlongCols();  //Not so nice should have a "Pure" Cos transform
      mtkMatrix< complex<double> > tempMat(mData->RSize(), mData->CSize());

      for(row=1;row < mData->RSize() +1;row++)
           for(col=1 ;col < mData->CSize() +1;col++)
              tempMat(row,col) = mData->mTheData(row,col);

      tempMat.Transpose();
      //Swap Rows
      for(row=1;row<tempMat.GetRowSize();row++)
        swap2(tempMat[row],tempMat.GetColSize());

    tempMat.Transpose();

       for(row=1;row < mData->RSize()+1;row++)
        for(col=1;col < mData->CSize()+1;col++)
          mData->mTheData(row,col) = mData->mTheData(row,col)+tempMat(row,col);
}

template<> inline
void mtkDataProcess< complex<double> >::CosTransformInT2Dim()
{
//      //Write code for this!!
//      fftAlongRows();
//
//      complex<double>  temp(0,0);
//      int n=mTheData->mTheData.Size();/*** Length of array ***/
//      for(int i=1; i<(n/2)+1;i++)
//    {
//        temp=mTheData->mTheData[1][i];
//        mData->mTheData[1][i]=mTheData->mTheData[1][n+1-i];
//        mData->mTheData[1][n+1-i]=temp;
//      }
}

}
#endif
