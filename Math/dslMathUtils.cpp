#pragma hdrstop
#include "dslMathUtils.h"
#include <cmath>

using namespace std;
namespace dsl
{

int round(double r)
{
	return (r > 0.0) ? (r + 0.5) : (r - 0.5);
}

bool checkForZero(double val, double small)
{
    return fabs(fabs(val) - small) <= DBL_EPSILON;
}

double toRadians(double inDeg)
{
    return inDeg*gPi/(180.);
}

double toDegree(double inRad)
{
    return inRad*180./(gPi);
}

int real(int const &Nr)
{
    return Nr;
}

double real(double const &Nr)
{
    return Nr;
}

long double real(long double const &Nr)
{
    return Nr;
}

int sign(double val)
{
    return (val < 0) ? -1 : +1;
}

int lcd(int NR1, int NR2)
{
    //This is calculating the least common denominator for 1/NR1 and 1/NR2
    //From Renate Schaaf..........
    int LCD = NR1;
      while(LCD % NR2)
    {
        LCD += NR1;
    }
      return LCD;
}

//
//
////EulerAngleTriplet* toRadians(const EulerAngleTriplet *inDeg){
////  EulerAngleTriplet *ReturnAngle = new EulerAngleTriplet(*inDeg);
////  ReturnAngle->toRadians();
////  return ReturnAngle;
////}
//
////EulerAngleTriplet* toDegree(const EulerAngleTriplet *inRad){
////  EulerAngleTriplet *ReturnAngle = new EulerAngleTriplet(*inRad);
////  ReturnAngle->toDegree();
////  return ReturnAngle;
////}
//


//int GetSatisfyingInteger(double &DeltaT, double &Time){
//    /*** This is a really ugly function ***/
//    /*** Find nearest integer (n) that satisfies DeltaT*n = Time ***/
//  double temp = 0, min = 100;
//  int Result= 0;
//  for(int n = 0; n<1000; n++){
//    temp  = fabs(n*DeltaT-Time);
//      if(temp < min ){
//        Result = n;
//        min = temp;
//      }
//  }
//  return Result;
//}
//
//
//static double dsqrarg;
//#define DSQR(a) ((dsqrarg=(a)) == 0.0 ? 0.0 : dsqrarg*dsqrarg)
//
//double dpythag(double a, double b){
//  double absa, absb;
//  absa = fabs(a);
//  absb = fabs(b);
//  if(absa > absb) return absa*sqrt(1.0+DSQR(absb/absa));
//  else return (absb == 0.0 ? 0.0 : absb*sqrt(1.0+DSQR(absa/absb)));
//}
//

//void cpx_to_real(complex<double>* in, dslVector<double>& out, int Size)
//{
//    int index_real = 1;
//
//    for(int i=1;i<Size+1;i++)
//    {
//        out[index_real]     = ::real(in[i]);
//           out[index_real + 1] = imag(in[i]);
//        index_real            += 2;
//    }
//}
//
//void real_to_cpx(dslVector<double>& in, complex<double> *out, int Size)
//{
//    int index_real = 1;
//    complex<double>  I(0,1);
//
//    for(int i = 1; i < Size + 1; i++)
//    {
//        out[i]                = in[index_real] + I*in[index_real + 1];
//        index_real             += 2;
//    }
//}
//
//void cpx_to_real(dslVector< complex<double> >& in, double *out)
//{
//    int index_real = 1;
//    int n = in.Size();
//
//    for(int i = 1; i < n + 1; i++)
//    {
//        out[index_real]        = ::real(in[i]);
//        out[index_real + 1]    = imag(in[i]);
//        index_real             += 2;
//    }
//}
//
//void real_to_cpx(double* in, dslVector< complex<double> >& out)
//{
//    int index_real = 1;
//    complex<double>  I(0,1);
//
//    for(int i = 1; i < out.Size() + 1; i++)
//    {
//           out[i]                    = in[index_real] + I*in[index_real + 1];
//        index_real             += 2;
//    }
//}

int getClosestPowerOfTwo(int len)
{
    int LEN = 16384;
    int m;
    if(len < 1)
        len = 1;

    if(len < LEN)
    {
        for(m = LEN; m >= len; m >>= 1)
            ;
        m <<= 1;
    }
    else
    {
        for(m = LEN; m < len; m <<= 1)
            ;
    }
    return m;
}


////dslVector<double> instance
//#define SWAP(a,b) tempr=(a);(a)=(b);(b)=tempr
//void dslfour1(dslVector<double>& data, unsigned long nn, int isign)
//{
//    unsigned long n,mmax,m,j,istep,i;
//    double wtemp,wr,wpr,wpi,wi,theta;
//    double tempr,tempi;
//
//    n=nn << 1;
//    j=1;
//    for (i=1;i<n;i+=2)
//    {
//        if (j > i) {
//            SWAP(data[j],data[i]);
//            SWAP(data[j+1],data[i+1]);
//        }
//        m=n >> 1;
//        while (m >= 2 && j > m)
//        {
//            j -= m;
//            m >>= 1;
//        }
//        j += m;
//    }
//    mmax=2;
//    while (n > mmax)
//    {
//        istep=mmax << 1;
//        theta=isign*(6.28318530717959/mmax);
//        wtemp = sin(0.5*theta);
//        wpr = -2.0*wtemp*wtemp;
//        wpi=sin(theta);
//        wr=1.0;
//        wi=0.0;
//        for (m=1;m<mmax;m+=2)
//        {
//            for (i=m;i<=n;i+=istep)
//            {
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

//int dslExport convertCMXNumber(int number){
//    int integer = 0;
//     integer |= (number & 0x000000ff) << 24;
//     integer |= (number & 0x0000ff00) << 8;
//     integer |= (number & 0x00ff0000) >> 8;
//     integer |= (number & 0xff000000) >> 24;
//     return integer;
//}
//
//float dslExport convertCMXNumber(float number){
//    unsigned char *Swap = (unsigned char*) &number;
//    unsigned char Dummy;
//    Dummy = Swap[0];
//    Swap[0] = Swap[3];
//    Swap[3] = Dummy;
//    Dummy = Swap[1];
//    Swap[1] = Swap[2];
//    Swap[2] = Dummy;
//    return number;
//}
//
//template <>
//void LinearInterPolateNPoints(int N, const complex<double>& P1, const complex<double>& P2, complex<double>* arr)
//{
//    //Having two points, P1 and P2, interpolate N points between and put them into the
//    //array arr.
//    //If complex points, interpolate real and imag seperately
//
//    if(!N) return;
//
//    double *reArr = new double[N];
//    double *imArr = new double[N];
//
//    LinearInterPolateNPoints(N, real(P1), real(P2), reArr);
//    LinearInterPolateNPoints(N, imag(P1), imag(P2), imArr);
//
//    //Put real and imag into the array
//    for(int i = 0; i < N; i++)
//        arr[i] = complex<double>(reArr[i], imArr[i]);
//
//    delete[] reArr;
//    delete[] imArr;
//}
//
//template <>
//void LinearInterPolateNPoints(int N, double P1, double P2, double* arr)
//{
//    //Having two points, P1 and P2, interpolate N points between and put them into the
//    //array arr.
//
//    if(!N) return;
//    double offset = P1;
//    double incr   = (P2 - P1)/ (N + 1);
//
//    //Calculate points
//    for(int i = 0; i < N; i++)
//        arr[i] = offset + (i+1)*incr;
//}
//

int GetRandomNumber(int min, int max)
{
    time_t t;
    static bool initialized;
    if(!initialized)
    {
           srand((unsigned) time(&t));
        initialized = true;
    }

    int nr = rand()%(max - min) + min;
    return nr;
}

int GetTimeRandomNumber()
{
   // char *tzstr = "TZ=PST8PDT";

   // struct timeb t;
   // putenv(tzstr);
   // tzset();
   // ::ftime(&t);
    return 42;//t.millitm;
}


double normalizeAngle(double a, int radOrDeg)
{
    double limit = (radOrDeg == 0) ? gPi : 180.0;
    return fmod(a + limit, 2.*limit) -limit;
}

}
