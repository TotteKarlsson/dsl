#pragma hdrstop
#include "TFileEditor.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#pragma link "TFileEditor"
TFileEditor *FileEditor;
//---------------------------------------------------------------------------

__fastcall TFileEditor::TFileEditor(const StringList& strs, TApplication* Owner)
:
TForm(Owner)
{
    Memo1->Clear();
      for(unsigned int i = 0; i < strs.size(); i++)
      {
        Memo1->Lines->Add(strs[i].c_str());
      }
      Label1->Caption = "No File";
      Caption =  "No File";
}

//---------------------------------------------------------------------------
void __fastcall TFileEditor::FormClose(TObject *Sender, TCloseAction &Action)
{
    Action = caFree;
}

//---------------------------------------------------------------------------
void __fastcall TFileEditor::SaveFileAction1Execute(TObject *Sender)
{
      Memo1->Lines->SaveToFile(Label1->Caption);
}

//---------------------------------------------------------------------------
void __fastcall TFileEditor::ReloadFileActionExecute(TObject *Sender)
{
      Memo1->Lines->LoadFromFile(Label1->Caption);
}

//---------------------------------------------------------------------------
void __fastcall TFileEditor::SaveAsActionExecute(TObject *Sender)
{
      if(SaveDialog1->Execute())
      {
        Memo1->Lines->SaveToFile(SaveDialog1->FileName);
      }
}

//---------------------------------------------------------------------------
bool __fastcall TFileEditor::Read(const string& file)
{
    ShowMessage("Reading is not implemented");
    return false;
}
//---------------------------------------------------------------------------
bool __fastcall TFileEditor::Write(const string& file)
{
    ShowMessage("Writing is not implemented");
    return false;
}

void __fastcall TFileEditor::UpdateWindow(){}

void __fastcall TFileEditor::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)

{
    if(Key == VK_ESCAPE)
    {
        Close();
    }
}
//---------------------------------------------------------------------------

