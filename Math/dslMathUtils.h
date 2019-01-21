#ifndef dslMathUtilH
#define dslMathUtilH
#include "dslMathExporter.h"
#include "dslConstants.h"
//#include <complex>
#include <float.h> //Epsilon

namespace dsl
{

//using std::complex;
template <class T> class dslVector;

//enum FrameOfReference {frWorld, frLocal};

						//make sure the val being passed is positive (use fabs)
bool                    DSL_MATH checkForZero(double val, double test = DBL_EPSILON);
//void                    DSL_MATH cpx_to_real(complex<double> *in, dslVector<double>& out,int Size);
//void                    DSL_MATH cpx_to_real(dslVector< complex<double> > &in, double *temp);
//void                    DSL_MATH real_to_cpx(dslVector<double>& in, complex<double>  *out, int Size);
//void                    DSL_MATH real_to_cpx(double *in, dslVector< complex<double> > &out);
int                     DSL_MATH getClosestPowerOfTwo(int len);
void                    DSL_MATH dslfour1(dslVector<double>& data, unsigned long nn, int isign);

double                  DSL_MATH toRadians(double inDeg);
double                  DSL_MATH toDegree(double inRad);

int                     DSL_MATH lcd(int NR1, int NR2);
int                     DSL_MATH round(double roundthis);

int                     DSL_MATH real(const int &Nr);
double                  DSL_MATH real(const double &Nr);
long double             DSL_MATH real(const long double &Nr);
int                     DSL_MATH sign(double val);

//double                DSL_MATH dpythag(double a, double b);
//int                   DSL_MATH GetSatisfyingInteger(double& DeltaT, double& Time);

//CMX
//int                   DSL_MATH convertCMXNumber(int number);
//float                 DSL_MATH convertCMXNumber(float number);

template <class T>
void                    DSL_MATH LinearInterPolateNPoints(int N, const T& P1, const T& p2, T* arr);
int                     DSL_MATH GetRandomNumber(int min, int max);
int                     DSL_MATH GetTimeRandomNumber();

double                  DSL_MATH normalizeAngle(double a, int radOrDeg = 0);

}
#endif
