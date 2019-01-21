#ifndef TSaveFormToRegistryH
#define TSaveFormToRegistryH
#include <Forms.hpp>
#include <Registry.hpp>
#include <memory>
#include <string>
#include "dslConstants.h"
//---------------------------------------------------------------------------

using std::string;
class VCLCOMMON TSaveFormToRegistry
{
    public:
                                                TSaveFormToRegistry(const string& registryRoot, const string& formName, TForm* f);
        virtual                                 ~TSaveFormToRegistry();
        virtual void                            read();
        virtual void                            write();

    protected:

        string                                  mRegistryRoot;
        string                                  mFormName;
        TForm*                                  mForm;
};

#endif
