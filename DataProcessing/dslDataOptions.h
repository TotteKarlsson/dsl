#ifndef dslDataOptionsH
#define dslDataOptionsH
#include "dslObject.h"
#include "DataExporter.h"
#include "dslConstants.h"

namespace dsl
{

class MTK_DATA mtkDataOptions: public DSLObject
{
    public:
        mtkDataOptions();
        mtkDataOptions(const mtkDataOptions& options);
        FILE_FORMAT readType;
        FILE_FORMAT writeType;
        void Set(mtkDataOptions* opt);
};

}
#endif
