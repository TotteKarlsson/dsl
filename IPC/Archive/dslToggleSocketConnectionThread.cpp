#pragma hdrstop
#include "dslToggleSocketConnectionThread.h"
#include "dslLogger.h"
#include "dslSocketClient.h"
//---------------------------------------------------------------------------

namespace dsl
{
ToggleSocketConnectionThread::ToggleSocketConnectionThread(SocketClient* aSocketClient)
:
mClient(aSocketClient),
Thread("ToggleSocketConnection")
{}

void ToggleSocketConnectionThread::run()
{
    worker();
}

void ToggleSocketConnectionThread::worker()
{
    mIsWorking = true;
    Log(lDebug)<<"Entering ToggleSocket connection thread.";
    mIsStarted = true;

    //Just execute the connect to log server function..
    if(mClient)
    {
        if(mClient->isConnected())
        {
            mClient->disConnect();
        }
        else
        {
            mClient->reConnect();
        }
    }

    mIsFinished = true;
    Log(lDebug)<<"Exiting Toggle socket connection.";
    mIsWorking = false;
}

}
