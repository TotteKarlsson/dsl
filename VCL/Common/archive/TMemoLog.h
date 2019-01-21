#ifndef TMemoLogH
#define TMemoLogH
#include <sstream>
#include <string>
#include <StdCtrls.hpp>

#include "dslLoggerUtils.h"
#include "dslLogLevel.h"
#include "dslLogging.h"

using std::string;
using std::ostringstream;

namespace dsl
{

template <class T>
class PACKAGE TMemoLog
{
    private:
        LogLevel                mCurrentLogLevel;
                                TMemoLog(const TMemoLog&);    //Can't copy a TMemoLog object..

    protected:
        ostringstream             os;

    public:
                                   TMemoLog();
        virtual                      ~TMemoLog();
        std::ostringstream&        Get(const LogLevel& level = lAny);
};

class PACKAGE TMemoLogOutput
{
    protected:
        static Stdctrls::TMemo* mLogMemo;

    public:
        static bool             mShowLogTime;
        static bool             mShowLogPrefix;
        static bool             mShowLogLevel;
        static bool             mUseLogTabs;
        static bool             mLogToMemo;

                                TMemoLogOutput();

        static void             SetLogMemo(Stdctrls::TMemo* aMemo);
        static bool             LogToMemo();
        static void             LogToMemo(bool doIt);
        static void             Output(const string& msg, const LogLevel& lvl);
        static bool             UseLogTabs();
        static void             StopLogging();
        static void             StartLogging();
};

extern template class TMemoLog<TMemoLogOutput>;

class PACKAGE MemoLogger : public TMemoLog<TMemoLogOutput>
{
};

}

#define LogToMemo() MemoLogger().Get()


#endif
