#ifndef dslPropertiesH
#define dslPropertiesH
#include <vector>
#include <string>
#include "dslCommonExporter.h"
#include "dslProperty.h"
#include "dslObject.h"
//---------------------------------------------------------------------------

namespace dsl
{

using std::vector;
using std::string;

//Properties is a container for a group of properties
//See also INIFileProperties and Registry properties
class DSL_COMMON Properties : public DSLObject
{
	public:

                                                            Properties(const string& iniSection = "");
        virtual                                             ~Properties();

        BaseProperty*				                        getProperty(int index);

        void                                                add(BaseProperty* para);


    protected:
        vector<BaseProperty*>     	                        mProperties;
        string                       	                    mSection;


};

}
#endif
