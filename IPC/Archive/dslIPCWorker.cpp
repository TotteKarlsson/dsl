#pragma hdrstop
#include <string>
#include "dslStringUtils.h"
#include "dslIPCWorker.h"
#include "dslIPCMessageBuilder.h"
#include "dslLogger.h"
using std::string;


namespace dsl
{
SocketWorker* createIPCWorker(int port_number, int socket_handle, void* server)
{
    SocketWorker* sWkr = new dslIPCWorker(port_number, socket_handle, (IPCServer*) server);
    if(sWkr)
    {
        Log(lInfo)<<"Created a dslIPCWorker, socket_handle ID is : "<<socket_handle;
        sWkr->send("[Connection was created]");
    }
    return sWkr;
}

SocketWorker *createIPCBroadcaster(int port_number, int socket_handle, void* server)
{
    SocketWorker* sWkr = new dslIPCWorker(port_number, socket_handle, (IPCServer*) server);
    sWkr->IgnoreIncomingMessages(true);

    if(sWkr)
    {
        Log(lInfo)<<"Created a dslIPCBroadcaster, socket_handle ID is : "<<socket_handle;
        sWkr->send("[Connection was created]");
    }
    return sWkr;
}

//----------------------------------------------------------------------------
dslIPCWorker::dslIPCWorker(int port_number, int socket_handle, IPCServer* server)
:
SocketWorker(port_number, socket_handle),
mTheServer(server)
{}

//----------------------------------------------------------------------------
dslIPCWorker::~dslIPCWorker()
{
    //shutdown();
}

void dslIPCWorker::run()
{
    Worker();
}
//----------------------------------------------------------------
void dslIPCWorker::Worker()
{
    IPCMessageBuilder aMessage(mLeftMessageDelimiter, mRightMessageDelimiter);
    while (!mIsTimeToDie)
    {
        //Check for messages, we block here
        int nBytes = receive();

        if(nBytes != -1)
        {
            //When a message is ready, post message to list
            while(mMessageBuffer.size())
            {
                char ch = mMessageBuffer.front();
                mMessageBuffer.pop_front();

                if(!aMessage.Build(ch))
                {
                    Log(lDebug4)<<"Character was discarded: \'"<<ch<<"\'";
                }

                if(aMessage.IsComplete())
                {
                    Log(lDebug3)<<"Received message: "<<aMessage.GetMessage()<<" in IPC Receiver("<<this->getSocketHandle()<<")";

                    if(mTheServer && mIgnoreIncomingMessages == false)
                    {
                        IPCMessage ipc_msg(-1, aMessage.GetMessage(), this->getSocketHandle());
                        mTheServer->postIPCMessage(ipc_msg);
                    }

                    aMessage.Reset();
                }
            }
            if(aMessage.IsComplete())
            {
                IPCMessage msg(-1, aMessage.GetMessage(),this->getSocketHandle());
                mTheServer->postIPCMessage(msg);
                aMessage.Reset();
            }
        }
        else
        {
            Log(lDebug3)<<"IPC inbox client was disconnected. Socket ID was: "<<this->getSocketHandle();
            mIsTimeToDie = true;
        }
    }
}
}
