#ifndef dslIPCMessageProcessorH
#define dslIPCMessageProcessorH
#include <string>
#include "dslThread.h"
#include "dslIPCExporter.h"
//----------------------------------------------------------------

namespace dsl
{

class IPCServer;

class DSL_IPC IPCMessageProcessor : public Thread
{
    public:
                                            IPCMessageProcessor(IPCServer* parent);
                                            ~IPCMessageProcessor();

                                            // overridden from Thread
        bool                                start(bool inThread = true);
        void                                worker();
        void                                shutDown();
        void                                run();

    private:
        string                              mServerName;
        IPCServer                           *mParent;
};

}
#endif 

