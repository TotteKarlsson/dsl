#pragma hdrstop
#include "dslTLogMemoFrame.h"
#include "dslUtils.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTLogFileReader"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TLogMemoFrame *LogMemoFrame;
using namespace dsl;

//---------------------------------------------------------------------------
__fastcall TLogMemoFrame::TLogMemoFrame(TComponent* Owner)
	: TFrame(Owner)
{
    LogFileReader1->start();
}

//---------------------------------------------------------------------------
void TLogMemoFrame::init()
{
    //Setup LogLevel CB
    string lvl = dsl::toString(gLogger.getLogLevel());

    //Find item in CB with this loglevel
    int index = LogLevelCB->Items->IndexOf(vclstr(lvl));

    if(index > -1)
    {
		LogLevelCB->ItemIndex = index;
    }
}

//Time will tell if this works... may need a more elaborate shutdown mechanism
//---------------------------------------------------------------------------
__fastcall TLogMemoFrame::~TLogMemoFrame()
{
    LogFileReader1->stop();
}

//---------------------------------------------------------------------------
void __fastcall TLogMemoFrame::mClearLogMemoBtnClick(TObject *Sender)
{
	infoMemo->Clear();
}


//---------------------------------------------------------------------------
void __fastcall TLogMemoFrame::LogLevelCBCloseUp(TObject *Sender)
{
	if(LogLevelCB->ItemIndex == -1)
    {
    	return;
    }

    string lvlS = stdstr(LogLevelCB->Items->Strings[LogLevelCB->ItemIndex]);
    LogLevel lvl = toLogLevel(lvlS);
    gLogger.setLogLevel(lvl);
}


