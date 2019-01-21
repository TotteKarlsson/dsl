#pragma hdrstop
#include "dslTMemoSocketServer.h"
#include "dslStringUtils.h"
#include "dslLogger.h"
#include "dslIPCMessageEnums.h"
#include "dslIPCUtils.h"
//--------------------------------------------------------------------------
#pragma package(smart_init)

using boost::mutex;

using namespace dsl;
TMemoSocketServer::TMemoSocketServer(dsl::IniFile* iniFile, const string& iniSection)
:
dsl::IPCServer(-1, iniSection),
mLogMemo(nullptr)
{
//    mParas.setSection(iniSection);
    SetupIniParameters();
    ReadIniParameters();
}

TMemoSocketServer::TMemoSocketServer(const string& iniFName, const string& iniSection)
:
IPCServer(-1, iniSection),
mLogMemo(nullptr)
{
    //mParas.setSection(iniSection);
    SetupIniParameters();
    ReadIniParameters();
}

TMemoSocketServer::~TMemoSocketServer()
{
    shutDown();

//    if(mIniFile)
//    {
//        mParas.write();
//        mIniFile->save();
//    }
}

bool TMemoSocketServer::Start(int portNR)
{
    //Initialize servers..
    return (portNR < 0 || !init(portNR)) ? false : true;
}

bool TMemoSocketServer::processMessage(IPCMessage& msg)
{
    if(msg.isPacked())
    {
        msg.unPack();
    }

    mutex::scoped_lock lock(mMemoMutex);
    //Choose what to show in the log window

    if(msg.GetID() != -1)
    {
        string aMsg = msg.GetMessageBody();
        vector<string> lines = splitString(aMsg, "\n");
        for(u_int i = 0; i < lines.size(); i++)
        {
            mLogMemo->Lines->Add(lines[i].c_str());
        }
    }
    else
    {
        string aMsg = msg.GetMessage();
        vector<string> lines = splitString(aMsg,"\n");
        for(int i = 0; i < lines.size(); i++)
        {
            mLogMemo->Lines->Add(lines[i].c_str());
        }
    }
    msg.IsProcessed(true);
    return true;
}

bool TMemoSocketServer::SetupIniParameters()
{
    Log(lInfo)<<"Setting up ini parameters in TMemoSocketServer";
    IPCServer::setupProperties();
    return true;
}

bool TMemoSocketServer::ReadIniParameters()
{
//    if(mIniFile)
//    {
//        mIniFile->load();
//        Log(lInfo)<<"Reading ini parameters in TMemoSocketServer";
//    }
//
//    mParas.read();
    return true;
}

