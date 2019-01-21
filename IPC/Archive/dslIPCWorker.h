#ifndef dslIPCWorkerH
#define dslIPCWorkerH
#include <string>
#include "dslIPCServer.h"
#include "dslSocketWorker.h"
//#include "dslLogger.h"

namespace dsl
{

using std::string;
SocketWorker* DSL_IPC createIPCWorker(int port_number, int socket_handle, void* server = nullptr);
SocketWorker* DSL_IPC createIPCBroadcaster(int port_number, int socket_handle, void* server = nullptr);

class DSL_IPC mtkIPCWorker : public SocketWorker
{
    public:
                        mtkIPCWorker(int port_number, int socket_handle, IPCServer* server = nullptr);
                        ~mtkIPCWorker();
        void            Worker();
        void            run();
    
	private:
        IPCServer*  	mTheServer;
};

}
#endif
