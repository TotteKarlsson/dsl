#ifndef dslTimerH
#define dslTimerH
#include "dslThread.h"
#include "Poco/Timestamp.h"
#include "Poco/Timespan.h"
#include <boost/function.hpp>
//---------------------------------------------------------------------------

namespace dsl
{

using Poco::Timestamp;
using Poco::Timespan;

//The timer class is desgined to fire off a function,
//assigned to function pointers, ever x seconds.
class DSL_COMMON Timer : public Thread
{
	typedef boost::function<void()> 	EventFunction;
    public:
                                        Timer(const Timespan& interval = Timespan(1000*Timespan::MILLISECONDS), EventFunction ef = nullptr, const string& lbl = gNoneString);
                                        ~Timer();
        bool                            setInterval(int interval);
        Timespan                        getInterval();
        Timespan                        getElapsedTime();
        Timespan                        getElapsedTimeSinceLastFire();
        void                            worker();
        string                          getLabel();
        bool                            assignTimerFunction(EventFunction ef);
        void                            pause();
        void                            resume();
        bool                            start(bool runInThread = true);
        void                            run();
        bool                            isPaused();     //This does not really pause the thread itself.
                                                        //It only prevents the timer function to be executed

		EventFunction					onTimer;

    private:
        Timespan                        mInterval;      //in milliseconds
        Timestamp                       mTheStart;      //When timer was started
        Timestamp                       mTheLastFire;   //When Timer last fired
};

}
#endif
