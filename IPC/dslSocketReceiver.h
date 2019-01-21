#ifndef SocketReceiverH
#define SocketReceiverH
#include <string>
#include "dslSocket.h"
#include "dslMessageContainer.h"

namespace dsl
{

using std::string;
class DSL_IPC SocketReceiver : public Thread
{
    public:
                                SocketReceiver(Socket& s, MessageContainer& msgs);
                                ~SocketReceiver();
        void                    run();
        virtual void            worker();


    protected:
    	Socket&					mSocket;
        MessageContainer& 		mMessages;
};

}
#endif

