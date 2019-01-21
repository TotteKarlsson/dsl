
#pragma hdrstop
#include "dslManagePluginsForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslPluginsFrame"
#pragma resource "*.dfm"
TmanagePluginsForm *managePluginsForm;
//---------------------------------------------------------------------------
__fastcall TmanagePluginsForm::TmanagePluginsForm(vector<dslPluginManager *> *plgins, TComponent* Owner)
  : TForm(Owner){
    plugins = plgins;
}
//---------------------------------------------------------------------------
void __fastcall TmanagePluginsForm::FillPluginsCBExecute(TObject *Sender){

    pluginsCB->Clear();

    for(unsigned int i = 0; i < plugins->size(); i++)
    {
        dslPluginManager *plgins = ((dslPluginManager *) plugins->at(i));
        pluginsCB->Items->AddObject(plgins->Name, (TObject*) plgins);
    }

    if(pluginsCB->Items->Count)
        pluginsCB->ItemIndex = 0;

    pluginsCBChange(0);
}
//---------------------------------------------------------------------------

void __fastcall TmanagePluginsForm::pluginsCBChange(TObject *Sender)
{
    //Fill the plugins frame with the selected plugins
    dslPluginManager *plugins = (dslPluginManager *) pluginsCB-> Items->Objects[pluginsCB->ItemIndex];
//    TPluginsFrame1->SetPlugins(plugins);
}
//---------------------------------------------------------------------------

void __fastcall TmanagePluginsForm::FormCreate(TObject *Sender)
{
    FillPluginsCBExecute(this);
}
//---------------------------------------------------------------------------

void __fastcall TmanagePluginsForm::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
    if(Key == VK_ESCAPE)
          Close();
}
//---------------------------------------------------------------------------


