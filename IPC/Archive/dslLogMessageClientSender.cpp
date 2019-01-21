#ifdef MTK_PCH
#include "dsl_pch.h"
#endif
#pragma hdrstop
#include "dslStringUtils.h"
#include "dslLogMessageClientSender.h"
#include "dslLogClient.h"
#include "dslLogger.h"
#pragma package(smart_init)
//----------------------------------------------------------------
dslLogMessageClientSender::dslLogMessageClientSender(dslLogClient* _parent)
: parent(_parent)
{}

//----------------------------------------------------------------
dslLogMessageClientSender::~dslLogMessageClientSender()
{
    ShutDown();
}

void dslLogMessageClientSender::ShutDown()
{
    dslThread::ShutDown();    //Sets time to die to true
    if(parent)
        parent->mListDataArrived.notify_all();    //conditionVariable

    int count = 0;
    if(mThread)             //The dtor will call shutdown. If already shutdown, the thread object is nullptr
    {
        while(mIsStarted == false)
        {
            count++;
            Sleep(1);
            if(count > 1000)
                break;
        }

        parent->mListDataArrived.notify_all();    //conditionVariable
        mThread->join();
        delete mThread;
        mThread = nullptr;
    }
}

void dslLogMessageClientSender::Worker()
{
    //Wait for conditional varible, regarding messages and
    //then, when set process messages...
    //The message list are accessed by child threads
    while(!mIsTimeToDie)
    {
        boost::mutex::scoped_lock lock(parent->mListMutex);
        if(parent->NrOfMessages() == 0)
        {
            mIsStarted = true;
            parent->mListDataArrived.wait(lock);
        }
        else
        {
            lock.unlock();
            parent->ProcessNextMessage();
        }
    }

    Log(lDebug3)<<"Exiting LogMessageClientSender worker function.";
    mIsFinished = true;
}
