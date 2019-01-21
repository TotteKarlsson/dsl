#ifndef dslTMemoSocketServerH
#define dslTMemoSocketServerH
//---------------------------------------------------------------------------
#include "dslIPCServer.h"
#include "dslIPCMessage.h"
#include "VCLCommonExporter.h"
#include <vcl.h>
class mtkHardwareAPI;

class PACKAGE TMemoSocketServer : public dsl::IPCServer
{
    public:
                                TMemoSocketServer(dsl::IniFile* iniFile = nullptr, const string& iniSection = "");
                                TMemoSocketServer(const string& iniFName = "TMemoSocketServer.ini", const string& iniSection="TMemoSocketServer");
                                ~TMemoSocketServer();
        bool                    SetupIniParameters();
        bool                    ReadIniParameters();
        bool                    Start(int portNR);

        //Messages
        bool                    processMessage(dsl::IPCMessage& msg);
        void                    SetMemo(TMemo* memo){mLogMemo = memo;}

    private:
        TMemo*                  mLogMemo;
        boost::mutex            mMemoMutex;

};
#endif
