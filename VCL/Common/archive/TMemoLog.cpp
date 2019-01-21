#pragma hdrstop
#include <string>
#include "TMemoLog.h"
#pragma package(smart_init)

namespace dsl
{

Stdctrls::TMemo*    TMemoLogOutput::mLogMemo         = nullptr;
bool                  TMemoLogOutput::mLogToMemo         = false;
bool                  TMemoLogOutput::mShowLogLevel    = true;
bool                  TMemoLogOutput::mShowLogPrefix    = true;
bool                  TMemoLogOutput::mUseLogTabs        = true;
bool                  TMemoLogOutput::mShowLogTime     = true;


template <class TMemoLogOutput>
TMemoLog<TMemoLogOutput>::TMemoLog()
{}

template <class TMemoLogOutput>
TMemoLog<TMemoLogOutput>::~TMemoLog()
{
    os << std::endl;
    TMemoLogOutput::Output(os.str(), mCurrentLogLevel);
}

template <class TMemoLogOutput>
std::ostringstream& TMemoLog<TMemoLogOutput>::Get(const LogLevel& level)
{
    mCurrentLogLevel = level;

    if(TMemoLogOutput::mShowLogPrefix)
    {
        os << gLogger.getLogPrefix() <<" ";
    }

    if(TMemoLogOutput::mShowLogTime)
    {
        os << getLogTime(true);
    }

    if(TMemoLogOutput::mUseLogTabs)
    {
        //Output tabs
        os << string(level > lInfo ? level - lInfo : 0, '\t');
        os << "\t";
    }

    if(TMemoLogOutput::mShowLogLevel)
    {
         os << dsl::toString(level) << ": "; //Next comes the log message
    }
    return os;
}

/////////////////////////////////////////////////////////////////////////

TMemoLogOutput::TMemoLogOutput(){}


void TMemoLogOutput::Output(const string& msg, const LogLevel& lvl)
{

    //Log to file, always..
    gLogger.write(msg.c_str());

    String aMsg = msg.c_str();

    if(aMsg.Length() && aMsg[aMsg.Length()] == '\n')
    {
        aMsg[aMsg.Length()] = '\0';
    }

    mLogMemo->Lines->Append(aMsg);
}


void TMemoLogOutput::SetLogMemo(Stdctrls::TMemo* aMemo)
{
    mLogMemo = aMemo;
}

}
