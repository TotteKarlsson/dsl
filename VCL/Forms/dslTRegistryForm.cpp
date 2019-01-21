#pragma hdrstop
#include "dslTRegistryForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

TRegistryForm *RegistryForm;

__fastcall TRegistryForm::TRegistryForm(const string& regRoot, const string& formName, TComponent* Owner)
:
TForm(Owner),
mFormSaver(regRoot, formName, this)
{
    mRegistryRoot = (formName.size()) ? formName : string("DefaultFormSettings");
    readRegistry();
}

void __fastcall TRegistryForm::readRegistry()
{
	mFormSaver.read();
}

void __fastcall TRegistryForm::writeToRegistry()
{
	mFormSaver.write();
}

//---------------------------------------------------------------------------
__fastcall TRegistryForm::~TRegistryForm()
{
	//Call WriteToRegistry in the forms OnClose...
	//This causes settings to be written to the registry
	writeToRegistry();
}

//---------------------------------------------------------------------------
void __fastcall TRegistryForm::CreateParams(TCreateParams &Params)
{
	TForm::CreateParams(Params);
	//Params.Style &= ~WS_CAPTION;
	TForm::FormStyle = fsNormal;
}

void __fastcall TRegistryForm::FormClose(TObject *Sender, TCloseAction &Action)
{
    writeToRegistry();
}