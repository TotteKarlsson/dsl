#ifndef dslLogMessageProcessorH
#define dslLogMessageProcessorH
#include <string>
#include "dslThread.h"
//#include "dslSocketClient.h"
//----------------------------------------------------------------

namespace dsl
{

class SocketClient;
class MessageContainer;
class LogClient;

class MTK_COMMON LogMessageProcessor : public Thread
{
    public:
                                        LogMessageProcessor(SocketClient* theSocket, MessageContainer& mMessageContainer, const string& threadName=gEmptyString);
                                        ~LogMessageProcessor();
        void                            AssignParent(LogClient* parent){mParent = parent;}

                                        // overridden from Thread
        void                            Worker();
        void                            run();
        void                            ShutDown();
        int                             Start();
        bool                            Stop();
        virtual  void                   ProcessMessages();
        void                            SuspendProcessing() {mAllowProcessing = false;}
        void                            ResumeProcessing()  {mAllowProcessing = true;}

	private:
        string                          mServerName;
        bool                            mAllowProcessing;
        MessageContainer&            	mMessageContainer;
        SocketClient*                   mSocketClient;
        LogClient*                      mParent;
};

}
#endif
