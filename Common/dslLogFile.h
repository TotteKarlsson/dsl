#ifndef dslLogFileH
#define dslLogFileH
#include "dslObject.h"
#include "dslCommonExporter.h"
#include "dslLogLevel.h"
//#include <memory>
#include <string>
#include <stdio.h>
//---------------------------------------------------------------------------

//Global class holding logfile and other settings. Persist trougout the life of the application that is using it. Based on RAII

namespace dsl
{

//using std::unique_ptr;

class DSL_COMMON LogFile : public DSLObject
{
    public:
                                         LogFile(const string& fName);
                                        ~LogFile();
        FILE*                            mFILEHandle;
        string                           getFileName();

    private:
                                         // prevent copying and assignment
                                         LogFile(const LogFile& logFile);
                                         LogFile& operator=(const LogFile&);
        string                           mFileName;
};

}
#endif
