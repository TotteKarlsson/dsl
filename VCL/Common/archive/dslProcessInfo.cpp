
#pragma hdrstop
#include "dslProcessInfo.h"
#include "dslWatchFileSystemThread.h"

#pragma package(smart_init)


bool dslProcessInfo::ShutDown()
{
//    BroadcastSystemMessage(
//    BSF_IGNORECURRENTTASK, // do not send message to this process
//    BSM_APPLICATIONS,      // broadcast only to applications
//    PM_MYMSG,              // registered private message
//    wParam,                // message-specific value
//    lParam );              // message-specific value
    return false;
}

bool dslProcessInfo::Terminate()
{
    return TerminateProcess(mProcessID);
}

bool TerminateProcess(const int& pid)
{
    //Kill the process
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, pid);
    if(!hProcess)
        return false;

    return TerminateProcess(hProcess, 0);

}

//dslWatchFileSystemThread::mParent(parent), mFileSystemItem(_FileSystemItem), dslThread("WatchFileFolderThreadA")
//{
//}
//
//dslWatchFileSystemThread::~dslWatchFileSystemThread()
//{
//}
