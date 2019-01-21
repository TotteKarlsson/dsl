#ifndef SocketWorkerH
#define SocketWorkerH
#include <string>
#include "dslThread.h"
#include "dslSocket.h"
//----------------------------------------------------------------

namespace dsl
{


class DSL_IPC SocketWorker : public Thread, public Socket
{
    public:
                                    SocketWorker(int portNr = -1, int socket_handle = -1);
        int                         GetPortNumber();
        virtual            	        ~SocketWorker();
        virtual string              GetInfo();
        void                        IgnoreIncomingMessages(bool doIt);
        void                        SetMessageDelimiters(const char& left, const char& right='\n');

    protected:
        int                         mPortNumber;
        bool                        mIgnoreIncomingMessages;
        char                        mLeftMessageDelimiter;
        char                        mRightMessageDelimiter;
};

}
#endif

