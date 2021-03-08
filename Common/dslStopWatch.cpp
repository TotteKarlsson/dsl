#pragma hdrstop
#include "dslStopWatch.h"
//---------------------------------------------------------------------------
namespace dsl
{

StopWatch::StopWatch()
:
mIsRunning(false)
{
    mStart = mEnd = 0;
}

StopWatch::~StopWatch()
{}

bool StopWatch::isRunning()
{
    return mIsRunning;
}

bool StopWatch::start()
{
    if(mIsRunning )
    {
        return false;
    }

    mStart.update();
    mIsRunning = true;
    return true;
}

bool StopWatch::stop()
{
    if(!mIsRunning)
    {
        return false;
    }

    mEnd.update();
    mIsRunning = false;
    return true;
}

void StopWatch::reset()
{
    mStart = mEnd = 0;
    mIsRunning = false;
}

bool StopWatch::reStart()
{
	reset();
    return start();
}

Timespan StopWatch::getElapsedTime()
{
     return mIsRunning ? Timestamp() - mStart : mEnd - mStart;
}

}
