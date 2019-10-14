#ifndef dslLoggerH
#define dslLoggerH
#include "dslLogLevel.h"
#include "dslLogOutput.h"
#include <sstream>
//---------------------------------------------------------------------------

namespace dsl
{

template <class T>
class Logit : public DSLObject
{
    public:
                                    Logit();
        virtual                    ~Logit();
        std::ostringstream&     	get(const LogLevel& level);

	protected:
        ostringstream          		mOutputStream;

	private:
        LogLevel                    mCurrentLogLevel;
                                    Logit(const Logit&);
};

template <> inline
Logit<LogOutput>::Logit()
{}

template <> inline
Logit<dsl::LogOutput>::~Logit()
{
    mOutputStream << std::endl;
    LogOutput::output(mOutputStream.str(), mCurrentLogLevel);
}

template <> inline
std::ostringstream& Logit<LogOutput>::get(const LogLevel& level)
{
    mCurrentLogLevel = level;

    if(LogOutput::mShowLogPrefix)
    {
        mOutputStream << gLogger.getLogPrefix() <<" ";
    }

    if(LogOutput::mShowLogTime)
    {
        mOutputStream << getLogTime(true)<<" ";
    }

    if(LogOutput::mUseLogTabs)
    {
        //Output tabs
        if(level > lInfo)
        {
        	int lvl = level - lInfo;
			mOutputStream << string(4 * lvl, ' ');

        }
//        mOutputStream << string(level > lInfo ? level - lInfo : 0, ' ');
        mOutputStream << "    ";
    }

    if(LogOutput::mShowLogLevel)
    {
         mOutputStream << dsl::toString(level) << ": "; //Next comes the log message
    }
    return mOutputStream;
}

class DSL_COMMON Logger : public Logit<dsl::LogOutput>
{};

#define Log(level) \
    if (level > dsl::getHighestLogLevel()) ;\
                else if (level > dsl::gLogger.getLogLevel()) ; \
                else dsl::Logger().get(level)

}
#endif
