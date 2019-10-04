#pragma hdrstop
#include <winsock.h>

#include "dslStringUtils.h"
#include "dslSocketServer.h"
#include "dslLogger.h"
#include "dslIPCMessage.h"
#include "dslIPCMessageBuilder.h"

#define MAXHOSTNAME 255

/* Maximum outstanding connection requests */
#define MAXPENDING 5

using boost::mutex;
typedef mutex::scoped_lock ScopedLock;

namespace dsl
{

int SocketServer::serverCount = 0;
void HandleTCPClient(int clntSocket);   /* TCP client handling function */

//----------------------------------------------------------------
SocketServer::SocketServer(int port_nr):
Socket(-1),
CreateWorkerFunction(nullptr),
mLeftMessageDelimiter('\n'),
mRightMessageDelimiter('\n'),
mSocketProtocol(spTCP),
mParent(nullptr)
{
    SetPortNumber(port_nr);
    serverCount++;
    mLabel            = "SocketServer[" + toString(serverCount) + "]";
}

//----------------------------------------------------------------
SocketServer::~SocketServer()
{
    close();
    ShutDown();
    serverCount--;
}

void SocketServer::ShutDown()
{
    //Call close on the socket
    Thread::stop();    //Sets time to die to true
    close();

    ScopedLock lock(mWorkerListMutex);
    while(mWorkerList.size() > 0)
    {
        SocketWorker *wkr = mWorkerList.front();
        mWorkerList.pop_front();
        if(wkr)
        {
            wkr->stop();
            wkr->close();
            while(wkr->isRunning())
            {
                ;
            }

            delete wkr;
        }
    }

    lock.unlock();
}

bool SocketServer::Stop()
{
    //Stopping the server implies to shutdown all connections
    //and also shutdown the listening for connections thread
    ShutDown();
    return true;
}

void SocketServer::run()
{
    Worker();
}

//Return value of 1 is success
int SocketServer::Start()
{
    if(mPortNumber < 1)
    {
       Log(lError)<<"The socket server could not start becuase the portnumber is not set!\n";
       return -1;
    }

    if (WSAStartup(MAKEWORD(2, 0), &mWSAData) != 0)     /* Load Winsock 2.0 DLL */
    {
        int error = WSAGetLastError();
        Log(lError)<<"WSAStartup() failed. Error was: "<<error;
        return error;
    }

    /* Create socket for incoming connections */
    SocketType sType;
    switch(mSocketProtocol)
    {
        case spTCP:            sType = stStream;        break;
        case spUDP:            sType = stDGram;         break;
        default:               sType = stStream;		break;
    }

    if ((mSocketHandle = socket(PF_INET, sType, mSocketProtocol)) < 0)
    {
        int error = WSAGetLastError();
        Log(lError)<<"Socket creation failed. Error was: "<<error;
        return error;
    }

    /* Construct local address structure */
    memset(&mServerAddress, 0, sizeof(mServerAddress));       /* Zero out structure */
    mServerAddress.sin_family = AF_INET;                    /* Internet address family */
    mServerAddress.sin_addr.s_addr = htonl(INADDR_ANY);     /* Any incoming interface */
    mServerAddress.sin_port = htons(mPortNumber);              /* Local port */

    /* Bind to the local address */
    if ( ::bind(mSocketHandle, (struct sockaddr *) &mServerAddress, sizeof(mServerAddress)) < 0)
    {
        int error = WSAGetLastError();
        Log(lError)<<"Socket Bind Error on socket port nr: "<<mPortNumber<<". Error was: "<<error;
        return error;
    }

    /* Mark the socket so it will listen for incoming connections */
    if (listen(mSocketHandle, MAXPENDING) < 0 && mSocketProtocol != spUDP)
    {
        int error = WSAGetLastError();
        Log(lError)<<"Socket Listen Call Failed. Error was: "<<error;
        return error;
    }

    return Thread::start();
}

void SocketServer::SetIncomingMessageDelimiters(const char& left, const char& right)
{
    mLeftMessageDelimiter   = left;
    mRightMessageDelimiter  = right;
}

//----------------------------------------------------------------
bool SocketServer::Broadcast(const string& msg)
{
    boost::mutex::scoped_lock lock(mWorkerListMutex);
    for (list<SocketWorker *>::iterator wkr = mWorkerList.begin(); wkr != mWorkerList.end(); wkr++)
    {
        SocketWorker* aWorker = (*wkr);
        if(!aWorker)
            break;

        if(aWorker->isConnected())
        {
            (aWorker)->send(msg);
        }
        else
        {
            delete aWorker;
            wkr = mWorkerList.erase(wkr);
        }
    }

    if(mSocketProtocol == spUDP)
    {
        send("Test");
    }
    return true;
}

void SocketServer::RetireWorker(SocketWorker* aWorker)
{
    ScopedLock lock(mWorkerListMutex);
    mWorkerList.remove( aWorker );
    delete aWorker;
}

SocketWorker* SocketServer::GetFirstWorker()
{
    boost::mutex::scoped_lock lock(mWorkerListMutex);
    return mWorkerList.size() ?    *(mWorkerList.begin()) : nullptr;
}

//----------------------------------------------------------------
bool SocketServer::SendToWorker(const string& msg, int socketID)
{
    bool success = false;
    ScopedLock lock(mWorkerListMutex);
    for (list<SocketWorker *>::iterator wkr = mWorkerList.begin(); wkr != mWorkerList.end(); wkr++)
    {
        if( (*wkr)->getSocketID() == socketID && (*wkr)->isConnected() )
        {
            (*wkr)->send(msg);
            success = true;
        }
    }
    return success;
}

//----------------------------------------------------------------
void SocketServer::Worker() //Waiting for connections, or UDP data grams
{
    mIsWorking = true;
    mIsStarted = true;

    while(!mIsTimeToDie)
    {
        //Blocking stuff
        switch(mSocketProtocol)
        {
            case spTCP:
                if(TCPWorker() == 1)
                {
                    Log(lInfo)<<"Socket client was accepted..";
                }
                else
                {
                    Log(lError)<<"There was a problem accepting socket client.";
                }
            break;

            case spUDP:
                UDPWorker();
            break;
            default:
                Log(lError)<<"No socket protocol selected.. Exiting";
                mIsTimeToDie = true;
            break;
        }
    }

    mIsWorking = false;
    mIsFinished = true;
}

int SocketServer::TCPWorker()
{
    int clntSock;
    int clntLen = sizeof(mClientAddress);

    //Blocking...
    Log(lInfo)<<"Waiting for new socket clients";
    if ((clntSock = accept(mSocketHandle, (struct sockaddr *) &mClientAddress, &clntLen)) < 0)
    {
        //If it is time to die, then this is normal. If not, we ahve a problem
        if(!mIsTimeToDie)
        {
            Log(lError)<<"Socket function accept() failed";
        }
        return -1;
    }
    else
    {
       // got a connection
        Log(lDebug3)<<"A socket client connected";
        if(CreateWorkerFunction != nullptr)
        {
            //This function creates a SocketWorker..
            SocketWorker *wkr = CreateWorkerFunction(mPortNumber, clntSock, mParent);

            ScopedLock lock(mWorkerListMutex);
                mWorkerList.push_back(wkr);
            lock.unlock();

            wkr->SetMessageDelimiters(mLeftMessageDelimiter, mRightMessageDelimiter);
            wkr->start();
            Log(lDebug)<< "A socket worker was created.";
         }
        else
        {
            Log(lError)<< "Create client worker function is not assigned in SocketServer. Client will not be served..";
        }
        return 1;
    }
}

int SocketServer::UDPWorker()
{
    // listen to messages here.
    IPCMessageBuilder aMessage('[',']');

    //Check for messages
    int nBytes = receive();
    if(nBytes != -1 || nBytes != 0)
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

            if(aMessage.isComplete())
            {
                int msgID             = 0;//GetMessageID(aMessage.GetMessage()); //A virtual function
                IPCMessage msg     = IPCMessage(msgID, aMessage.getMessage(), this->getSocketHandle());
                //mServer->PostMessage(msg);
                aMessage.reset();
            }
        }
    }
    else
    {
        stop();
    }

    return 0;
}

