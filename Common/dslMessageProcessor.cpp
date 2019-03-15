#pragma hdrstop
#include "dslMessageProcessor.h"
#include "dslStringUtils.h"
#include "dslMessageContainer.h"
#include "Poco/Mutex.h"
#include "dslLogger.h"
//----------------------------------------------------------------

namespace dsl
{

using Poco::Mutex;
//----------------------------------------------------------------
MessageProcessor::MessageProcessor(MessageContainer& messageContainer, const string& threadName)
:
Thread(threadName),
mAllowProcessing(true),
mMessageContainer(messageContainer)
{}

//----------------------------------------------------------------
MessageProcessor::~MessageProcessor()
{
    stop();
}

void MessageProcessor::pauseProcessing()
{
    mAllowProcessing = false;
}

void MessageProcessor::resumeProcessing()
{
    mAllowProcessing = true;
}

void MessageProcessor::stop()
{
    //Sets time to die to true
    dsl::Thread::stop();
    mMessageContainer.mGotMessage.signal();    //conditionVariable

    int count = 0;
    if(mThread.isRunning())//The dtor will call shutdown. If already shutdown, the thread object is nullptr
    {
        mThread.join();    //Wait for worker to exit...
    }
}

void MessageProcessor::run()
{
    worker();
}

void MessageProcessor::worker()
{
    Log(lDebug)<<"Entering LogMessageProcessor Worker Function.";
    //mID =  GetCurrentThreadId();
    mID = -1;
}

bool MessageProcessor::start(bool inThread)
{
    if(inThread)
    {
        return dsl::Thread::start();
    }
    else
    {
        worker();
        return true;
    }
}


}
