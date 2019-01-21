#pragma hdrstop
#include "TPluginsFrame.h"
#include "dslVCLUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

TPluginsFrame *PluginsFrame;
using namespace dsl;

//---------------------------------------------------------------------------
__fastcall TPluginsFrame::TPluginsFrame(TComponent* Owner)
  : TFrame(Owner)
{
  Plugins = nullptr;
}
//---------------------------------------------------------------------------
void TPluginsFrame::SetPlugins(PluginManager *plugins)
{
//    Plugins = plugins;
//    PluginFolderLbl->Hint = Plugins->PluginFolder;
//    PluginFolderLbl->Caption = MinimizeName(Plugins->PluginFolder, PluginFolderLbl->Canvas, 200);
//
//    //Fill list with available plugins, i.e. files in the plugin directory
//    FillFileList(GetFilesInDir(Plugins->PluginFolder, Plugins->PluginExtension));
//
//    //Check plugins that are loaded
//    TStringList *loadedP = new TStringList;
//    Plugins->GetLoadedPluginsFileNames(loadedP);
//    for(int i = 0; i < CheckListBox1->Items->Count; i++)
//        if(loadedP->IndexOf(CheckListBox1->Items->Strings[i]) != -1)
//            CheckListBox1->Checked[i] = true;
}

void TPluginsFrame::FillFileList(TStrings* list)
{
    CheckListBox1->Clear();
    for(int i = 0; i < list->Count; i++)
        CheckListBox1->Items->Add(ExtractFileName(list->Strings[i]));
}

void __fastcall TPluginsFrame::CheckListBox1Click(TObject *Sender)
{
//    //Take action depending on if the item is checked or unchecked
//    //If checked, load the plugin at itemindex, otherwise unload it
//    int item = CheckListBox1->ItemIndex;
//    bool isChecked = CheckListBox1->Checked[item];
//    String fName;
//    if(isChecked)
//    {
//        //Load the plugin
//        fName = Plugins->PluginFolder + "\\";
//        fName += CheckListBox1->Items->Strings[item];
//        Plugins->LoadPlugin(fName);
//    }
//    else
//    {
//        //Unload the plugin
//        fName = Plugins->PluginFolder + "\\";
//        fName += CheckListBox1->Items->Strings[item];
//        Plugins->UnLoadPlugin(fName);
//    }
}
//---------------------------------------------------------------------------






