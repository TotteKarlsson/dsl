#pragma hdrstop
#include <string>
#include "dslLogger.h"
#include "dslStringUtils.h"
#include "dslIPCMessageBuilder.h"
#include "dslIPCServer.h"
#include "dslIPCReceiver.h"

using namespace std;

#undef GetMessage
namespace dsl
{

SocketWorker* createIPCReceiver(int portNr, int socketHandle, void* server)
{
    SocketWorker* sWkr = new IPCReceiver(portNr, socketHandle, (IPCServer*) server);
    if(sWkr)
    {
        Log(lInfo)<<"Created an IPCReceiver. Socket Handle ID is : "<<socketHandle<<"\n";
        sWkr->send("[Connection was created!]");
    }
    return sWkr;
}

//----------------------------------------------------------------------------
IPCReceiver::IPCReceiver(int portNr, int socketHandle, IPCServer* server)
:
SocketWorker(portNr, socketHandle),
mServer(server)
{}

//----------------------------------------------------------------------------
IPCReceiver::~IPCReceiver()
{
    stop();
}

string IPCReceiver::getRemoteHostName()
{
    return "<none>";
}


bool IPCReceiver::start(bool inThread)
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

void IPCReceiver::run()
{
    worker();
}
//----------------------------------------------------------------
void IPCReceiver::worker()
{
    IPCMessageBuilder aMessage('[',']');
    while( !isTimeToDie() )
    {
        //Check for messages
        int nBytes = receive();
        if(nBytes != -1)
        {
            //When a message is ready, post message to list
            while(mMessageBuffer.size())
            {
                char ch = mMessageBuffer.front();
                mMessageBuffer.pop_front();

                if(!aMessage.build(ch))
                {
                    Log(lDebug)<<"Character was discarded in IPCReceiver: \'"<<ch<<"\'"<<endl;
                }

                if(aMessage.isComplete() )
                {
                    int msgID          = getMessageID(aMessage.getMessage()); //A virtual function
                    IPCMessage msg     = IPCMessage(msgID, aMessage.getMessage(), this->getSocketHandle());
                    if(mServer)
                    {
                        mServer->postRequest(msg);
                    }
                    send("ACK");
                    aMessage.reset();
                }
            }
        }
        else
        {
            stop();
        }
    }
    mSocketHandle = -1;
}

}
