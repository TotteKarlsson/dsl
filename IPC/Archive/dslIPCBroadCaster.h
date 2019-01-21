#ifndef dslIPCBroadCasterH
#define dslIPCBroadCasterH
#include "dslObject.h"
#include "dslTimer.h"
#include "dslSocketServer.h"
#include "dslIPCWorker.h"
#include "dslIPCExporter.h"
//---------------------------------------------------------------------------

namespace dsl
{

class DSL_IPC mtkIPCBroadcaster : DSLObject
{
    public:
                            mtkIPCBroadcaster(int broadcastInterval = 100, int serverPort = 50003);
                            ~mtkIPCBroadcaster();
        bool                SetBroadcastInterval(int _ms){return mTimer.setInterval(_ms);}
        bool                SetBroadcastPort(int port_nr){mServer.SetPortNumber(port_nr); return true;}
        bool                AssignBroadCastFunction(OnTimerCFPtr func_ptr);
        bool                Stop();
        bool                Start();
        bool                Broadcast(const string& msg);
        bool                isRunning(){return mTimer.isRunning();}
        void                Pause(){mTimer.pause();}
        void                Resume(){mTimer.resume();}
        int                 GetNumberOfClients(){return mServer.GetNumberOfClients();}


    protected:
        Timer               mTimer;
        SocketServer     	mServer;
};

}
#endif
