#ifndef dslGetRemoteTextFileDataThreadH
#define dslGetRemoteTextFileDataThreadH
#include <System.hpp>
#include <string>
#include "dslVCLCommonExporter.h"
#include "dslThread.h"

//---------------------------------------------------------------------------

namespace dsl
{

//Need __fastcall when used by the VCL
typedef void __fastcall (__closure *TGetRemoteTextFileDataThreadCallBack)(const std::string& remoteTextFile);

//This thread can retrieve remote version data, e.g. ChangeLog or version info.
//If website can't be reached, information is kept in the same string (mData)
class VCLCOMMON GetRemoteTextFileDataThread : public dsl::Thread
{
    public:
                                                GetRemoteTextFileDataThread(const string& url = gEmptyString);
        void                                    worker();
        void                                    run();
        void                                    setURL(const string& url);
        void                                    assignCallBack(TGetRemoteTextFileDataThreadCallBack cb);
        string                                  getErrorData();

    private:
        string                                  mURL;
        string                                  mRemoteTextData;
        string                                  mErrorData;
        TGetRemoteTextFileDataThreadCallBack    mCallBackFunction;
};

}

#endif
