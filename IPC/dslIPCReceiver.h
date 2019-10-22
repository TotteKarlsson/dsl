#ifndef dslIPCReceiverH
#define dslIPCReceiverH
#include <string>
#include "dslSocketWorker.h"

namespace dsl
{

using std::string;
class IPCServer;

//Function to used to create a worker
DSL_IPC SocketWorker* createIPCReceiver(int portNr, int socketHandle, void* parent);

class DSL_IPC IPCReceiver : public SocketWorker
{
	public:
		                                IPCReceiver(int portNr, int socketHandle, IPCServer* server);
		                                ~IPCReceiver();
		virtual void                    Worker();
		void                            run();

	protected:
		IPCServer*                      mServer;
};

}
#endif
