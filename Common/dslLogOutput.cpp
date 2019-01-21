#pragma hdrstop
#include "dslLogOutput.h"
#include <iostream>
#include <string>
//---------------------------------------------------------------------------
namespace dsl
{
using namespace std;
extern Logging  gLogger;
/////////////////////////////////////////////////////////////////////////
bool LogOutput::mDoLogging         = true;
bool LogOutput::mLogToConsole      = true;
bool LogOutput::mShowLogTime       = true;
bool LogOutput::mShowLogLevel      = true;
bool LogOutput::mShowLogPrefix     = false;
bool LogOutput::mUseLogTabs        = false;

LogOutput::LogOutput(){}

void LogOutput::stopLogging()
{
    mDoLogging = false;
}

void LogOutput::startLogging()
{
    mDoLogging = true;
    cout << "Started Logging";
}

void LogOutput::output(const string& msg, const LogLevel& lvl)
{
    if(!mDoLogging)
    {
        return;
    }

    //Log to file, always..
    dsl::gLogger.write(msg.c_str());

    if(mLogToConsole == true)     //Default is standard error
    {
        fprintf(stderr, "%s", msg.c_str());
        fflush(stderr);
    }
}

}
