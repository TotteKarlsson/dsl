#pragma hdrstop
#include "dslIPCMessageProcessor.h"
#include "dslStringUtils.h"
#include "dslIPCServer.h"
#include "dslLogger.h"

using boost::mutex;
typedef mutex::scoped_lock ScopedLock;

namespace dsl
{

//----------------------------------------------------------------
IPCMessageProcessor::IPCMessageProcessor(IPCServer* _parent)
: mParent(_parent)
{}

//----------------------------------------------------------------
IPCMessageProcessor::~IPCMessageProcessor()
{
    shutDown();
}

void IPCMessageProcessor::shutDown()
{
    mIsTimeToDie = true;
    if(mParent)
    {
        //conditionVariable
        mParent->mListDataArrived.notify_all();
    }

    while(mThread.isRunning())
    {
        ;
    }

    return;
}

void IPCMessageProcessor::run()
{
    worker();
}

void IPCMessageProcessor::worker()
{
    mIsStarted = true;
    mIsRunning = true;

    Log(lDebug3)<<"Entering IPCMessage processor thread.";

    while(!mIsTimeToDie)
    {
        ScopedLock lock(mParent->mListMutex);
        if(mParent->nrOfMessages() == 0)
        {
            Log(lDebug5)<<"Waiting for message in IPCMessage processor";
            mIsStarted = true;
            mParent->mListDataArrived.wait(lock);
        }
        else
        {
            lock.unlock();
            mParent->processNextRequest();
        }
    }

    Log(lDebug3)<<"Exiting Process Messages Thread...";
    mIsFinished = true;
    mIsRunning = false;
}


}
