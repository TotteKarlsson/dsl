#pragma hdrstop
#include <cmath>
#include "dslMathUtils.h"
#include "dslCellParameters.h"


namespace dsl
{
CellParameters::CellParameters(double aAxes, double bAxes, double cAxes, double betaAngle)
{
    a = aAxes;  b = bAxes;  c = cAxes;  beta = toRadians(betaAngle);
}

void CellParameters::set_abcBeta(double aAxes, double bAxes, double cAxes, double betaAngle)
{
    a = aAxes;  b = bAxes;  c = cAxes;  beta = toRadians(betaAngle);
}

dslMatrix<double> CellParameters::getTranformationMatrix() const
{
    dslMatrix<double> T(3,3);
    T(1,1) = a*sin(beta);
    T(2,2) = b;
    T(3,3) = c;
    T(3,1) = a*cos(beta);
    return T;
}

}
