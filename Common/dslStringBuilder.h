#ifndef dslStringBuilderH
#define dslStringBuilderH
#include <string>
#include "dslObject.h"
#include "dslCommonExporter.h"
//---------------------------------------------------------------------------

namespace dsl
{

using std::string;
class DSL_COMMON StringBuilder : public DSLObject
{
    public:
                                            StringBuilder(const char& del = '\n');
        bool                                isBuilding(){return mIsBuilding;}
        bool                                hasString(){return mHasString;}
        void                                reset();
        bool                                build(const char& ch);
        string                              getString();
        size_t								getStringSize(){return mTheString.size();}
        void                                setDelimiter(const char& rDel = '\n');

    private:
        string                              mTheString;
        char                                mDelimiter;
        bool                                mIsBuilding;
        bool                                mHasString;

        int                                 mNrOfDels;
};

}
#endif
