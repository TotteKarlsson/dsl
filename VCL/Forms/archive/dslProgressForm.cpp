
#pragma hdrstop
#include "dslProgressForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TProgressF *ProgressF;
//---------------------------------------------------------------------------
__fastcall TProgressF::TProgressF(TComponent* Owner)
    : TForm(Owner){
    ProgressBar1->Brush->Color = clLime;
    ProgressBar1->Max = 100;
    ProgressBar1->Step = 1;
}
//---------------------------------------------------------------------------
void __fastcall TProgressF::StepBy(const int& incr)
{
/* TODO : Use the StepIt Method instead */
    ProgressBar1->StepBy(incr);
}

int __fastcall TProgressF::GetMax()
{
    return ProgressBar1->Max;
}

void __fastcall TProgressF::SetFileNameLabel(const String& str)
{
    FileNameLabel->Caption = str;
}

