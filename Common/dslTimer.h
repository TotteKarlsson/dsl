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
typedef boost::function<void(void)> 	EventFunction;

class DSL_COMMON Timer : public Thread
{

    public:
                                        Timer(const Timespan& interval = Timespan(1000*Timespan::MILLISECONDS), EventFunction ef = 0, const string& lbl = gNoneString);
                                        ~Timer();
        bool                            setInterval(int interval);
        void                            finishEarly();
        Timespan                        getInterval() const;
        Timespan                        getElapsedTime() const;
        Timespan                        getElapsedTimeSinceLastFire() const;
        void                            worker();
        string                          getLabel();
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
        bool                            mFinishEarly;   //Will tell the timer to fire and finish
};

}
#endif
