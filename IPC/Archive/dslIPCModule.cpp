
#pragma hdrstop
#include <iostream>
#include <iomanip>
#include "dslStringUtils.h"
#include "dslIPCModule.h"
//#include "mvlinsUtil.h"

using namespace std;


namespace dsl
{
dslIPCModule::dslIPCModule()
: mIniFile("module.ini"),
mIniFileName(""),
mIniFileSection(""),
mLogFileName("")
{

}

dslIPCModule::~dslIPCModule()
{
}

bool dslIPCModule::Setup()
{
    return false;
}

bool dslIPCModule::ReadIniFile(const string& fName, const string& sec)
{
//    mIniFileName = fName;
//    if(sec.size())
//        mIniFileSection = sec;
//
//    if(!mIniFile.LInit(fName))
//    {
//        //mverror(string("Could not open ini file: \"") + iniFile.GetFilePath() + string("\""));
//        return false;
//    }
//
//       for(unsigned int i = 0; i < mPropertys.size(); i++)
//    {
//        mPropertys[i]->ReadFromIniFile(iniFile, mIniFileSection);
//        if(!mPropertys[i]->WasRead())
//        {
//            //mverror(string("The Parameter ") + mPropertys[i]->GetLabel() + string(" was not found in the ini file: ") + iniFile.GetFilePath() + " under section " + string(mIniFileSection));
//        }
//    }

    return true;
}

vector<IPCMessage> dslIPCModule::PopMessageBuffer()
{
    vector<IPCMessage> msgBuf(msgOutBuffer);
    msgOutBuffer.clear();
    return msgBuf;
}

void dslIPCModule::HandleIPCMessage(const IPCMessage& msgIn)
{
    //Any output generated in this function is buffered in the msgOutBuffer, emptied by calling WriteIPC
    if(msgIn.hasData())
    {
//        LogMessage(string("A dslIPCModule received message: ") + string(msgIn));
        msgOutBuffer.push_back(msgIn);
    }
}

void dslIPCModule::SetLogFileName(const string& fName)
{
    mLogFileName = fName;
}


}
