#pragma hdrstop
#include "dslStringUtils.h"
#include "dslSocketClient.h"
#include "dslLogger.h"
#include "dslIPCMessageBuilder.h"

namespace dsl
{

SocketClient::SocketClient(int portNr, const string& hostname) :
Socket(-1),
mPortNumber(portNr),
mReceiver(*this, mIncomingMessages),
mToggleConnection(NULL)
{
    if(!hostname.size())
    {
        mHostName = "localhost";
    }
}

bool SocketClient::disConnect()
{
    return close();
}

bool SocketClient::reConnect()
{
    return connect(mPortNumber, mHostName);
}

bool SocketClient::connect(int portNr, const string& hostname)
{
	mPortNumber = portNr;
    mHostName =  hostname.size() ? hostname : string("localhost");

    struct sockaddr_in ServerAddress;             /* Echo server address */
    string servIP;

    if(mHostName == "localhost")
    {
        servIP = "127.0.0.1";                /* First arg: server IP address (dotted quad) */
    }
    else
    {
        servIP = mHostName;
    }

     if(setupSocket() != true)
    {
        Log(lInfo)<<"Failed to connect client to "<<mHostName<<" on port number "<<portNr;
        return false;
    }

    /* Construct the server address structure */
    memset(&ServerAddress, 0, sizeof(ServerAddress));             /* Zero out structure */
    ServerAddress.sin_family      = AF_INET;                     /* Internet address family */
    ServerAddress.sin_addr.s_addr = inet_addr(servIP.c_str());   /* Server IP address */
    ServerAddress.sin_port        = htons(portNr);                 /* Server port */

    /* Establish the connection to the server */
    if (::connect(mSocketHandle, (struct sockaddr *) &ServerAddress, sizeof(ServerAddress)) < 0)
    {
        int error = WSAGetLastError();
        Log(lDebug3)<<"Client socket connection failed. Error "<<error<<" occured.";
        mSocketHandle = -1;
        return false;
    }

    //Worked out fine
    mIsBroken = false;

    Log(lInfo)<<"Client socket connection to host: "<<mHostName<<" on port:"<<portNr<<" succeded";

    if(onConnected)
    {
    	onConnected();
    }

    return true;
}

bool SocketClient::requestByID(IPC_ID request)
{
    //Make sure the request has a good format
    string req = "[";
    req += dsl::toString(request).c_str();
    req += "]";

    if(send(req) == -1)
    {
        Log(lInfo)<<"Sending request failed";
        return false;
    }

    return true;
//    if(!waitForResponse)
//    {
//        return "";
//    }
//
//    IPCMessageBuilder aMessage('[',']');
//    while(!aMessage.isComplete())
//    {
//        if(receive() != -1)
//        {
//            while(mMessageBuffer.size())
//            {
//                char ch = mMessageBuffer.front();
//                mMessageBuffer.pop_front();
//
//                if(!aMessage.build(ch))
//                {
//                    Log(lInfo)<<"Character was discarded: \'"<<ch<<"\'";
//                }
//
//                if(aMessage.isComplete())
//                {
//                    Log(lInfo)<<"Received message: "<<aMessage.getMessage()<<" on socket id: "<<this->getSocketHandle();
//                }
//            }
//        }
//        else
//        {
//            //The connection is broken
//            mMessageBuffer.clear();
//            Log(lInfo)<<"Connection was broken";
//            return "[NO RESPONSE]";
//        }
//    }
//
//    return aMessage.getMessage();
}

bool SocketClient::request(const string& request)
{
    //Make sure the request has a good format
    string req = "[";
    req += request;
    req += "]";

    if(send(req) == -1)
    {
        Log(lInfo)<<"Failed sending request: "<<req;
        return false;
    }

//    if(!waitForResponse)
//    {
//        return false;
//    }

//    IPCMessageBuilder aMessage('[',']');
//    while(!aMessage.isComplete())
//    {
//        if(receive() != -1)
//        {
//            while(mMessageBuffer.size())
//            {
//                char ch = mMessageBuffer.front();
//                mMessageBuffer.pop_front();
//
//                if(!aMessage.build(ch))
//                {
//                    Log(lInfo)<<"Character was discarded: \'"<<ch<<"\'";
//                }
//
//                if(aMessage.isComplete())
//                {
//                    Log(lDebug3)<<"Received message: "<<aMessage.getMessage()<<" on socket id: "<<this->getSocketHandle();
//                }
//            }
//        }
//        else
//        {
//            //The connection is broken
//            mMessageBuffer.clear();
//            Log(lInfo)<<"Connection was broken";
//            return "[NO RESPONSE]";
//        }
//    }
//
//    return aMessage.getMessage();
	return true;
}

}
