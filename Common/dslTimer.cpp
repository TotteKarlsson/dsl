#pragma hdrstop
#include "dslTimer.h"
#include "dslStringUtils.h"
#include "dslLogger.h"
#include "dslUtils.h"
//---------------------------------------------------------------------------

namespace dsl
{

Timer::Timer(const Timespan& interval, EventFunction f, const string& label)
:
mInterval(interval),
Thread(label),
mFinishEarly(false),
onTimer(f)
{}

Timer::~Timer()
{}

void Timer::finishEarly()
{
	mFinishEarly = true;
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
    mFinishEarly = false;
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
            if(onTimer != NULL && mIsPaused == false && !mIsTimeToDie)
            {
                onTimer();
            }

            mTheLastFire.update();
        }

        if(mFinishEarly)
        {
            if(onTimer != NULL)
            {
                onTimer();
                mIsTimeToDie = true;
            }
            Log(lDebug) << "The timer (" << mLabel <<") finished early";
        }
    }

    Log(lDebug5) <<"Timer Worker Finished";
    mIsWorking  = false;
    mIsFinished = true;
}

bool Timer::setInterval(int interval)
{
    mInterval = Timespan(interval*Timespan::MILLISECONDS);
    return true;
}

Timespan Timer::getInterval() const
{
    return mInterval;
}

Timespan Timer::getElapsedTime() const
{
    Timestamp now;
    return  now - mTheStart;
}

Timespan Timer::getElapsedTimeSinceLastFire() const
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
