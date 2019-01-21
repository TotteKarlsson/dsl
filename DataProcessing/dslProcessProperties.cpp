
#pragma hdrstop
#include "dslProcessProperties.h"


namespace dsl
{

dslProcessProperties::dslProcessProperties()
:
FFT(false),
ZeroFill(false),
LeftShift(false),
DCOffsetCorrection(false),
EM(false),
NormalizationFactor(false),
ProcFileName("<none>")
{}


dslProcessProperties::~dslProcessProperties()
{
}

}
