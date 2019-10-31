#pragma hdrstop
#include "dslSocket.h"
#include "dslLogger.h"
#include "dslStringUtils.h"
//---------------------------------------------------------------------------

using std::endl;
using dsl::toString;

namespace dsl
{
Socket::Socket(int socket_handle)
:
mSocketHandle(socket_handle),
mIsBroken(false),
mSocketAddressFamily(sfInet),
mSocketType(stStream),
mSocketProtocol(spTCP)
{}

Socket::~Socket()
{}

string Socket::getLastSentData()
{
    return mLastSentData;
}

void Socket::setSocketProtocol(SocketProtocol proto)
{
    mSocketProtocol = proto;
    switch(mSocketProtocol)
    {
        case spTCP:  mSocketType = stStream; break;
        case spUDP:  mSocketType = stDGram;  break;
    }
}

bool Socket::isConnected()
{
    if(mIsBroken)
    {
        return false;
    }

    return (send("") >= 0) ? true : false;
}

bool Socket::setupSocket()
{
    if(hasHandle())
    {
        close();
    }

    if (WSAStartup(MAKEWORD(2, 0), &mWSAData) != 0) /* Load Winsock 2.0 DLL */
    {
        int error = WSAGetLastError();
        Log(lInfo) << "WSAStartup failed. Error was: " << error << endl;
        return false;
    }

    /* Create a reliable, stream socket using TCP */
    if( (mSocketHandle = socket(mSocketAddressFamily, mSocketType, mSocketProtocol)) < 0)
    {
        int error = WSAGetLastError();
        Log(lInfo) << "Socket handle creation failed. Error " << error << " occured.";
        return false;
    }

    return true;
}

int Socket::close()
{
    int retVal = 0;
    if(mSocketHandle != -1)
    {
        int retVal = closesocket(mSocketHandle);
        if(retVal != 0)
        {
            Log(lError)<<"Socket close error:  ("<< retVal<<") :" <<strerror(retVal);
        }
        else
        {
            Log(lInfo)<<"Socket with handle "<<mSocketHandle<<" was closed";
            mSocketHandle = -1;
            mIsBroken = true;
        }
    }
    return retVal;
}

int Socket::receive(long bytes)
{
    long bSize = bytes;
    char *msg = new char[bSize];

    //This is a blocking call, execute in a thread.
    int nReceived = recv(mSocketHandle, msg, bSize, 0);

    //If == -1, then the socket is broken
    if (nReceived == -1)
    {
        delete [] msg;
        mIsBroken = true;
        close();
        return -1;
    }

    //If == 0, then the socket was closed
    if (nReceived == 0)
    {
        close();
        delete [] msg;
        return 0;
    }

    for(int i = 0; i < nReceived; i++)
    {
        mMessageBuffer.push_back(msg[i]);
    }
    delete [] msg;
    return nReceived;
}

int Socket::send(const string& msg)
{
    if(mSocketHandle == -1)
    {
        return -1;
    }

    size_t retval = ::send(mSocketHandle, msg.c_str(), msg.length(), 0);
    if(retval < 0)
    {
        if(errno == EPIPE)
        {
            // don't print anything; this is a normal disconnect
            Log(lInfo) << "Socket was disconnected";
        }
        else
        {
            Log(lInfo) << "Socket send error: " << errno ;
        }
    }
    return retval;
}

string Socket::getReceivedBufferContent()
{
    string content;
	for(int i = 0; i < mMessageBuffer.size(); i++)
    {
        content += mMessageBuffer[i];
    }
    return content;
}

deque<char>& Socket::getIncomingDataBuffer()
{
	return mMessageBuffer;
}

bool Socket::hasHandle()
{
    return (mSocketHandle != -1);
}

int Socket::getSocketID()
{
    return mSocketHandle;
}

int Socket::getSocketHandle()
{
    return mSocketHandle;
}

string Socket::getInfo()
{
    return "Some socket info...";
}


}
