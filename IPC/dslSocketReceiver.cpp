#pragma hdrstop
#include <string>
#include "dslToggleSocketConnectionThread.h"
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
            if(mSocket.receive() != -1)
            {
            	deque<char>& inComing = mSocket.getIncomingDataBuffer();
                while(inComing.size())
                {
                    char ch = inComing.front();
                    inComing.pop_front();

                    if(!aMessage.build(ch))
                    {
                        Log(lInfo)<<"Character was discarded: \'"<<ch<<"\'";
                    }

                    if(aMessage.isComplete())
                    {
                        Log(lDebug)<<"Received message: "<<aMessage.getMessage()<<" on socket id: "<<mSocket.getSocketHandle();
                        mMessages.postMessage(aMessage.getMessage());
                    }
                }
            }
            else
            {
                //The connection is broken or closed
                Log(lInfo)<<"Connection was closed";
                mIsTimeToDie = true;
                if(mSocket.onDisconnected)
                {
					mSocket.onDisconnected();
                }
            }
        }
    }

    Log(lInfo)<<"Exiting socket receiver thread";
    mIsFinished = true;
}

}
