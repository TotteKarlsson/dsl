#pragma hdrstop
#include "dslReadDirectoryChangesHost.h"
#include "dslReadDirectoryChangesWorker.h"
#include "dslWin32Utils.h"
//---------------------------------------------------------------------------

ReadDirectoryChangesHost::ReadDirectoryChangesHost(DirectoryNotifier* notifier)
:
mTerminate(false),
mOutstandingRequests(0),
mTheNotifier(notifier)
{}

unsigned int WINAPI ReadDirectoryChangesHost::threadStartProc(void* arg)
{
    ReadDirectoryChangesHost* pServer = (ReadDirectoryChangesHost*)arg;
    pServer->run();
    return 0;
}

// Called by QueueUserAPC to start orderly shutdown.
void CALLBACK ReadDirectoryChangesHost::terminateProc(ULONG_PTR arg)
{
    ReadDirectoryChangesHost* pServer = (ReadDirectoryChangesHost*)arg;
    pServer->requestTermination();
}

// Called by QueueUserAPC to add another directory.
void CALLBACK ReadDirectoryChangesHost::addDirectoryProc(ULONG_PTR arg)
{
    ReadDirectoryChangesWorker* pRequest = (ReadDirectoryChangesWorker*)arg;
    pRequest->mHost->addDirectory(pRequest);
}

void ReadDirectoryChangesHost::run()
{
    while (mOutstandingRequests || !mTerminate)
    {
        //Blocking call here
        DWORD rc = ::SleepEx(INFINITE, true);
    }
}

void ReadDirectoryChangesHost::addDirectory(ReadDirectoryChangesWorker* pBlock)
{
    if (pBlock->getDirectoryHandle())
    {
        ::InterlockedIncrement(&pBlock->mHost->mOutstandingRequests);
        mBlocks.push_back(pBlock);
        pBlock->beginRead();
    }
    else
    {
        delete pBlock;
    }
}

void ReadDirectoryChangesHost::requestTermination()
{
    mTerminate = true;

    for (DWORD i = 0; i < mBlocks.size(); ++i)
    {
        // Each Request object will delete itself.
        mBlocks[i]->requestTermination();
    }

    mBlocks.clear();
}

