#ifndef SocketReceiverH
#define SocketReceiverH
#include "dslSocket.h"
#include "dslMessageContainer.h"
#include "dslThread.h"

namespace dsl
{

using std::string;
class DSL_IPC SocketReceiver : public Thread
{
    public:
                                SocketReceiver(Socket& s, MessageContainer& msgs);
                                ~SocketReceiver();
		bool 					start(bool inThread = true);
        void                    run();
        virtual void            worker();

    protected:
    	Socket&					mSocket;
        MessageContainer& 		mMessages;
};

}
#endif

