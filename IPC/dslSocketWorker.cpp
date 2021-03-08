#pragma hdrstop
#include "dslStringUtils.h"
#include "dslSocketWorker.h"
#include "dslLogger.h"
//----------------------------------------------------------------

namespace dsl
{
SocketWorker::SocketWorker(int portNr, int sock_handle)
:
Socket(sock_handle),
mPortNumber(portNr),
mIgnoreIncomingMessages(false),
mLeftMessageDelimiter('\n'),
mRightMessageDelimiter('\n')
{
    mLabel    = "SocketConnection [" + toString(sock_handle) + "]";
    Log(lInfo)<<"Created a socket worker using port number:"<<mPortNumber<<" and socket handle "<<mSocketHandle;
}

//----------------------------------------------------------------
SocketWorker::~SocketWorker()
{
    Log(lInfo)<<"Killing socket worker on port number:"<<mPortNumber;
    close();
}

string SocketWorker::getInfo()
{
    string info = "Socket Worker Information \n";
    info += "mSocketHandle = " + dsl::toString((int) mSocketHandle);
    info += "\n";
    return info;
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
