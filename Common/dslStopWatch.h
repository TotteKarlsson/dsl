#ifndef dslStopWatchH
#define dslStopWatchH
#include "Poco/Timestamp.h"
#include "Poco/Timespan.h"
#include "dslObject.h"
//---------------------------------------------------------------------------

namespace dsl
{

using Poco::Timestamp;
using Poco::Timespan;


class DSL_COMMON StopWatch : public DSLObject
{
    public:
                                        StopWatch();
                                        ~StopWatch();
        bool                            isRunning();
        Timespan                        getElapsedTime();
        bool                            start();
        bool                            reStart();
        bool                            stop();
        void                            reset();

    private:
        Timestamp                       mStart;         //When stop watch was started
        Timestamp                       mEnd;          //When stop watch was stopped
        bool                            mIsRunning;
};

}

#endif
