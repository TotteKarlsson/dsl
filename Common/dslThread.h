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

//using namespace boost;
using namespace std;

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
        bool                                        isWorking();
        bool                                        isRunning();
        virtual bool                                isFinished();

        virtual void                                reset();

        virtual bool                                start(bool inThread = true);

        void                                        pause();
        void                                        resume();
        virtual void                                stop();

                                                    //The derived run function is doing the work
        virtual void               	                run();  //Poco calls run..
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
        																	//for example
        bool                                        mIsPaused;              //Use to pause a thread... has to be implemented in derived classes..
        int                                         mExitStatus;            //Read exit status to get some ideas on what happened in the worker
};

}
#endif
