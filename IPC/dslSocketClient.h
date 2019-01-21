#ifndef SocketClientH
#define SocketClientH
#include "dslSocket.h"
#include "dslIPCMessageEnums.h"
#include "dslToggleSocketConnectionThread.h"
#include "dslSocketReceiver.h"
//---------------------------------------------------------------------------

namespace dsl
{

class DSL_IPC SocketClient : public Socket
{
    public:
                                            SocketClient(int portNr = -1, const string& hostname = gEmptyString);
        virtual                             ~SocketClient(){}
        virtual bool                        connect(int portNr, const string& host = gEmptyString);

						                     //!Returns the portNr
        int                                 getPortNumber(){return mPortNumber;}

        bool                                disConnect();
        bool                                reConnect();
        bool	                            request(const string& request);
        bool                                requestByID(IPC_ID request);

        void                                assignParent(void* _parent){mParent = _parent;}

    protected:
        void*                               mParent;
        int                                 mPortNumber;
        string                              mHostName;
        SocketReceiver						mReceiver;
        MessageContainer                 	mIncomingMessages;
        ToggleSocketConnectionThread        mToggleConnection;
};

}
#endif
