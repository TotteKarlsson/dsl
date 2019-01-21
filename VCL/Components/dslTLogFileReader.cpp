#include <vcl.h>
#pragma hdrstop
#include "dslTLogFileReader.h"
#include "dslLogger.h"
#include "dslVCLUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace dsl;
typedef void __fastcall (__closure *dummy)(void);
dummy d;
//---------------------------------------------------------------------------
__fastcall TLogFileReader::TLogFileReader(TComponent* Owner)
	: TComponent(Owner),
	mReader("", d, false),
	FLogMemo(NULL)
{}

__fastcall 	TLogFileReader::~TLogFileReader()
{
    Log(lInfo) << "LogFile Reader destructor";
}

bool TLogFileReader::start()
{
	mReader.setFileName(dsl::gLogger.getLogFileName());
    mReader.assignOnMessageCallBack(callback);
	return mReader.start(true);
}

bool TLogFileReader::stop()
{
    mReader.stop();
    return true;
}

bool TLogFileReader::isRunning()
{
    return mReader.isRunning();
}

void __fastcall TLogFileReader::callback()
{
    if(FLogMemo)
    {
		FLogMemo->Lines->Add(vclstr(mReader.getData()));
		mReader.purge();
    }
}


