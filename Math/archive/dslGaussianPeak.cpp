#pragma hdrstop
#include <math.h>
#include "dslGaussianPeak.h"
//---------------------------------------------------------------------------

namespace dsl
{

GaussianPeak::GaussianPeak(double centerX, double centerY, double amplitude, double xWidth, double yWidth)
:
Peak(Point(centerX, centerY, 0), Point(xWidth, yWidth, 0))
{}

GaussianPeak::~GaussianPeak() {}

double GaussianPeak::z(double x, double y)
{
    double x0 = mOrigin.x();
    double y0 = mOrigin.y();
    double sigmaX = mWidth.x();
    double sigmaY = mWidth.y();

    if(sigmaX && sigmaY)
    {
        double val = pow(x - x0, 2)/(2.*pow(sigmaX,2)) + pow(y - y0, 2)/(2.*pow(sigmaY,2));
        double z = mAmplitude*exp(-val);
        return z;
    }
    return 0;
}


}
