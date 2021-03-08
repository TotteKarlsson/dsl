#pragma hdrstop
#include "dslMessageProcessor.h"
#include "dslStringUtils.h"
#include "dslMessageContainer.h"
#include "Poco/Mutex.h"
#include "dslLogger.h"

#if defined(__linux__)
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/syscall.h>
#endif
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
#if defined(_WIN32)
    mID =  GetCurrentThreadId();
#elif defined(__linux__)
    mID =syscall( __NR_gettid );
#else
    mID = -1;
#endif

}

bool MessageProcessor::start(bool inThread)
{
    if(inThread)
    {
    	dsl::Thread::run();
    }
    else
    {
        worker();
        return true;
    }
}

}
