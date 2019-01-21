#ifndef dslRestartApplicationUtilsH
#define dslRestartApplicationUtilsH
#include <System.hpp>
#include <string>
#include "dslVCLCommonExporter.h"

namespace dsl
{
using std::string;

// Check process command line for restart switch
// Call this function to check that is restarted instance
bool VCLCOMMON checkForCommandLineFlag(const string& flag);

// Wait till previous instance of process finish
bool VCLCOMMON WaitForPreviousProcessToFinish(const string& mutexName, HANDLE applicationRestartMutex);

// Call it when process finish
bool VCLCOMMON RestartProcessFinished(HANDLE applicationRestartMutex);

// Call this function when you need restart application
// After call you must close an active instance of your application
bool VCLCOMMON ActivateRestartProcess(const string& mutexNam, HANDLE applicationRestartMutex, const string& cmdLineParameter = "");

bool VCLCOMMON ActivateApplicationStyleChange(const string& mutexName, const string& newStyleName);

}
#endif
