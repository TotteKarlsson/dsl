#pragma hdrstop
#include "dslStringUtils.h"
#include "dslMessageContainer.h"
#include "dslIPCMessage.h"
//#include "dslLogClient.h"
#include "dslSocketClient.h"
#include "dslLogger.h"
#include "dslLogMessageProcessor.h"
//----------------------------------------------------------------

namespace dsl
{

LogMessageProcessor::LogMessageProcessor(SocketClient* theSocket, MessageContainer& _mMessageContainer, const string& threadName)
:
mMessageContainer(_mMessageContainer),
Thread(threadName),
mSocketClient(theSocket),
mAllowProcessing(true),
mParent(nullptr)
{}

//----------------------------------------------------------------
LogMessageProcessor::~LogMessageProcessor()
{
    ShutDown();
}

void LogMessageProcessor::ShutDown()
{
    Thread::stop();    //Sets time to die to true
    mMessageContainer.mGotMessage.signal();    //conditionVariable

    int count = 0;
    if(mThread.isRunning())             //The dtor will call shutdown. If already shutdown, the thread object is nullptr
    {
        mThread.join();    //Wait for worker to exit...
        //delete mThread;
        //mThread = nullptr;
    }
}

void LogMessageProcessor::run()
{
    Worker();
}

void LogMessageProcessor::Worker()
{
    Log(lDebug)<<"Entering LogMessageProcessor Worker Function.";
    mID =  GetCurrentThreadId();
    //Wait for conditional varible, regarding messages and
    //then, when set process messages...
    while(!mIsTimeToDie)
    {
//        ScopedLock lock(mMessageContainer.mListMutex);
//        if(mMessageContainer.getNrOfMessages() == 0)
//        {
//            mIsStarted = true;
//            mMessageContainer.mListDataArrived.wait(lock);
//        }
//
//        lock.unlock();
//        if(!mIsTimeToDie)
//        {
//            ProcessMessages();
//        }
    }

    mIsFinished = true;
    mID = -1;
}

int LogMessageProcessor::Start()
{
    return Thread::start();
}

bool LogMessageProcessor::Stop()
{
    Thread::stop();
    mMessageContainer.mGotMessage.signal();
    return true;
}

void LogMessageProcessor::ProcessMessages()
{
    //We cannot process messages if the logClient is in the process
    //of connecting to the server
    if(mParent && mParent->IsConnecting() || mAllowProcessing == false)
        return;

    if(!mSocketClient)
        return;

    //Process each message in the message list
    string msg = mMessageContainer.pop();    //If client is not connected, this message will never be sent to the server
    while(msg.size() && mSocketClient->isConnected())
    {
        //Create a IPC message of type cLogMessage
        IPCMessage ipc_msg(cLogMessage, msg);
        ipc_msg.Pack();
        ipc_msg =  "[" +ipc_msg + "]";

        if(msg.size())
        {
        	mSocketClient->send(ipc_msg);
        }
        msg = mMessageContainer.pop();
    }
}


}
