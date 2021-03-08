#ifndef SocketClientH
#define SocketClientH
#include "dslSocket.h"
#include "dslIPCMessageEnums.h"
#include "dslSocketActionThread.h"
#include "dslSocketReceiver.h"
//---------------------------------------------------------------------------

namespace dsl
{

//---------------------------------------------------------------------------
class DSL_IPC SocketClient : public Socket
{
    friend SocketActionThread;
    public:
                                                    SocketClient(int portNr = -1, const string& hostname = gEmptyString);
        virtual                                     ~SocketClient();

        virtual string                              getRemoteHostName();

						                             //!Returns the portNr
        int                                         getPortNumber();
        bool                                        disConnect();

        											//!These are executed in threads
        void                                        connect(int portNr = 0, const string& hostName = "");
        void                                        reConnect();
        virtual bool	                            request(const string& request);
        virtual bool                                requestByID(IPC_ID request);
        void                                        assignParent(void* _parent);

    protected:
        void*                                       mParent;
        int                                         mPortNumber;

                                                    //!Hostname, will become localhost, if nothing is given
        string                                      mHostName;
        SocketReceiver						        mReceiver;

        MessageContainer                 	        mIncomingMessages;
        SocketActionThread       			        mSocketActionThread;
        bool                                        sendRequest(const string& msg);

        											//!Blocking, so execute a try to connect in a thread
        virtual bool                                connectByHostName(int portNr, const string& host = gEmptyString);
        virtual bool                                connectByIP(int portNr, const string& hostIP = gEmptyString);
};

}
#endif
