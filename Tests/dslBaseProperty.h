#ifndef dslBasePropertyH
#define dslBasePropertyH
#include <string>
#include "dslObject.h"
#include "dslCommonExporter.h"
//---------------------------------------------------------------------------

namespace dsl
{

using std::string;
using std::ostream;
class IniFile;

//abstract class for inifile parameters
//a non template base class allow us to store derived objects,
//of any type, in a vector for example
class DSL_COMMON BaseProperty : public DSLObject
{
	public:
                                                        BaseProperty();
                                                        BaseProperty(const string& lbl);
        virtual                                         ~BaseProperty();

        //Interface
        virtual string                                  getLabel() = 0;


	protected:
        string mKey;
};

}
#endif
