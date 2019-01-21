#ifndef dslLoggingH
#define dslLoggingH
#include "dslCommonExporter.h"
#include "dslLogLevel.h"
#include "dslObject.h"
#include "dslLogFile.h"
//#include <memory>
//---------------------------------------------------------------------------

namespace dsl
{

//using std::unique_ptr;

//Global class holding logfile and other settings.
//Persist trougout the life of the application that is using it. Based on RAII

class DSL_COMMON Logging : public DSLObject
{
    public:
                                        Logging();
                                       ~Logging();
        string                          mLastLogMessage;

        string                          getLogPrefix();
        string                          getLogFileName();
        void                            showLogPrefix(bool doIt = true);
        void                            showLogTime(bool doIt = true);
        void                            showLogLevel(bool doIt = true);
        void                            setLogPrefix(const string& prefix);
        LogLevel                        getLogLevel();
        void                            setLogLevel(const LogLevel& lvl);
        void                            logToConsole(bool doIt = true);
        void                            logToFile(const string& file);
        void                            closeLogFile();
        bool                            init(const string& logPrefix = gEmptyString, const LogLevel& level = lDebug5);//, LogFile logFile = LogFile(""));
        void                            write(const char* str);
        bool                            mLogToServer;

    private:
        //unique_ptr<LogFile>             mLogFile;
        LogFile*                        mLogFile;
        string                          mLogPrefix;
        LogLevel                        mLogLevel;
        static int                      mNrOfInstances;


                                        // prevent copying and assignment
                                        Logging(const Logging& logFile);
                                        Logging& operator=(const Logging &);
};

extern DSL_COMMON Logging  gLogger;

}
#define Log(level) \
    if (level > getHighestLogLevel()) ;\
    else if (level > dsl::gLogger.getLogLevel()) ; \
    else Logger().get(level)
#endif
