
#pragma hdrstop
#include "dslPhasing.h"


namespace dsl
{

dslPhasing::dslPhasing()
:
mZeroOrderPhase(0),
mFirstOrderPhase(0),
mFirstOrderPhaseOffset(0)
{}

void dslPhasing::Reset()
{
    mZeroOrderPhase = 0;
    mFirstOrderPhase = 0;
    mFirstOrderPhaseOffset = 0;
}

}
