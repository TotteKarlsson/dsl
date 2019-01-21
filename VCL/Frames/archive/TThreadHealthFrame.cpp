
#pragma hdrstop
#include <vcl.h>
#include "dslThread.h"
#include "TThreadHealthFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TThreadHealth *ThreadHealth;
//---------------------------------------------------------------------------
__fastcall TThreadHealth::TThreadHealth(TComponent* Owner)
    : TFrame(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TThreadHealth::ToggleStartStopAExecute(TObject *Sender)
{
    if(!mTheThread)
    {
        return;
    }

    //Start stop the thread
    (ToggleStartStopA->Caption == "Start") ?
        mTheThread->Start() : mTheThread->Stop();

}
//---------------------------------------------------------------------------
void __fastcall TThreadHealth::Timer1Timer(TObject *Sender)
{
    //Check thread status
    if(mTheThread)
    {
        mThreadNameLbl->Caption     = mTheThread->GetLabel().c_str();
        mThreadIDLbl->Caption       = IntToStr(mTheThread->GetID());
        ToggleStartStopA->Caption = (mTheThread->GetID() > 0) ? "Stop" : "Start";
    }
}
//---------------------------------------------------------------------------
void       TThreadHealth::SetThread(dslThread* aThread){mTheThread = aThread;}
void       TThreadHealth::StartMonitor(){Timer1->Enabled = true;}
void       TThreadHealth::StopMonitor(){Timer1->Enabled = false;}
