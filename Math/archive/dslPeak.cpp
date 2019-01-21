#pragma hdrstop
#include "dslPeak.h"
//---------------------------------------------------------------------------
namespace dsl
{

void Peak::setOrigin(double x, double y , double z)
{
    mOrigin.set(x,y,z);
}

void Peak::setWidth(double x, double y, double z)
{
    mWidth.set(x,y,z);
}


}
