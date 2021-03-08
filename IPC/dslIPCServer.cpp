#pragma hdrstop
#include "dslSocketServer.h"
//#include "dslIPCReceiver.h"
#include "dslStringUtils.h"
#include "dslIPCServer.h"
#include "dslLogger.h"
#include "dslSocket.h"
#include "dslIPCMessageEnums.h"
//---------------------------------------------------------------------------

using namespace std;
using boost::mutex;
typedef mutex::scoped_lock ScopedLock;

namespace dsl
{

//IPCServer(int port = 0, const string& iniSection = gEmptyString, CreateWorkerFPtr createWorkerFPtr = NULL);
IPCServer::IPCServer(int serverPort, const string& iniSection, CreateWorker createWorkerPtr)
:
mMessageDelimiters('[', ']'),
mNrOfProcessedRequests(0),
mMessageProcessor(this),
mServerPort(serverPort, string("SERVER_PORT")),
mCreateWorkerFunction(createWorkerPtr),
mIniSection(iniSection),
mServerName(""),
mSocketProtocol(Socket::SocketProtocol::spTCP, string("SERVER_PROTOCOL")),
mSocketServer(*this)
{
//    mSocketServer.
    if(mServerPort != -1)
    {
        init(mServerPort, createWorkerPtr);
    }

    initProcessor();
    mSocketServer.onClientConnect 		= boost::bind(&IPCServer::privateOnClientConnect, 		this, _1);
    mSocketServer.onClientDisconnect 	= boost::bind(&IPCServer::privateOnClientDisconnect, 	this, _1);

}

IPCServer::~IPCServer()
{
    shutDown();
}

bool IPCServer::init(int pNumber, CreateWorker createWorkerPtr)
{
    Log(lInfo)<<"Setting up Socket server";

    if(pNumber > 0)
    {
		mServerPort = pNumber;
    }

    //Check that the port number is reasonable
    if(mServerPort < 1 || mServerPort > 100000)
    {
        Log(lError)<<"Error trying to init server using port number: "<<mServerPort<<endl;
        Log(lError)<<"Please assign valid port number"<<endl;
        return false;
    }

    return  initServer(pNumber, createWorkerPtr);
}

bool IPCServer::initServer(int pNumber, CreateWorker aCreateIPCWorkerFunction)
{
    Log(lDebug2)<<"Setting up server:"<<mServerName<<" on port: "<<pNumber;
    mServerPort = pNumber;

    if(mSocketServer.isRunning())
    {
        shutDownServer();
    }

    mSocketServer.setPortNumber(mServerPort);
//    mSocketServer.assignParent(this);
    mSocketServer.setSocketProtocol(mSocketProtocol.getValue());

    if(aCreateIPCWorkerFunction)
    {
	    mSocketServer.assignCreateWorkerFunctionPtr(aCreateIPCWorkerFunction);
    }
    else
    {
	    mSocketServer.assignCreateWorkerFunctionPtr(mCreateWorkerFunction);
    }

    mSocketServer.setIncomingMessageDelimiters(mMessageDelimiters.first, mMessageDelimiters.second);
    mSocketServer.start();

//    if(startRes != 1)
//    {
//        Log(lWarning)<<"Failed to start server "<<mServerName<<" on port number :"<<mServerPort;
//        return false;
//    }
//    Log(lInfo)<<"Server "<<mServerName<<" listening on port number: "<<mServerPort;
//    Sleep(100);
    return mSocketServer.isRunning();
}

void IPCServer::privateOnClientConnect(Socket* s)
{
    if(onClientConnect)
    {
		onClientConnect(s);
    }
}

void IPCServer::privateOnClientDisconnect(Socket* s)
{
    if(onClientDisconnect)
    {
		onClientDisconnect(s);
    }
}

bool IPCServer::saveParameters()
{
    return mProperties.write();
}

void IPCServer::setSocketProtocol(Socket::SocketProtocol proto)
{
    mSocketProtocol.setValue(proto);
    mSocketServer.setSocketProtocol(proto);
}

bool IPCServer::start(const int portNumber)
{
    return initServer(portNumber);
}

string IPCServer::getServerInfo()
{
    return mSocketServer.getServerInfo();
}

string IPCServer::getConnectionInfo()
{
    return mSocketServer.getServerInfo();
}

int IPCServer::servingPort()
{
    return mSocketServer.getPortNumber();
}

bool IPCServer::initProcessor()
{
    Log(lInfo)<<"Setting up Message Processing thread";

    //Processor thread for incoming messages
    mMessageProcessor.start();
    return true;
}

bool IPCServer::isProcessorRunning()
{
    return mMessageProcessor.isRunning();
}

bool IPCServer::shutDown()
{
    shutDownProcessor();
    shutDownServer();
    return true;
}

bool IPCServer::shutDownServer()
{
    mSocketServer.shutDown();
    int count(0);
    while(mSocketServer.isAlive())
    {
        Log(lInfo)<<"Shuting down the IPC server thread";
        Sleep(10);
        count++;
        if(count > 500)
        {
	        Log(lError)<< "Failed shutting down the IPC server thread";
            return false;
        }
    }

    return true;
}

bool IPCServer::shutDownProcessor()
{
    mMessageProcessor.shutDown();
    while(mMessageProcessor.isAlive())
    {
        Log(lInfo)<<"Shutting down the processing thread";
    }

    return true;
}

void IPCServer::stop()
{
    return mSocketServer.stop();
}

bool IPCServer::isRunning()
{
    return mSocketServer.isRunning();
}

int IPCServer::getMessageID(const string& msg)
{
    return dsl::getMessageID(msg);
}

bool IPCServer::readProperties()
{
    Log(lDebug3)<<("Reading ini parameters in CoreServer");
    mProperties.read();
    return true;
}

bool IPCServer::request(const string& smsg)
{
    IPCMessage msg(-1, smsg);

    //The message list are accessed by child threads
    ScopedLock lock(mListMutex);
        mMessages.push_back(msg);
    lock.unlock();

    Log(lDebug5)<<"Received message: "<<msg.getMessage();
    if(mMessages.size())
    {
        mListDataArrived.notify_one();
    }
    return true;
}

bool IPCServer::postRequest(IPCMessage& msg)
{
    //The message list are accessed by child threads
    ScopedLock lock(mListMutex);
        mMessages.push_back(msg);
    lock.unlock();

    Log(lDebug5)<<"Received message: "<<msg.getMessage();
    if(mMessages.size())
    {
        mListDataArrived.notify_one();
    }
    return true;
}

void IPCServer::processRequests()
{
    //Process each message in the message list
    while(mMessages.size())
    {
        ScopedLock lock(mListMutex);
        IPCMessage msg;
        msg = mMessages.front();
        mMessages.pop_front();
        lock.unlock();
        processRequest(msg);
    }
}

bool IPCServer::processRequest(IPCMessage& msg)
{
    //Server Mesages are processed here
    //Most messages will be processed in descendant classes
    if(msg.isPacked())
    {
        msg.unPack();
    }

    switch(msg.getCommand())
    {
        case cPause:
            Sleep(toInt(msg.getData()));
            msg.isProcessed(true);
        break;

        case cSetLogLevel:
            setLogLevel(toLogLevel(msg.getData()));
            msg.isProcessed(true);
        break;
        case cFlush:
            broadcast("[FLUSH]");
            msg.isProcessed(true);
        break;

        case cShutDown:
            //Signal to main thread that its time to shutdown.
            mSocketServer.shutDown();
            msg.isProcessed(true);
        break;

        default:
            msg.isProcessed(false);
        break;
    }
    return msg.isProcessed();
}

bool IPCServer::clientRequestResponse(const string& msg, int socketID)
{
    if(mSocketServer.isRunning())
    {
        string theMessage;
   	    theMessage = mMessageDelimiters.first + string(msg) + mMessageDelimiters.second;
    	if(mSocketServer.getNumberOfClients() > 0)
        {
        	mSocketServer.sendToWorker(theMessage, socketID);
	        Log(lDebug5)<<"Client request response:" << theMessage;
        }
        else
        {
	        Log(lDebug4)<<"No Server Clients. Was to respond to client with message:" << theMessage;
        }
    }
    else
    {
        Log(lWarning)<<"Socket server is not running (in client request response)";
    }
    return true;
}

bool IPCServer::broadcast(const string& msg)
{
    if(mSocketServer.isRunning())
    {
        string theMessage;
   	    theMessage = mMessageDelimiters.first + string(msg) + mMessageDelimiters.second;
    	if(mSocketServer.getNumberOfClients() > 0)
        {
        	mSocketServer.broadcast(theMessage);
	        Log(lDebug5)<<"Server broadcasted:" << theMessage;
        }
        else
        {
	        Log(lDebug4)<<"No Server Clients. Was to broadcast message:" << theMessage;
        }
    }
    else
    {
        Log(lWarning)<<"Socket server is not running (In Broadcast function)";
    }
    return true;
}

bool IPCServer::removeLostConnections()
{
    return mSocketServer.removeLostConnections();
}

size_t IPCServer::getNumberOfClients()
{
    return mSocketServer.getNumberOfClients();
}

void IPCServer::setIncomingMessageDelimiters(const char& left, const char& right)
{
    mMessageDelimiters.first = left;
    mMessageDelimiters.second = right;
}

bool IPCServer::setupProperties()
{
    LogLevel lvl = lDebug;
    Log(lDebug3)<<"Setting up ini parameters in CoreServer";
    mProperties.add( (BaseProperty*)         &mServerName.setup(     "SERVER_NAME",         "<none>",                   true));
    mProperties.add( (BaseProperty*)         &mServerPort.setup(     "SERVER_PORT",         -1,                         true));
    mProperties.add( (BaseProperty*)         &mSocketProtocol.setup( "SERVER_PROTOCOL",  Socket::spTCP,              true));
    return true;
}

void IPCServer::processNextRequest()
{
    IPCMessage msg;
    if(mMessages.size())
    {
        ScopedLock lock(mListMutex);
        msg = mMessages.front();
        mMessages.pop_front();
        lock.unlock();
    }

    //The following function is virtual and should be
    //over ridden in descendants
    processRequest(msg);
}

string IPCServer::getUsage()
{
    stringstream usage;
    usage <<"\n============ CoreServer functions ========"<<endl;
    usage <<"SHUTDOWN, SD : ShutDown Server"<<endl;
    usage <<"SET_LOG_LEVEL|lvl : Set log level (0-5)"<<endl;
    usage <<"PAUSE|time : Executes a PAUSE for time. Time is in milliseconds"<<endl;
    return usage.str();
}

bool IPCServer::logProcessResult(IPCMessage& msg)
{
    string logStr = msg.isProcessed() ? " was processed" : " was not processed";
    logStr += " by server ";
    logStr += mServerName;
    Log(lInfo)<<"Message \'"<<  msg.getID() <<"\'"<< logStr;
    return true;
}

bool IPCServer::sendResponse(const string& response, int origin)
{
    string resp;
    resp += "[";
    resp += response;
    resp +="]";

    return mSocketServer.sendToWorker(resp, origin);
}

bool IPCServer::sendResponse(bool response, int origin)
{
    return  response ?
            mSocketServer.sendToWorker("[true]", origin)
            : mSocketServer.sendToWorker("[false]", origin);
}

bool IPCServer::setLogLevel(LogLevel lvl)
{
    gLogger.setLogLevel(lvl);
    Log(lInfo)<<"Loglevel set to: "<< dsl::toString(lvl);
    return true;
}

string IPCServer::getUpTime()
{
    //Return the up time for the server
    double elapsed = difftime(time(nullptr), mStartTime);
    return getStringFromSeconds((time_t) elapsed);
}

}
