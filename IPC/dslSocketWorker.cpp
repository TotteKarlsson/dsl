#pragma hdrstop
#include "dslStringUtils.h"
#include "dslSocketWorker.h"
#include "dslLogger.h"
//----------------------------------------------------------------

namespace dsl
{

using namespace std;
SocketWorker::SocketWorker(int portNr, SOCKET sock_handle)
:
Socket(sock_handle),
mPortNumber(portNr),
mIgnoreIncomingMessages(false),
mLeftMessageDelimiter('\n'),
mRightMessageDelimiter('\n')
{
    mLabel    = "SocketConnection [" + toString(sock_handle) + "]";
    Log(lDebug3)<<"Created a socket worker using port number:"<<mPortNumber<<" and socket handle "<<mSocketHandle;
}

//----------------------------------------------------------------
SocketWorker::~SocketWorker()
{
    Log(lDebug) << "Closing socket worker on port number: " << mPortNumber;
    closeSocket();
}

string SocketWorker::getInfo()
{
    stringstream info;
    info << "socket_handle=" + dsl::toString((int) mSocketHandle);
    return info.str();
}

int SocketWorker::getPortNumber()
{
    return mPortNumber;
}

void SocketWorker::ignoreIncomingMessages(bool doIt)
{
    mIgnoreIncomingMessages = doIt;
}

void SocketWorker::setMessageDelimiters(const char& left, const char& right)
{
    mLeftMessageDelimiter = left;
    mRightMessageDelimiter = right;
}


}
