#ifndef dslObjectH
#define dslObjectH
#include <string>
#include "dslCommonExporter.h"
//---------------------------------------------------------------------------
using std::string;

namespace dsl
{

class DSL_COMMON DSLObject
{
    public:
                                        DSLObject();
                                        DSLObject(const DSLObject& obj);
        virtual                         ~DSLObject();
        virtual string                  getTypeName() const;
        virtual string                  asString(const char& delimiter=',') const;
        virtual const char*             c_str() const;

    protected:

};

}
#endif
