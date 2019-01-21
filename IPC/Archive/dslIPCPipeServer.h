#ifndef dslIPCPipeServerH
#define dslIPCPipeServerH
#include "dslIPCPipe.h"
//---------------------------------------------------------------------------

namespace dsl
{

class mtkIPCPipeServer : public mtkIPCPipe
{
    public:
                            mtkIPCPipeServer(const string& _pipeName = "MTK_PIPE");
        bool                CreatePipe();
        bool                ReadClientPipeData(string& data, size_t timeout = 0L);
        bool                PeekPipe();
};

}
#endif
