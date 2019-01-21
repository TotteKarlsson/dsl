#pragma hdrstop
//#include "dslIPCWorker.h"
#include "dslStringUtils.h"
#include "dslLogClient.h"
#include "dslSocketClient.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------

namespace dsl
{
LogClient::LogClient()
:
mSocketClient(nullptr),
mProcessThread(nullptr),
mToggleSocket(nullptr),
mLogLevel(lDebug)
{

}

LogClient::~LogClient()
{
    Log(lDebug3)<<"Log client is shutting down..";
    delete mSocketClient;
    delete mProcessThread;
}

bool LogClient::Init(int serverPort, const string& hostname, bool connectOnInit)
{
    Log(lDebug3)<<"Setting up log client";

    if(!mSocketClient)
    {
        mSocketClient = new SocketClient(serverPort, hostname);
        mToggleSocket.setSocket(mSocketClient);
        mSocketClient->assignParent(this);
    }
    else
    {
        mSocketClient->close();
    }

    StartProcessing();

    if(connectOnInit)
    {
        mToggleSocket.start();
    }

    return true;
}

string LogClient::GetClientInfo()
{
    return mSocketClient->getInfo();
}

void LogClient::ToggleConnection()
{
    if(!mToggleSocket.isRunning())
        mToggleSocket.start();
}

bool LogClient::StartProcessing()
{
    if(!mProcessThread)
    {
        mProcessThread = new LogMessageProcessor(mSocketClient, mMessageContainer);
        mProcessThread->AssignParent(this);
        mProcessThread->Start();
    }
    return true;
}

bool LogClient::IsConnected()
{
    if(mSocketClient)
    {
        return mSocketClient->isConnected();
    }
    return false;
}

bool LogClient::ShutDown()
{
    if(mProcessThread)
    {
        Log(lDebug3)<<"Shutting down Processing thread in LogClient";
        mProcessThread->ShutDown();
        //delete mProcessThread;
        //mProcessThread = nullptr;
    }

    if(mSocketClient)
    {
        Log(lDebug3)<<"Closing socket in LogClient";
        mSocketClient->close();
        //delete mSocketClient;
        //mSocketClient = nullptr;
    }

    Log(lDebug3)<<"LogClient was shut down";
    mIsActive = false;
    return true;
}

bool LogClient::IsFinished()
{
    return !mIsActive;
}

bool LogClient::Connect(int serverPort, const string& host)
{
    return Init(serverPort, host, true);
}

bool LogClient::ReConnect()
{
    return !mToggleSocket.isRunning() ? mToggleSocket.start() : false;
}

bool LogClient::Disconnect()
{
    if(mSocketClient)
    {
        mSocketClient->close();
        return !mSocketClient->isConnected();
    }
    return true;
}

void LogClient::PostLogMessage(const string& msg)
{
    string socketMessage = msg;
    mMessageContainer.postMessage(socketMessage);
}

bool LogClient::SetLogLevel(int lvl)
{
    mLogLevel = lvl;
    Log(lInfo)<<"Loglevel set to "<<mLogLevel;
    return true;
}

bool LogClient::StopProcessing()
{
    if(mProcessThread->isAlive())
    {
        mProcessThread->Stop();
    }
    return true;
}


}
