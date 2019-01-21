#pragma hdrstop
#include "dslShowDataPart.h"
//---------------------------------------------------------------------------

namespace dsl
{
dslShowDataPart::dslShowDataPart(int i )
: bitset<5>(i)
{
    //bit 0 - real
    //bit 1 - imag
    //bit 2 - mag
    //bit 3 - all
}

dslShowDataPart::dslShowDataPart(const dslShowDataPart& rhs)
{
    *this = rhs;
}

}
