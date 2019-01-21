//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Unit1.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTSTDStringLabeledEdit"
#pragma link "dslTLogMemoFrame"
#pragma resource "*.dfm"
using namespace dsl;
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	mAProcess.assignCallbacks(onProcessStarted, onProcessProgress, onProcessFinished);
}

//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if(Key == vkEscape)
    {
        Close();
    }
}

//---------------------------------------------------------------------------
void __fastcall TForm1::RunBtnClick(TObject *Sender)
{
    //Run
    if(RunBtn->Caption == "Run")
    {
        mAProcess.setExecutable(ExecutableE->getValue());
        if(mAProcess.setup(ParametersE->getValue(), mhCatchMessages))
//        if(mAProcess.setup(ParametersE->getValue(), mhShowMessages))
        {
            mAProcess.start();
        }
    }
    else if(RunBtn->Caption == "Stop")
    {
        mAProcess.stop();
        RunBtn->Caption = "Stopping..";
    }
}

//Need to synchronize with main thread here
void TForm1::onProcessStarted(void* arg1, void* arg2)
{
    Log(lInfo) << "Process was started.";
    RunBtn->Caption = "Stop";
}

//Need to synchronize with main thread here
void TForm1::onProcessProgress(void* arg1, void* arg2)
{
    string* str = (string*) arg2;
    Log(lInfo) << "Process is progressing: " << (*str);
}

//Need to synchronize with main thread here
void TForm1::onProcessFinished(void* arg1, void* arg2)
{
    Log(lInfo) << "Process finished.";
    RunBtn->Caption = "Run";
}



