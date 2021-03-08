#ifndef dslTRegistryFormH
#define dslTRegistryFormH
#include <Forms.hpp>
#include <string>
#include "dslTSaveFormToRegistry.h"
//---------------------------------------------------------------------------

class PACKAGE TRegistryForm : public TForm
{
    __published:


    private:
        TSaveFormToRegistry                         mFormSaver;
        std::string                                 mRegistryRoot;

	protected:
		virtual void                 __fastcall     CreateParams(TCreateParams &Params);

    public:
                                    __fastcall      TRegistryForm(const std::string& regRoot, const std::string& formName, TComponent* Owner);
        virtual                     __fastcall      ~TRegistryForm();
        virtual void                __fastcall      readRegistry();
		virtual void                __fastcall      writeToRegistry();
};

extern PACKAGE TRegistryForm *RegistryForm;
#endif
