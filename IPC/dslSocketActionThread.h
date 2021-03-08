#ifndef dslSocketActionThreadH
#define dslSocketActionThreadH
#include "dslIPCExporter.h"
#include "dslThread.h"
#include "dslStringList.h"
//---------------------------------------------------------------------------

namespace dsl
{

class SocketClient;

enum SocketActionEnum {saConnect, saDisconnect, saReconnect, saUndefined};


class SocketAction
{
	public:

	    				            SocketAction(SocketActionEnum action = saUndefined, const StringList& args = StringList())
                                    :
                                    mActionEnum(action),
                                    mArguments(args)
                                    {}

        virtual 		            ~SocketAction(){}
    	StringList		            mArguments;
		SocketActionEnum			mActionEnum;
};

class DSL_IPC SocketActionThread : public Thread
{

	public:
		                            SocketActionThread(SocketClient& client);
		                            ~SocketActionThread();
		SocketAction                mAction;
		bool 						start(bool inThread = true);
	protected:
		SocketClient&               mSocket;
		void                        run();
};

}
#endif
