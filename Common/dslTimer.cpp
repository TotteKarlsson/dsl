#pragma hdrstop
#include "dslTimer.h"
#include "dslStringUtils.h"
#include "dslLogger.h"
#include "dslUtils.h"
//---------------------------------------------------------------------------

namespace dsl
{

Timer::Timer(const Timespan& interval, EventFunction class_func_ptr, const string& label)
:
mInterval(interval),
Thread(label),
OnTimer(0)
{}

Timer::~Timer()
{}

bool Timer::assignTimerFunction(EventFunction ef)
{
    OnTimer = ef;
    return true;
}

void Timer::run()
{
    worker();
}

bool Timer::start(bool runInThread)
{
    if(runInThread && mIsPaused == false)
    {
        if(mThread.isRunning())
        {
            Log(lDebug3)<<"Tried to start a working thread!";
            return false;
        }
        else
        {
            mIsTimeToDie = false;
            mThread.start(*this);
        }
    }

    if(mIsPaused)
    {
        resume();
    }
    return true;
}

void Timer::worker() //The threads worker function
{
    mIsStarted = true;            //Use to indicate if Worker function is entered
    mIsWorking = true;
    mTheStart.update();
    mTheLastFire.update();

    while(mIsTimeToDie == false)
    {
        Timestamp now;
        long intervall = (long) mInterval.totalMilliseconds();

        sleep(10); //Resolution is 10 milliseconds
        Timespan current = now - mTheLastFire;

        if(current  > mInterval)
        {
            if(OnTimer != NULL && mIsPaused == false && !mIsTimeToDie)
            {
                OnTimer();
            }

            mTheLastFire.update();
        }
    }

    mIsWorking  = false;
    mIsFinished = true;
    Log(lDebug) <<"Timer Worker Finished";
}

bool Timer::setInterval(int interval)
{
    mInterval = Timespan(interval*Timespan::MILLISECONDS);
    return true;
}

Timespan Timer::getInterval()
{
    return mInterval;
}

Timespan Timer::getElapsedTime()
{
    Timestamp now;
    return  now - mTheStart;
}

Timespan Timer::getElapsedTimeSinceLastFire()
{
    Timestamp now;
    return  now - mTheLastFire;
}

string Timer::getLabel()
{
    return mLabel;
}

void Timer::pause()
{
    mIsPaused = true;
}

void Timer::resume()
{
    mIsPaused = false;
}

//This does not really pause the thread itself. It only prevents the timer function to be executed
bool Timer::isPaused()
{
    return mIsPaused;
}
}
