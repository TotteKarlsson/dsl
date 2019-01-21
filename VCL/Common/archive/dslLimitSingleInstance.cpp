
#pragma hdrstop
#include "dslLimitSingleInstance.h"
#include "dslConstants.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

dslLimitSingleInstance::dslLimitSingleInstance(TCHAR *strMutexName)
{
    //Make sure that you use a name that is unique for this application otherwise
    //two apps may think they are the same if they are using same name for
    //3rd parm to CreateMutex
    mMutex = CreateMutex(nullptr, FALSE, strMutexName); //do early
    mLastError = GetLastError(); //save for use later...
}

dslLimitSingleInstance::~dslLimitSingleInstance()
{
    if (mMutex)  //Do not forget to close handles.
    {
       CloseHandle(mMutex); //Do as late as possible.
       mMutex = nullptr;     //Good habit to be in.
    }
}

bool dslLimitSingleInstance::IsAnotherInstanceRunning()
{
    return (ERROR_ALREADY_EXISTS == mLastError);
}
