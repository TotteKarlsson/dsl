#pragma hdrstop
#include "dslVCLUtils.h"
#include "dslApplicationInfo.h"
#pragma package(smart_init)

using namespace dsl;

dslApplicationInfo::dslApplicationInfo(TApplication* a)
:
mApplication(a),
mExeName("<not set>"),
mExePath("<not set>"),
mProductName("<not set>"),
mVersion("<not set>"),
mRegistryRoot(""),
mLogFileName("application.log")
{
      if(mApplication)
      {
          Setup();
      }
}

void dslApplicationInfo::Setup()
{
    if(!mApplication)
    {
        return;
    }

    mExeName        = getApplicationNameW();
    mExePath        = getApplicationPath();
    mProductName    = getProductName(mApplication);
    mVersion        = getProductVersion(mApplication).c_str();
    mRegistryRoot   = getProductRegistryRoot(mApplication).c_str();
}


