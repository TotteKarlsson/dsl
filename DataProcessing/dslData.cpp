
#pragma hdrstop
#include "dslMathUtils.h"
#include "dslData.h"

namespace dsl
{

template class dslData<double>;
template class dslData< complex<double> >;


ostream& operator<<(ostream& stream, const dslComplexData& mat)
{
    for(unsigned row = 1; row < mat.RSize() + 1; row++)
    {
        for(unsigned col = 1; col < mat.CSize() + 1; col++)
        {
            complex<double> val = mat(row,col);
            stream<<val<<"\t";
        }
        stream<<"\n";
    }
    return stream;
}


template <>
void dslData< complex<double> >::FillRandom()
{
    for(int i = 1; i < RSize() + 1; i++)
    {
        for(int j = 1; j < CSize() + 1; j++)
        {
            double re = double(GetRandomNumber(0, 100000)/5.);
            double im = double(GetRandomNumber(0, 100000)/5.);
            complex<double> val = complex<double> (re, im);
              Element(i,j) = val;
            complex<double> val2 = Element(i,j);
              Element(i,j) = val;
        }
    }
}

template <>
void dslData< double >::FillRandom()
{
    for(int i = 1; i < RSize() + 1; i++)
    {
        for(int j = 1; j < CSize() + 1; j++)
        {
              Element(i,j) = double(GetRandomNumber(0, 100000)/5.);
        }
    }
}


//template <>
//bool dslData< complex<double> >::Write(const string& fName, const FILE_FORMAT& fFormat, const DATA_FORMAT& dFormat)
//{
//    return Writer->Write(fName, fFormat, dFormat);
//}
//
//



//int GetClosestPowerOfTwo(int len)
//{
//    int LEN = 16384;
//    int m;
//    if (len < 1)
//        len = 1;
//
//    if (len < LEN)
//    {
//        for (m = LEN; m >= len; m >>= 1)
//            ;
//        m <<= 1;
//    }
//    else
//    {
//        for (m = LEN; m < len; m <<= 1)
//        ;
//    }
//    return m;
//}
//
//
//#define SWAP(a,b) tempr=(a);(a)=(b);(b)=tempr
//void dslfour1(dslVector<double>& data, unsigned long nn, int isign)
//{
//    unsigned long n,mmax,m,j,istep,i;
//    double wtemp,wr,wpr,wpi,wi,theta;
//    double tempr,tempi;
//
//    n=nn << 1;
//    j=1;
//    for (i=1;i<n;i+=2) {
//        if (j > i) {
//            SWAP(data[j],data[i]);
//            SWAP(data[j+1],data[i+1]);
//        }
//        m=n >> 1;
//        while (m >= 2 && j > m) {
//            j -= m;
//            m >>= 1;
//        }
//        j += m;
//    }
//    mmax=2;
//    while (n > mmax) {
//        istep=mmax << 1;
//        theta=isign*(6.28318530717959/mmax);
//        wtemp = sin(0.5*theta);
//        wpr = -2.0*wtemp*wtemp;
//        wpi=sin(theta);
//        wr=1.0;
//        wi=0.0;
//        for (m=1;m<mmax;m+=2) {
//            for (i=m;i<=n;i+=istep) {
//                j=i+mmax;
//                tempr=wr*data[j]-wi*data[j+1];
//                tempi=wr*data[j+1]+wi*data[j];
//                data[j]=data[i]-tempr;
//                data[j+1]=data[i+1]-tempi;
//                data[i] += tempr;
//                data[i+1] += tempi;
//            }
//            wr=(wtemp=wr)*wpr-wi*wpi+wr;
//            wi=wi*wpr+wtemp*wpi+wi;
//        }
//        mmax=istep;
//    }
//}
//#undef SWAP
//
//


}


