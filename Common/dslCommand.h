#ifndef dslCommandH
#define dslCommandH
#include "dslCommonExporter.h"
#include "dslObject.h"
//---------------------------------------------------------------------------
namespace dsl
{
class DSL_COMMON Command : public DSLObject
{
    public:
        virtual                         ~Command();
        virtual void                    execute() = 0;
        virtual void                    undo() = 0;

    protected:

};
}
#endif
