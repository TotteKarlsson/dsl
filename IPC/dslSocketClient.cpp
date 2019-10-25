#pragma hdrstop
#include "dslSocketClient.h"
#include "dslStringUtils.h"
#include "dslLogger.h"
#include <sstream>
//---------------------------------------------------------------------------

namespace dsl
{
using namespace std;

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

SocketClient::~SocketClient()
{}

string SocketClient::getRemoteHostName()
{
    return mHostName;
}

bool SocketClient::disConnect()
{
    return close();
}

bool SocketClient::reConnect()
{
    return connect(mPortNumber, mHostName);
}

int SocketClient::getPortNumber()
{
	return mPortNumber;
}

void SocketClient::assignParent(void* _parent)
{
	mParent = _parent;
}

bool SocketClient::connect(int portNr, const string& hostname)
{
	mPortNumber = portNr;
    mHostName =  hostname.size() ? hostname : string("localhost");

    struct sockaddr_in ServerAddress;
    string server_ip;

    if(mHostName == "localhost")
    {
        server_ip = "127.0.0.1";                /* First arg: server IP address (dotted quad) */
    }
    else
    {
        server_ip = mHostName;
    }

     if(setupSocket() != true)
    {
        Log(lInfo) << "Failed to connect client to " << mHostName << " on port number " << portNr;
        return false;
    }

    /* Construct the server address structure */
    memset(&ServerAddress, 0, sizeof(ServerAddress));             /* Zero out structure */
    ServerAddress.sin_family      = AF_INET;                     /* Internet address family */
    ServerAddress.sin_addr.s_addr = inet_addr(server_ip.c_str());   /* Server IP address */
    ServerAddress.sin_port        = htons(portNr);                 /* Server port */

    /* Establish the connection to the server */
    if (::connect(mSocketHandle, (struct sockaddr *) &ServerAddress, sizeof(ServerAddress)) < 0)
    {
        int error = WSAGetLastError();
        Log(lDebug3) << "Client socket connection failed. Error " << error << " occured.";
        mSocketHandle = -1;
        return false;
    }

    //Worked out fine
    mIsBroken = false;

    Log(lInfo) << "Client socket connection to host: " << mHostName << " on port:" << portNr << " succeded";

    if(onConnected)
    {
    	onConnected(this);
    }
	mReceiver.start();
    return true;
}

bool SocketClient::requestByID(IPC_ID request_id)
{
    //Make sure the request has a good format
    stringstream request;
    request << "[" << dsl::toString(request_id) << "]";

    if(send(request.str()) == -1)
    {
        Log(lInfo) << "Sending request failed";
        return false;
    }

    return true;
}

bool SocketClient::request(const string& request)
{
    //Make sure the request has a good format
    string req = "[" + request +  "]";

    if(send(req) == -1)
    {
        Log(lInfo) << "Failed sending request: " << req;
        return false;
    }

	return true;
}

}
