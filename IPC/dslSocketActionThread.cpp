#pragma hdrstop
#include "dslSocketActionThread.h"
#include "dslLogger.h"
#include "dslSocketClient.h"
//---------------------------------------------------------------------------

namespace dsl
{
SocketActionThread::SocketActionThread(SocketClient& aSocketClient)
:
mSocket(aSocketClient),
Thread("SocketActionThread")
{}

SocketActionThread::~SocketActionThread()
{}

bool SocketActionThread::start(bool inThread)
{
    if(inThread)
    {
        Thread::run();
    }
    else
    {
    	run();
    }
    return true;
}


void SocketActionThread::run()
{
    mIsStarted = true;
    Log(lDebug3)<<"Entering socket action thread.";

    StringList& args = mAction.mArguments;
    switch(mAction.mActionEnum)
    {
        case saConnect:
            //Parse args, and call connect
            if(args.count() != 2)
            {
                Log(lError) << "Bad argument count for reconnecting socket in SocketActionThread";
            }
            else
            {
            	mSocket.connectByHostName(toInt(args[0]), args[1]);
            }
        break;

        case saDisconnect:
        	mSocket.disConnect();
        break;

        case saReconnect:
            //Parse args, and call connect
            if(args.count() != 2)
            {
                Log(lError) << "Bad argument count for reconnecting socket in SocketActionThread";
            }
            else
            {
            	mSocket.connectByHostName(toInt(args[0]), args[1]);
            }
        break;
        default:
        break;
    }

    mIsFinished = true;
    Log(lDebug3)<<"Exiting socket action thread.";
}
}
