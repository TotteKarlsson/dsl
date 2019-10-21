#pragma hdrstop
#include "dslLogger.h"
#include "dslThread.h"

//---------------------------------------------------------------------------
namespace dsl
{

int Thread::mThreadCount = 0;

Thread::Thread(const std::string& label)
:
mID(-1),
mIsTimeToDie(false),
mLabel(label),
mIsStarted(false),
mIsFinished(false),
mIsWorking(false),
mIsPaused(false),
mExitStatus(0)
{}

Thread::~Thread()
{}

void Thread::reset()
{
    mIsTimeToDie   = false;
    mIsFinished    = false;
    mIsStarted     = false;
    mIsWorking     = false;
    mIsPaused      = false;
    mExitStatus    = 0;
}

void Thread::stop()
{
    if(!mIsStarted)
    {
        mIsFinished = true; //If clients ask if thread is finished..
    }
    mIsTimeToDie = true;
}

void Thread::pause()
{
    mIsPaused = true;
}

void Thread::resume()
{
    mIsPaused = false;
}

bool Thread::start(bool inThread)
{
    if(inThread)
    {
        Thread::run();
    }
    else
    {
    	run();
    }
    return true;
}

//----------------------------------------------------------------
void Thread::run()
{
    //This starts and runs the thread
    if(mIsWorking)
    {
        Log(lDebug3) << "Tried to start a running thread.";
        return;
    }

    Log(lDebug5) << "Entering Thread::Run function";
    mIsTimeToDie = false;

    //Start poco thread
    mThread.start(*this);
}

string Thread::getState()
{
    return "Not known";
}

string Thread::getUpTime()
{
    return "Not known";
}

bool Thread::isAlive()
{
    return !mIsFinished;
}

string Thread::getLabel()
{
    return mLabel;
}

string Thread::getName()
{
    return mLabel;
}

int Thread::getID()
{
    return mID;
}

bool Thread::isTimeToDie()
{
    return mIsTimeToDie;
}

bool Thread::isStarted()
{
    return mIsStarted;
}

bool Thread::isWorking()
{
    return mIsWorking;
}

bool Thread::isRunning()
{
    return mThread.isRunning();

//	if(mThread.isRunning() ||  mIsWorking)
//    {
//    	if(mIsPaused)
//        {
//        	return false;
//        }
//
//        return true;
//    }
//
//    return false;
}

bool Thread::isFinished()
{
    return mIsFinished;
}

bool Thread::isPaused()
{
    return mIsPaused;
}


}
