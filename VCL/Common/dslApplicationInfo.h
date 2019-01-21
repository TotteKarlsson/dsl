#ifndef dslApplicationInfoH
#define dslApplicationInfoH
#include <StdCtrls.hpp>
#include <string>
#include "dslConstants.h"
#include "dslVCLCommonExporter.h"
using std::string;

//namespace Forms
//{
//	class TApplication;
//}

class VCLCOMMON dslApplicationInfo
{
    public:
                            dslApplicationInfo(TApplication* a  = nullptr);

        TApplication*       mApplication;
        string              mExeName;
        string              mExePath;
        string              mProductName;
        string              mVersion;
        string              mRegistryRoot;
        string              mLogFileName;
        void                Setup();
};

#endif
