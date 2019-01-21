#ifndef dslTimerH
#define dslTimerH
#include "dslThread.h"
#include "Poco/Timestamp.h"
#include "Poco/Timespan.h"
//---------------------------------------------------------------------------

namespace dsl
{

using Poco::Timestamp;
using Poco::Timespan;

typedef void (*OnTimerFPtr)(void);

#if defined(__BORLANDC__)
	typedef void (__closure *OnTimerCFPtr)(); //Need to research this and make it portable
#else
	typedef void (*OnTimerCFPtr)();
#endif


//The timer class is desgined to fire off a function,
//assigned to function pointers, ever x seconds.
class DSL_COMMON Timer : public Thread
{
    public:
                                        Timer(const Timespan& interval = Timespan(1000*Timespan::MILLISECONDS), OnTimerCFPtr func_ptr = nullptr, const string& lbl = gNoneString);
                                        ~Timer();
        bool                            setInterval(int interval);
        Timespan                        getInterval();
        Timespan                        getElapsedTime();
        Timespan                        getElapsedTimeSinceLastFire();
        OnTimerCFPtr                    OnTimerC;   //Function pointer to class member function
        OnTimerFPtr                     OnTimerF;   //Function pointer to regular non member function
        void                            worker();
        string                          getLabel();
        bool                            assignTimerFunction(OnTimerCFPtr func_ptr);
        void                            pause();
        void                            resume();
        bool                            start(bool runInThread = true);
        void                            run();
        bool                            isPaused();     //This does not really pause the thread itself.
                                                        //It only prevents the timer function to be executed

    private:
        Timespan                        mInterval;      //in milliseconds
        Timestamp                       mTheStart;      //When timer was started
        Timestamp                       mTheLastFire;   //When Timer last fired
};

}
#endif
