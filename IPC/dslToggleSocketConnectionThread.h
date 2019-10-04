#ifndef dslToggleSocketConnectionThreadH
#define dslToggleSocketConnectionThreadH
#include "dslIPCExporter.h"
#include "dslThread.h"

namespace dsl
{
class SocketClient;

class DSL_IPC ToggleSocketConnectionThread : public Thread
{
	public:
		                                    ToggleSocketConnectionThread(SocketClient* aSocketClient);
		                                    ~ToggleSocketConnectionThread(){}
		bool                                isTogglingConnection(){return mIsWorking;}
		void                                setSocket(SocketClient* aSocket){mClient = aSocket;}
		void                                worker();
		void                                run();

	protected:
		SocketClient*                       mClient;
};

}
#endif
