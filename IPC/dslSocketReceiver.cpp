#pragma hdrstop
#include <string>
//#include "dslToggleSocketConnectionThread.h"
#include "dslStringUtils.h"
#include "dslSocketReceiver.h"
#include "dslIPCMessageBuilder.h"
#include "dslLogger.h"
using std::string;

namespace dsl
{

//----------------------------------------------------------------------------
SocketReceiver::SocketReceiver(Socket& s, MessageContainer& msgs)
:
mSocket(s),
mMessages(msgs)
{}

//----------------------------------------------------------------------------
SocketReceiver::~SocketReceiver()
{}

bool SocketReceiver::start(bool inThread)
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

void SocketReceiver::run()
{
	worker();
}
//----------------------------------------------------------------
void SocketReceiver::worker()
{
    Log(lInfo)<<"Entering socket receiver thread";

    while(!mIsTimeToDie)
    {
        IPCMessageBuilder aMessage('[',']');
        while(!aMessage.isComplete() && mIsTimeToDie == false)
        {
        	int nBytes = mSocket.receive();
            if(nBytes == -1 || nBytes == 0)
            {
                if(mSocket.onDisconnect)
                {
                    mSocket.onDisconnect(&mSocket);
                }
                mSocket.closeSocket();
                stop();
            }
            else
            {
            	deque<char>& inComing = mSocket.mMessageBuffer;
                if(mSocket.onReceiveData)
                {
                    mSocket.onReceiveData(&mSocket);
                }

                while(inComing.size())
                {
                    char ch = inComing.front();
                    inComing.pop_front();

                    if(!aMessage.build(ch))
                    {
                        Log(lDebug4) << "Character was discarded: \'" << ch << "\'";
                    }

                    if(aMessage.isComplete())
                    {
                        Log(lDebug) << "Received message: " << aMessage.getMessage() << " on socket id: " << mSocket.getSocketHandle();
                        mMessages.postMessage(aMessage.getMessage());
                    }
                }
            }
        }
    }

    Log(lInfo) << "Exiting socket receiver thread";
    mIsFinished = true;
}

}
