
#pragma hdrstop
#include "dslStringUtils.h"
#include "dslProgressFrame.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TProgressFrame *ProgressFrame;
//---------------------------------------------------------------------------
__fastcall TProgressFrame::TProgressFrame(TComponent* Owner)
    : TFrame(Owner)
{
    ProgressBar1->Max = 100;
    ProgressBar1->Step = 1;
}

void __fastcall TProgressFrame::SetBarColor(int color)
{
    SendMessage(ProgressBar1->Handle, PBM_SETBARCOLOR, 0, color);
}

//---------------------------------------------------------------------------
void __fastcall TProgressFrame::StepBy(const int& incr)
{
    /* TODO : Use the StepIt Method instead */
    ProgressBar1->StepBy(incr);
    progressLbl->Caption = Sysutils::IntToStr(ProgressBar1->Position) + " %";
}

int __fastcall TProgressFrame::Max()
{
    return ProgressBar1->Max;
}

void __fastcall TProgressFrame::SetPos(int pos)
{
    ProgressBar1->Position = pos;
    progressLbl->Caption = Sysutils::IntToStr(ProgressBar1->Position) + " %";
}

void __fastcall TProgressFrame::SetPos(const String& pos)
{
    int currPos = ProgressBar1->Position;
    int newPos = -1;

    try
    {
        if(pos.Length())
            newPos = StrToInt(pos);
    }
    catch(EConvertError& e)
    {

    }
    progressLbl->Caption = pos + " %";
    if(newPos != -1)
        ProgressBar1->Position = newPos;
}
