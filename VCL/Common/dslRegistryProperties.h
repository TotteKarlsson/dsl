#ifndef dslRegistryPropertiesH
#define dslRegistryPropertiesH
#include <System.hpp>
#include "dslProperties.h"
#include "dslVCLCommonExporter.h"
//---------------------------------------------------------------------------

namespace dsl
{

using std::vector;
using std::string;

//TRegistryProperties is a container for a group of properties
//that can be read and retrieved from the windows registry
class VCLCOMMON TRegistryProperties : public Properties
{
	public:

                                        TRegistryProperties(const string& registryRoot, const string& iniSection = dsl::gEmptyString);
                                        ~TRegistryProperties();
        virtual bool                    read();
        virtual bool                    write();
        bool                            doesSectionExist();

    protected:
        string                          mRegistryRoot;
};

}
#endif
