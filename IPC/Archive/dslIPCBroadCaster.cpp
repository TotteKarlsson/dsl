#pragma hdrstop
#include "dslIPCBroadCaster.h"
//---------------------------------------------------------------------------


namespace dsl
{
dslIPCBroadcaster::dslIPCBroadcaster(int broadcastInterval, int serverPort)
:
mTimer(broadcastInterval),
mServer(serverPort)
{
    mServer.AssignParent(this);
//    mServer.AssignCreateWorkerFunctionPtr(createIPCBroadcaster);
}

dslIPCBroadcaster::~dslIPCBroadcaster()
{
    mTimer.OnTimerC = nullptr;
    Stop();
}

bool dslIPCBroadcaster::AssignBroadCastFunction(OnTimerCFPtr func_ptr)
{
    mTimer.OnTimerC = func_ptr;
    return true;
}

bool dslIPCBroadcaster::Stop()
{
    mTimer.stop();
    mServer.ShutDown();
    return true;
}


bool dslIPCBroadcaster::Start()
{
    if(mTimer.OnTimerC == nullptr)
    {
        return false;
    }
    mTimer.start();
    mServer.Start();
    return true;
}

bool dslIPCBroadcaster::Broadcast(const string& msg)
{
    string theMessage;
    if(!msg.size())
        return false;

    //Make sure the message is enclosed in []
    if(msg[0] != '[')
    {
        theMessage = "[" + msg + "]";
        return mServer.Broadcast(theMessage);
    }
    else
    {
        return mServer.Broadcast(msg);
    }
}

}
