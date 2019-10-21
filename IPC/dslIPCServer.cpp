#pragma hdrstop
#include "dslSocketServer.h"
//#include "dslIPCReceiver.h"
#include "dslStringUtils.h"
#include "dslIPCServer.h"
#include "dslLogger.h"
#include "dslSocket.h"
//---------------------------------------------------------------------------

using boost::mutex;
typedef mutex::scoped_lock ScopedLock;

namespace dsl
{

IPCServer::IPCServer(int serverPort, const string& iniSection, CreateWorker createWorkerPtr)
:
mMessageDelimiters('[', ']'),
mNrOfProcessedRequests(0),
mMessageProcessor(this),
mServerPort(serverPort, string("SERVER_PORT")),
mCreateWorkerFunction(createWorkerPtr),
mIniSection(iniSection),
mServerName(""),
mSocketProtocol(Socket::SocketProtocol::spTCP, string("SERVER_PROTOCOL"))

{
    if(mServerPort != -1)
    {
        init(mServerPort, createWorkerPtr);
    }
    initProcessor();
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

    mSocketServer.SetPortNumber(mServerPort);
    mSocketServer.AssignParent(this);
    mSocketServer.SetSocketProtocol(mSocketProtocol.getValue());

    if(aCreateIPCWorkerFunction)
    {
	    mSocketServer.AssignCreateWorkerFunctionPtr(aCreateIPCWorkerFunction);
    }
    else
    {
	    mSocketServer.AssignCreateWorkerFunctionPtr(mCreateWorkerFunction);
    }

    mSocketServer.SetIncomingMessageDelimiters(mMessageDelimiters.first, mMessageDelimiters.second);
    int startRes = mSocketServer.Start();

    if(startRes != 1)
    {
        Log(lWarning)<<"Failed to start server "<<mServerName<<" on port number :"<<mServerPort;
        return false;
    }
    Log(lInfo)<<"Server "<<mServerName<<" listening on port number: "<<mServerPort;

    return true;
}

bool IPCServer::saveParameters()
{
    return mProperties.write();
}

void IPCServer::setSocketProtocol(Socket::SocketProtocol proto)
{
    mSocketProtocol.setValue(proto);
    mSocketServer.SetSocketProtocol(proto);
}

bool IPCServer::start(const int portNumber)
{
    return initServer(portNumber);
}

string IPCServer::getServerInfo()
{
    return mSocketServer.GetServerInfo();
}

string IPCServer::getConnectionInfo()
{
    return mSocketServer.GetServerInfo();
}

int IPCServer::servingPort()
{
    return mSocketServer.GetPortNumber();
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
    mSocketServer.ShutDown();
    while(mSocketServer.isAlive())
    {
        Log(lInfo)<<"Shutting down the server thread";
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

bool IPCServer::stop()
{
    return mSocketServer.Stop();
}

bool IPCServer::isRunning()
{
    return mSocketServer.isRunning();
}

int IPCServer::getMessageID(const string& msg)
{
    return getIPCMessageID(msg);
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

    Log(lDebug5)<<"Received message: "<<msg.GetMessage();
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

    Log(lDebug5)<<"Received message: "<<msg.GetMessage();
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

    switch(msg.GetCommand())
    {
        case cPause:
            Sleep(toInt(msg.getData()));
            msg.IsProcessed(true);
        break;

        case cSetLogLevel:
            setLogLevel(toLogLevel(msg.getData()));
            msg.IsProcessed(true);
        break;
        case cFlush:
            broadcast("[FLUSH]");
            msg.IsProcessed(true);
        break;

        case cShutDown:
            //Signal to main thread that its time to shutdown.
            mSocketServer.ShutDown();
            msg.IsProcessed(true);
        break;

        default:
            msg.IsProcessed(false);
        break;
    }
    return msg.IsProcessed();
}

bool IPCServer::broadcast(const string& msg)
{
    if(mSocketServer.isRunning())
    {
        string theMessage;
   	    theMessage = mMessageDelimiters.first + string(msg) + mMessageDelimiters.second;
    	if(mSocketServer.GetNumberOfClients() > 0)
        {
        	mSocketServer.Broadcast(theMessage);
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
    return mSocketServer.RemoveLostConnections();
}

int IPCServer::getNumberOfClients()
{
    return mSocketServer.GetNumberOfClients();
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
    string logStr = msg.IsProcessed() ? " was processed" : " was not processed";
    logStr += " by server ";
    logStr += mServerName;
    Log(lInfo)<<"Message \'"<<  msg.GetID() <<"\'"<< logStr;
    return true;
}

bool IPCServer::sendResponse(const string& response, int origin)
{
    string resp;
    resp += "[";
    resp += response;
    resp +="]";

    return mSocketServer.SendToWorker(resp, origin);
}

bool IPCServer::sendResponse(bool response, int origin)
{
    return  response ?
            mSocketServer.SendToWorker("[true]", origin)
            : mSocketServer.SendToWorker("[false]", origin);
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
    time_t elapsed = difftime(time(nullptr), mStartTime);
    return getStringFromSeconds(elapsed);
}

}
