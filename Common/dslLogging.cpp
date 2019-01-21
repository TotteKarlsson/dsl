#pragma hdrstop
#include "dslLogging.h"
#include "dslLogOutput.h"
#include "dslException.h"
//---------------------------------------------------------------------------

namespace dsl
{

Logging gLogger;
int Logging::mNrOfInstances = 0;

Logging::Logging()
:
mLogToServer(false),
mLogFile(nullptr),
mLogPrefix("none"),
mLogLevel(lDebug5)
{
    mNrOfInstances++;
}

bool Logging::init(const string& logPrefix, const LogLevel& level)//, unique_ptr<LogFile> logFile)
{
    mLogPrefix = logPrefix;
    mLogLevel = level;
    //mLogFile = move(logFile);
    return true;//mLogFile.get() ? true : false;
}

Logging::~Logging()
{
    mNrOfInstances--;
}

void Logging::logToFile(const string& fName)
{
    if(!mLogFile)
    {
        mLogFile = new LogFile(fName);
    }
}

void Logging::closeLogFile()
{
    delete mLogFile;
    mLogFile = nullptr;
}

void Logging::logToConsole(bool doIt)
{
    LogOutput::mLogToConsole = doIt;
}

void Logging::showLogPrefix(bool doIt)
{
    LogOutput::mShowLogPrefix = doIt;
}

void Logging::showLogLevel(bool doIt)
{
    LogOutput::mShowLogLevel = doIt;
}

void Logging::showLogTime(bool doIt)
{
    LogOutput::mShowLogTime = doIt;
}

LogLevel Logging::getLogLevel()
{
    return mLogLevel;
}

string Logging::getLogFileName()
{
    if(mLogFile)
    {
        return mLogFile->getFileName();
    }
    return string("<none>");
}

void Logging::setLogLevel(const LogLevel& lvl)
{
    mLogLevel = lvl;
}

void Logging::setLogPrefix(const string& prefix)
{
    mLogPrefix = prefix;
}

string Logging::getLogPrefix()
{
    return mLogPrefix;
}

void Logging::write(const char* str)
{
    if(str)
    {
        mLastLogMessage = str;
    }

    if(!mLogFile || !mLogFile->mFILEHandle)
    {
        return;
    }

    fprintf(mLogFile->mFILEHandle, "%s", str);

    if (EOF == fflush(mLogFile->mFILEHandle))
    {
        throw std::runtime_error("file write failure");
    }
}

}
