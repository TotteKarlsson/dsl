#ifndef dslTRegistryFormH
#define dslTRegistryFormH
#include <Forms.hpp>
#include <string>
#include "dslTSaveFormToRegistry.h"
//---------------------------------------------------------------------------

using std::string;

class PACKAGE TRegistryForm : public TForm
{
    __published:
		void __fastcall 							FormClose(TObject *Sender, TCloseAction &Action);

    private:
        TSaveFormToRegistry                         mFormSaver;
        string                                      mRegistryRoot;

	protected:
		virtual void                 __fastcall     CreateParams(TCreateParams &Params);

    public:
                                    __fastcall      TRegistryForm(const string& regRoot, const string& formName, TComponent* Owner);
        virtual                     __fastcall      ~TRegistryForm();
        virtual void                __fastcall      readRegistry();
		virtual void                __fastcall      writeToRegistry();
};

extern PACKAGE TRegistryForm *RegistryForm;
#endif
