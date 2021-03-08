#pragma hdrstop
#include "dslSocketClient.h"
#include "dslStringUtils.h"
#include "dslLogger.h"
#include <sstream>
//---------------------------------------------------------------------------

namespace dsl
{
using namespace std;

SocketClient::SocketClient(int portNr, const string& hostname)
:
Socket(0),
mHostName(hostname),
mPortNumber(portNr),
mReceiver(*this, mIncomingMessages),
mSocketActionThread(*this)
{
    if(!hostname.size())
    {
        mHostName = "localhost";
    }

	//Initialize Winsock
	WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        int error = WSAGetLastError();
        Log(lError)<<"WSAStartup() failed. Error was: "<<error;
        return;
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
    return closeSocket();
}

int SocketClient::getPortNumber()
{
	return mPortNumber;
}

void SocketClient::assignParent(void* _parent)
{
	mParent = _parent;
}

void SocketClient::reConnect()
{
	SocketAction sa(saReconnect);
    sa.mArguments.append(mPortNumber);
	sa.mArguments.append(mHostName);
    mSocketActionThread.mAction = sa;
	mSocketActionThread.start();
}

void  SocketClient::connect(int portNr, const string& hostName)
{
    if(portNr != 0)
    {
        mPortNumber = portNr;
    }

    if(hostName.size() > 0)
    {
        mHostName = hostName;
    }

	SocketAction sa(saConnect);
    sa.mArguments.append(mPortNumber);
	sa.mArguments.append(mHostName);
    mSocketActionThread.mAction = sa;
	mSocketActionThread.start();
}

//Clean this up and only allow both IP/host address to be passed
bool SocketClient::connectByHostName(int portNr, const string& hostname)
{
	mPortNumber = portNr;
    mHostName = hostname;

    //Get serverIP
    string server_ip;

    //Get IP address if not given
    //get host IP
    struct hostent *host_entry;
    host_entry = gethostbyname(mHostName.c_str());

    if(host_entry && host_entry->h_addr_list)
    {
        // To convert an Internet network
        // address into ASCII string
        char* IPBuffer = inet_ntoa(*((struct in_addr*) host_entry->h_addr_list[0]));
        server_ip = string(IPBuffer);
    }
    else
    {
        Log(lError)<<"Failed to get IP for host: " << mHostName;
        return false;
    }

    return connectByIP(portNr, server_ip);
}

//Clean this up and only allow both IP/host address to be passed
bool SocketClient::connectByIP(int portNr, const string& hostIP)
{
	mPortNumber = portNr;
	string server_ip(hostIP);

    if(setupSocket() != true)
    {
        Log(lError) << "Failed to setup socket";
        return false;
    }


    struct sockaddr_in ServerAddress;

    /* Construct the server address structure */
    memset(&ServerAddress, 0, sizeof(ServerAddress));             	/* Zero out structure */
    ServerAddress.sin_family      = AF_INET;                     	/* Internet address family */
    ServerAddress.sin_addr.s_addr = inet_addr(server_ip.c_str());   /* Server IP address */
    ServerAddress.sin_port        = htons(portNr);                 	/* Server port */

    /* Establish the connection to the server */
    if (::connect(mSocketHandle, (struct sockaddr *) &ServerAddress, sizeof(ServerAddress)) < 0)
    {
        int error = WSAGetLastError();
        Log(lDebug3) << "Client socket connection failed. Error " << error << " occured.";
        mSocketHandle = NULL;
        return false;
    }

    //Worked out fine
    mIsBroken = false;

    Log(lInfo) << "Client socket connection to host: " << mHostName << " on port:" << portNr << " succeded";
    if(onConnect)
    {
    	onConnect(this);
    }

    //Start receiver thread
	mReceiver.start();
    return true;
}

bool SocketClient::requestByID(IPC_ID request_id)
{
    //Make sure the request has a good format
    stringstream request;
    request << "[" << dsl::toString(request_id) << "]";

    return sendRequest(request.str());
}

bool SocketClient::request(const string& request)
{
    //Make sure the request has a good format
    string req = "[" + request +  "]";
    return sendRequest(req);
}

bool SocketClient::sendRequest(const string& request)
{
    if(send(request) == -1)
    {
        Log(lWarning) << "Failed sending message to host: " << mHostName << " on port: " << mPortNumber;
        Log(lDebug2)  << "The message was: " << request;
        return false;
    }

	mLastSentData = request;
    if(onSendData)
    {
        onSendData(this);
    }
	return true;
}

}
