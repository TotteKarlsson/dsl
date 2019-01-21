#pragma hdrstop
#include <Dialogs.hpp>
#include "dslStringUtils.h"
#include "dslVCLUtils.h"
#include "dslProcess.h"
#include "dslLogger.h"
#include "dslStringBuilder.h"
#pragma package(smart_init)

using std::string;

namespace dsl
{

Process::Process(const string& exeFName, const string& wd)
:
mExeFile(exeFName),
mReadPipeHandle(nullptr),
mWritePipeHandle(nullptr),
mWorkingDirectory(wd),
onEnter(nullptr),
onProgress(nullptr),
onExit(nullptr),
mOpaqueData1(nullptr),
mOpaqueData2(nullptr)
{
    ZeroMemory(&mSI, sizeof(mSI) );
    ZeroMemory(&mPI, sizeof(mPI) );
}

Process::~Process()
{}

bool Process::setExecutable(const string& nameAndPath)
{
    mExeFile = nameAndPath;
    return true;
}

bool Process::setWorkingDirectory(const string& wd)
{
    mWorkingDirectory = wd;
    return true;
}

void Process::assignCallbacks(Callback enterFnc, Callback progressFnc, Callback exitFnc)
{
    onEnter 	= enterFnc;
    onProgress 	= progressFnc;
    onExit 		= exitFnc;
}

void Process::assignOpaqueData(void* one, void* two)
{
    mOpaqueData1 = one;
    mOpaqueData2 = two;
}

bool Process::setup(const string& commandLine, MessageHandling mh)
{
    if(mIsRunning)
    {
        return false;
    }

	mMessageHandling = mh;
    ZeroMemory(&mSI, sizeof(mSI) );
    ZeroMemory(&mPI, sizeof(PROCESS_INFORMATION));

    mSI.cb = sizeof(mSI);
    mSI.dwFlags = STARTF_USESHOWWINDOW;

    switch(mMessageHandling)
    {
        case mhCatchMessages:
            setupPipe();
            mSI.dwFlags      = STARTF_USESHOWWINDOW|STARTF_USESTDHANDLES;
            mSI.wShowWindow  = SW_HIDE;
            mSI.hStdOutput   = mWritePipeHandle;
            mSI.hStdError    = mWritePipeHandle;
        break;
        case mhIgnoreMessages:          mSI.wShowWindow = SW_HIDE;        break;
        case mhShowMessages:            mSI.wShowWindow = SW_SHOW;        break;
    }

    mCommandLine = mExeFile + string(" ") + commandLine;
    char cmdLine[32768]; //Path and parameters
    strcpy(cmdLine, mCommandLine.c_str());

    //Create a Console
    if(!CreateProcessA(NULL,        // No module name (use command line).
        cmdLine,                    // Command line.
        NULL,                       // Process handle not inheritable.
        NULL,                       // Thread handle not inheritable.
        TRUE,                       // Set handle inheritance to FALSE.
        CREATE_SUSPENDED,           // No creation flags.
        NULL,                       // Use parent's environment block.
        mWorkingDirectory.c_str(),  // Use 's starting directory.
        &mSI,                       // Pointer to STARTUPINFO structure.
        &mPI)                       // Pointer to PROCESS_INFORMATION structure.
    )
    {
        mProcessState = psTerminated;
        return false;
    }
    else
    {
        mProcessState = psPaused;
        return true;
    }
    return false;
}

bool Process::start(bool inThread)
{
    if(inThread)
    {
        if(mThread.isRunning())
        {
            Log(lDebug3)<<"Tried to start a working thread!";
            return false;
        }
        else
        {
            mIsTimeToDie = false;
            mThread.start(*this);
        }
    }
    else
    {
        run();
    }
}

void Process::run()
{
    Log(lInfo) << "Entered Process Thread..";
    mIsRunning = true;
    mIsStarted = true;
    if(onEnter)
    {
        onEnter(this, nullptr);
    }

    if(ResumeThread(mPI.hThread) == 0xFFFFFFFF)
    {
        mProcessState = psUndefined;
        return;
    }

    mProcessState = psRunning;
    if(mMessageHandling == mhCatchMessages)
    {
        readFromPipe();
    }
    else
    {
        while(WaitForSingleObject(mPI.hProcess,0) != WAIT_OBJECT_0)
        {
            Sleep(10);
            if(mIsTimeToDie)
            {
                break;
            }
        }
    }

    if(mIsTimeToDie)
    {
        if(!terminate())
        {
            Log(lError) << "Failed to properly terminate process..";
        }
        else
        {
            Log(lInfo) << "Process was terminated";
        }
    }
    else
    {
		mProcessState = psFinished;
    }

    CloseHandle(mPI.hThread);
    CloseHandle(mPI.hProcess);

    if(mhCatchMessages)
    {
        CloseHandle(mReadPipeHandle);
        CloseHandle(mWritePipeHandle);
    }

    if(onExit)
    {
        onExit(mOpaqueData1, mOpaqueData2);
    }

    mIsFinished = true;
    mIsRunning = false;
    Log(lInfo) << "Finished process thread..";
}

bool Process::readFromPipe()
{
    StringBuilder sb;
    const int bufferSize(1024);
    char data[bufferSize];

    DWORD BytesToRead;
    DWORD TotalBytes;
    DWORD BytesLeft;

    while (mIsTimeToDie == false)
    {
        //Check for the presence of data in the pipe
        if(!PeekNamedPipe(mReadPipeHandle, data, sizeof(data), &BytesToRead, &TotalBytes, &BytesLeft))
        {
            RaiseLastOSError();
        }

        //If there are bytes, read them
        if(BytesToRead)
        {
            if(!ReadFile(mReadPipeHandle, data, sizeof(data)-1, &BytesToRead, NULL))
            {
                RaiseLastOSError();
            }

            data[BytesToRead] = '\0';

            //Parse data
            for(int i = 0; i < BytesToRead; i++)
            {
                //Find a new line in data
                if(!sb.isBuilding())
                {
                    sb.build(data[i]);
                }

                if(onProgress && sb.hasString())
                {
                    string theString(sb.getString());
                    onProgress(this, &(theString));
                    sb.reset();
                }
                else if(sb.hasString())
                {
                    Log(lDebug) << "Got Message: " <<sb.getString();
                    sb.reset();
                }
            }
        }
        else
        {
            //Is the console app terminated?
            if(WaitForSingleObject(mPI.hProcess, 0) == WAIT_OBJECT_0)
            {
                mProcessState = psFinished;
                break;
            }
        }
    	Sleep(10);
    }

    return true;
}

bool Process::terminate()
{
    // Close process and thread handles.
    BOOL TermSucc = TerminateProcess(mPI.hProcess, 0);
    if(TermSucc == false)
    {
        mProcessState = psUndefined;
        return false;
    }
    else
    {
        mProcessState = psTerminated;
    }
    return true;
}

bool Process::pause()
{
    DWORD res = SuspendThread(mPI.hThread);     // handle to the thread
    if(res == 0xFFFFFFFF)
    {
        mProcessState = psUndefined;
        return false;
    }
    else
    {
        mProcessState = psPaused;
    }
    return true;
}

bool Process::setupPipe()
{
    SECURITY_ATTRIBUTES sa;
    ZeroMemory(&sa,sizeof(SECURITY_ATTRIBUTES));
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = true;
    sa.lpSecurityDescriptor = NULL;

    if(!CreatePipe(&mReadPipeHandle, &mWritePipeHandle, &sa,0))
    {
        RaiseLastOSError();
        return false;
    }
    else
    {
        return true;
    }
}

ProcessState Process::getProcessState()
{
    //Check what state the process is in
    DWORD status = STILL_ACTIVE;
    GetExitCodeProcess(mPI.hProcess, &status);
    if(status != STILL_ACTIVE)
    {
        mProcessState = psFinished;
    }

//  hProcess = OpenProcess(PROCESS_TERMINATE , FALSE, ProcId);
//  if(!hProcess)
//      mProcessState = psFinished;
//  else
//    CloseHandle(hProcess);
    return mProcessState;
}

string Process::getProcessStateAsString()
{
    switch(getProcessState())
    {
        case psRunning:         return "Running";
        case psPaused:          return "Paused";
        case psFinished:        return "Finished";
        case psTerminated:      return "Terminated";
        default:
        return "Undefined";
    }
}

}

