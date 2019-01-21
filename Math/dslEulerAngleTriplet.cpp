#pragma hdrstop
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "dslEulerAngleTriplet.h"
#include "dslUtils.h"
#include "dslMathUtils.h"

using namespace std;

namespace dsl
{

EulerAngleTriplet::EulerAngleTriplet(double a, double b, double g, double w)
{
    mAlpha = a;
    mBeta = b;
    mGamma = g;
    mWeight = w;
}

EulerAngleTriplet::~EulerAngleTriplet()
{}

EulerAngleTriplet::EulerAngleTriplet(const EulerAngleTriplet& e)
{
    mAlpha = e.getAlpha();
    mBeta = e.getBeta();
    mGamma = e.getGamma();
    mWeight = e.getWeight();
}

EulerAngleTriplet& EulerAngleTriplet::operator = (const EulerAngleTriplet& e)
{
    mAlpha = e.getAlpha();
    mBeta = e.getBeta();
    mGamma = e.getGamma();
    mWeight = e.getWeight();
    return *this;
}

void EulerAngleTriplet::setAlpha(double Alpha)
{
    mAlpha = Alpha;
}

double EulerAngleTriplet::getAlpha() const
{
    return mAlpha;
}

double& EulerAngleTriplet::getAlphaRef()
{
    return mAlpha;
}

void EulerAngleTriplet::setBeta(double Beta)
{
    mBeta = Beta;
}

double EulerAngleTriplet::getBeta() const
{
    return mBeta;
}

double& EulerAngleTriplet::getBetaRef()
{
    return mBeta;
}

void EulerAngleTriplet::setGamma(double Gamma)
{
    mGamma=Gamma;
}

double EulerAngleTriplet::getGamma() const
{
    return mGamma;
}

double& EulerAngleTriplet::getGammaRef()
{
    return mGamma;
}

void EulerAngleTriplet::setWeight(double Weight)
{
    mWeight = Weight;
}

double  EulerAngleTriplet::getWeight() const
{
    return mWeight;
}

double& EulerAngleTriplet::getWeightRef()
{
    return mWeight;
}


void EulerAngleTriplet::set(double X, double Y, double Z)
{
    mAlpha = X;
    mBeta = Y;
    mGamma = Z;
}

void EulerAngleTriplet::set(double X, double Y, double Z, double Weight)
{
    mAlpha = X;
    mBeta = Y;
    mGamma = Z;
    mWeight = Weight;
}

void EulerAngleTriplet::set(const EulerAngleTriplet &angle)
{
    mAlpha = angle.getAlpha();
    mBeta = angle.getBeta();
    mGamma = angle.getGamma();
    mWeight = angle.getWeight();
}

void EulerAngleTriplet::zero()
{
    mAlpha = mBeta = mGamma = 0;
}

EulerAngleTriplet& EulerAngleTriplet::convertToRadians()
{
    mAlpha   = dsl::toRadians(mAlpha);
    mBeta   = dsl::toRadians(mBeta);
    mGamma  = dsl::toRadians(mGamma);
    return *this;
}

EulerAngleTriplet& EulerAngleTriplet::convertToDegree()
{
    mAlpha   = dsl::toDegree(mAlpha);
    mBeta   = dsl::toDegree(mBeta);
    mGamma  = dsl::toDegree(mGamma);
    return *this;
}

std::ostream& operator<<(std::ostream &str, const EulerAngleTriplet &out)
{
    str <<"("<<out.getAlpha()<<","<<out.getBeta()<<","<<out.getGamma()<<","<<out.getWeight()<<")";
    return str;
}


}
