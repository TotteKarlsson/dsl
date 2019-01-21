#pragma hdrstop
#include <System.Classes.hpp>
#include "dslLogFileReader.h"
#include "dslLogger.h"
#include "dslFileUtils.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace dsl;

LogFileReader::LogFileReader(const string& file, Callback AMethod, bool atEnd)
:
mStartAtFileEnd(atEnd),
mFileName(file),
mCallBackFnc(AMethod)
{
	if(file.size())
	{
		init();
	}
}

void LogFileReader::assignOnMessageCallBack(Callback AMethod)
{
	mCallBackFnc = AMethod;
}

void LogFileReader::setFileName(const string& fName)
{
    mFileName = fName;
}

string LogFileReader::getLogFileName()
{
    return mFileName;
}

void LogFileReader::run()
{
    worker();
}

bool LogFileReader::init()
{
    if(fileExists(mFileName.c_str()))
    {
        mFS.open(mFileName.c_str());
        return true;
    }
    else
    {
		if(createFile(mFileName))
        {
        	mFS.open(mFileName.c_str());
	        return true;
    	}
        return false;
    }
}

bool LogFileReader::reStart()
{
    bool val = init();
    start();
    return val;
}

bool LogFileReader::hasData()
{
    return mTheData.size() ? true : false;
}

string& LogFileReader::getData()
{
	return mTheData;
}

void LogFileReader::purge()
{
    mTheData.clear();
}

void LogFileReader::worker()
{
    Log(lInfo)<<"Entering logFile Reader thread function";
    mIsRunning = true;
    mIsFinished = false;

    if(!mFS.is_open())
    {
        mFS.open(mFileName.c_str());
        if(!mFS)
        {
            mIsTimeToDie = true;
        }

    }
	if(!mCallBackFnc)
	{
		mIsTimeToDie = true;
		Log(lError)<<"No call back function in LogFileReader.. Exiting.";
	}

	if(mStartAtFileEnd)
	{
		mFS.seekg (0, ios::end);
	}
	else
	{
		mFS.seekg (0, ios::beg);
	}

	streampos pos = mFS.tellg();
	streampos lastPosition = pos;

	//This should be rewritten and we should wait for a file system change
	while(mIsTimeToDie == false)
	{
		//Read until end of file
		while(!mFS.eof() && mIsTimeToDie == false )
		{

			getline(mFS, mTheData);

			if(mTheData.size() > 1)
			{
				if(mCallBackFnc)
				{
					TThread::Synchronize(nullptr, mCallBackFnc);
				}
                //Need this in case logs are coming faster than we can write.
                //1 ms is enough for the UI to refresh
				Sleep(5);
				mTheData.clear();
			}
		}

		if(mFS.fail())
		{
			mFS.clear();
		}
		pos = mFS.tellg();
		Sleep(5);
	}

	mIsRunning = false;
	mIsFinished = true;
	Log(lInfo)<<"Exiting logFile Reader thread function";
}

