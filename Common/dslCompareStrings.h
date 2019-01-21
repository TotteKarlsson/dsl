#ifndef dslCompareStringsH
#define dslCompareStringsH
#include "dslObject.h"
#include <string>
#include <functional>
//---------------------------------------------------------------------------

namespace dsl
{

using std::string;
class DSL_COMMON CompareStrings : public std::unary_function<string, bool>, public DSLObject
{
    public:
                                    CompareStrings(const std::string& n);
                                    CompareStrings(const char* s);
        bool                        operator () (const string& obj) const;

    private:
        string                      name;
};

}
#endif
