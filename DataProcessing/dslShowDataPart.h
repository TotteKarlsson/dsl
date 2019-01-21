#ifndef dslShowDataPartH
#define dslShowDataPartH
#include <bitset>
#include "DataExporter.h"
#include "dslObject.h"
//---------------------------------------------------------------------------

namespace dsl
{

using std::bitset;

class MTK_DATA mtkShowDataPart : public bitset<5> , public DSLObject
{
    public:
        mtkShowDataPart(int i = 0);
        mtkShowDataPart(const mtkShowDataPart& rhs);
};

}

#endif
