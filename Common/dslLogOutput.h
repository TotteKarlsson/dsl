#ifndef dslLogOutputH
#define dslLogOutputH
#include "dslCommonExporter.h"
#include "dslLoggerUtils.h"
#include "dslLogLevel.h"
#include "dslLogging.h"
#include <stdio.h>
#include <sstream>
#include <string>
//---------------------------------------------------------------------------

namespace dsl
{

using std::string;
using std::ostringstream;

class DSL_COMMON LogOutput
{
    public:
                                LogOutput();
        static bool             mShowLogTime;
        static bool             mShowLogPrefix;
        static bool             mShowLogLevel;
        static bool             mUseLogTabs;
        static bool             mLogToConsole;
        static bool             mDoLogging;

        static void             output(const string& msg, const LogLevel& lvl);
        static void             stopLogging();
        static void             startLogging();
		
    protected:
};

}
#endif
