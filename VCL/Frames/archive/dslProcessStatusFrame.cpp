
#pragma hdrstop
#include "dslStringUtils.h"
#include "dslLogger.h"
#include "dslProcessStatusFrame.h"
#include "dslProcessList.h"
#include "dslStopProcessThread.h"
#include "dslVCLUtils.h"
#include "dslTableRow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TProcessStatusFrame *ProcessStatusFrame;
//---------------------------------------------------------------------------
__fastcall TProcessStatusFrame::TProcessStatusFrame(TComponent* Owner)
    : TFrame(Owner)
{

}

//---------------------------------------------------------------------------
bool __fastcall TProcessStatusFrame::SetExecutable(const string& theExe)
{
//    mExeName = GetFileName(theExe).c_str();
//    mExePath = GetFilePath(theExe.c_str()).c_str();

    dslTableRow fName(mExeName, ".");
    string appName = fName.GetEntry(0);
    ProcessGB->Caption = appName.c_str();

    string shutDownMsg = "SHUTDOWN_" + mExeName;
//    mShutDownMessageID = RegisterWindowMessage(TCHAR(shutDownMsg.c_str())));

    StartStopA->Enabled = true;
    mStatusTimer->Enabled = true;
    return true;
}

void __fastcall TProcessStatusFrame::StartStopAExecute(TObject *Sender)
{
    (StartStopA->Caption == "Start") ? Start() : Stop();
}

//---------------------------------------------------------------------------
void __fastcall TProcessStatusFrame::mStatusTimerTimer(TObject *Sender)
{
    //Check if process is running.
    bool isRunning = IsRunning();
    string status = (isRunning) ? "Running" : "Not Running";
    StartStopA->Caption  = (isRunning) ? "Stop" : "Start";
    StartStopA->ImageIndex = (isRunning) ? 1 : 0;
    Log(lDebug5)<<"Status for process: "<<mExeName<<" : "<<status;

    string theExe = joinPath(mExePath, mExeName);
    //Check if executable is present
//    EnableDisableFrame(this, FileExists(theExe));

}
//---------------------------------------------------------------------------
bool __fastcall TProcessStatusFrame::IsRunning()
{
    //Check if a process is running..
    dslProcessList processes;
    return(processes.ContainsProcess(mExeName));
}

bool __fastcall TProcessStatusFrame::Start()
{
    int mPID = SpawnProcess(mExePath, mExeName);
    return true;
}

bool __fastcall TProcessStatusFrame::Stop()
{
    //Try to stop the application in a thread
    dslStopProcessThread* aThread = new dslStopProcessThread(mExeName);
    if(aThread)
    {
        aThread->Start();
    }

    return true;
}


