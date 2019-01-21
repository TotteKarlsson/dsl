#ifndef dslIPCPipeClientH
#define dslIPCPipeClientH
#include "dslIPCPipe.h"

namespace dsl
{


class mtkIPCPipeClient : public mtkIPCPipe
{
    public:
                mtkIPCPipeClient(const string& _pipeName) : mtkIPCPipe(_pipeName){}
        bool    SendData(const string& data, size_t timeOut = 3000L);
};

}
#endif
