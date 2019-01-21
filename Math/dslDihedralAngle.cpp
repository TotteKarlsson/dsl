#pragma hdrstop
#include "dslDihedralAngle.h"
#include <cmath>
#include "dslPoint.h"
#include "dslUtils.h"
#include "dslMathUtils.h"

namespace dsl
{
using namespace std;
DihedralAngle::DihedralAngle(const Point& a1, const Point& a2, const Point& a3, const Point& a4)
{
    mPoints.push_back(a1);
    mPoints.push_back(a2);
    mPoints.push_back(a3);
    mPoints.push_back(a4);
    mTheAngle = calculate();
}

DihedralAngle::~DihedralAngle()
{}

DihedralAngle::operator double()
{
    return mTheAngle;
}

Vector3D DihedralAngle::getNormal1()
{
    return mNormal1;
}

Vector3D DihedralAngle::getNormal2()
{
    return mNormal2;
}

//Change to use calculation using atan2 instead
//See http://math.stackexchange.com/questions/47059/how-do-i-calculate-a-dihedral-angle-given-cartesian-coordinates
double DihedralAngle::calculate()
{
    Vector3D A1_A2 = mPoints[1] - mPoints[0];
    Vector3D A2_A3 = mPoints[2] - mPoints[1];
    Vector3D A3_A4 = mPoints[3] - mPoints[2];

    /*** Calculate Normal to plane formed by A1-A2-A3 ***/
    Vector3D Normal1 = A1_A2.VP(A2_A3);
    mNormal1 = Vector3D(Normal1);

    /*** Calculate Normal to plane formed by A2-A3-A4 ***/
    Vector3D Normal2 = A2_A3.VP(A3_A4);
    mNormal2 = Vector3D(Normal2);

    double theAngle(0);
    if((Normal2.getMagnitude() != 0))
    {
         double temp1 = Normal1.SP(Normal2);
         double temp2 = (Normal1.getMagnitude() * Normal2.getMagnitude());
         double temp3 = (temp2 != 0) ? temp1/temp2 : 0;

         if(std::fabs(temp3 - 1) < 0.0000000001)
         {
            theAngle = 0;
         }
         else if(std::fabs(temp3 + 1) < 0.0000000001)
         {
            theAngle = gPi;
         }
         else
         {
            theAngle = acos(temp3);
         }
    }

    //Get the correct sign..
    theAngle = theAngle * sign(A2_A3.SP(A3_A4.VP(A1_A2)));
    return toDegree(theAngle);
}

vector<Point> DihedralAngle::getPoints()
{
    return mPoints;
}

}
