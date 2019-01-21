#ifndef dslNumberBuilderH
#define dslNumberBuilderH
#include <string>
#include "dslObject.h"
#include "dslMathExporter.h"
//---------------------------------------------------------------------------

namespace dsl
{

class DSL_MATH NumberBuilder : DSLObject
{
    public:
                                NumberBuilder(const string& str = "0.0");
        void                    Init(const string& val);
        void                    AddChar(char* aChar);
        void                    RemoveLastChar();
        string                  GetString();
        char                    GetLastChar();
        bool                    HasDot();
        void                    Clear();
        bool                    IsFresh();
        void                    SwitchSign();

	private:
        string                  mTheString;
        bool                    mIsFresh;
};

}
#endif
