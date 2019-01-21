#include <vcl.h>
#pragma hdrstop
#include "TCreditsForm.h"
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TCreditsForm *CreditsForm;


__fastcall TCreditsForm::TCreditsForm(TComponent* Owner)
    : TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TCreditsForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if(Key == VK_ESCAPE)
    {
        Close();
    }
}

//---------------------------------------------------------------------------
void __fastcall TCreditsForm::Panel2Click(TObject *Sender)
{
    Close();
}


