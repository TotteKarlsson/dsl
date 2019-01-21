#pragma hdrstop
#include "dslRandom.h"
//---------------------------------------------------------------------------
namespace dsl
{

Random::Random(double min, double max, int seed)
:
mMin(min),
mMax(max)
{
    MTRand_int32 irand(seed);
}

double Random::NextDouble() const
{
    return mRand()*(mMax - mMin) + mMin;;
}

double Random::NextDouble(double min, double max) const
{
    return mRand()*(max-min) + min;
}
}

