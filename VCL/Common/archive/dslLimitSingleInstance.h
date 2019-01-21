#ifndef dslLimitSingleInstanceH
#define dslLimitSingleInstanceH
//---------------------------------------------------------------------------
#include <vcl.h>
//#include <windows.h>
#include "VCLCommonExporter.h"

//This code is from Q243953 in case you lose the article and wonder
//where this code came from.
class VCL_COMMON mtkLimitSingleInstance
{
    protected:
        DWORD                      mLastError;
          HANDLE                     mMutex;

    public:
                                  mtkLimitSingleInstance(TCHAR *strMutexName);
                                  ~mtkLimitSingleInstance();
          bool                     IsAnotherInstanceRunning();
};

#endif
