#ifndef dslThreadH
#define dslThreadH
#include "Poco/Thread.h"
#include "dslObject.h"
#include "dslConstants.h"
#include <iostream>
#include <string>
//---------------------------------------------------------------------------

namespace dsl
{

class DSL_COMMON Thread : public DSLObject, public Poco::Runnable
{
    public:
                                                    Thread(const string& label = gEmptyString);
        virtual                                     ~Thread();
        string                                      getLabel();
        string                                      getName();
        int                                         getID();
        string                                      getState();
        string                                      getUpTime();

        bool                                        isTimeToDie();
        bool                                        isAlive();
        bool                                        isStarted();
        bool                                        isWorking() const;
        bool                                        isRunning() const;
        virtual bool                                isFinished();
        virtual void                                reset();

                                                    //!How we start poco threads
        virtual bool                                start(bool inThread = true);

                                                    //Run must be overridden!
                                                    //The derived run function is doing the work
                                                    //Poco calls run from the Thread::run function
                                                    //Need to cleanup this logic...
        virtual void               	                run();

        void                                        pause();
        void                                        resume();
        virtual void                                stop();
        bool                                        isPaused();

    protected:
        int                                         mID;
        bool                                        mIsTimeToDie;
        Poco::Thread                                mThread;
        string                                      mLabel;
        static int                                  mThreadCount;
        bool                                        mIsStarted;            //Use to indicate if Worker function is entered
        bool                                        mIsFinished;           //Use to indicate if Worker function is exiting

        bool                                        mIsWorking;             //Set to true in worker. A thread can be running, but not working (while waiting for  a condition
        																	//for example .. perhaps use mIsWaiting..
        bool                                        mIsPaused;              //Use to pause a thread... has to be implemented in derived classes..
        int                                         mExitStatus;            //Read exit status to get some ideas on what happened in the worker



};

}
#endif