bool SocketServer::RemoveLostConnections()
{
    ScopedLock lock(mWorkerListMutex);
    bool bMore = true;
    while ( bMore )
    {
        bMore = false;
        for ( list<SocketWorker *>::iterator wkr = mWorkerList.begin(); wkr != mWorkerList.end(); wkr++ )
        {
            if ( !(*wkr)->isConnected() )
            {
                delete *wkr;
                mWorkerList.remove( *wkr );

                bMore = true;
                break;
            }
        }
    }
    return true;
}

string SocketServer::GetServerInfo()
{
    RemoveLostConnections();
    int nrOfClients = GetNumberOfClients();

    stringstream info;
    info<<"Is accepting connections: \n";
    info<<"Listening Port = "<<GetPortNumber()<<endl;
    info<<"Nr of Clients = "<<nrOfClients<<endl;
    boost::mutex::scoped_lock lock(mWorkerListMutex);
    for ( list<SocketWorker *>::iterator wkr = mWorkerList.begin(); wkr != mWorkerList.end(); wkr++ )
    {
        info<<(*wkr)->GetInfo()<<endl;
    }

    return info.str();
}

//----------------------------------------------------------------------------
string SocketServer::GetProcessInfo( string indent )
{
    string msg = "Process info....";
//    msg += Thread::GetProcessInfoAsString();
    return msg;
}

}
