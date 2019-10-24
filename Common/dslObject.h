#ifndef dslObjectH
#define dslObjectH
#include "dslCommonExporter.h"
#include "dslConstants.h"
#include <string>
//---------------------------------------------------------------------------
using std::string;

namespace dsl
{

typedef unsigned int dsluint;

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

using dsl::DSLObject;

#endif
