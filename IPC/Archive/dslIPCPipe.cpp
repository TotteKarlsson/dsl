
#pragma hdrstop
#include "dslIPCPipe.h"
//---------------------------------------------------------------------------

#include <windows.h>
#include <shellapi.h>
#include <fstream>

namespace dsl
{
dslIPCPipe::dslIPCPipe(const string& _pipeName) : mPipeName(CreatePipeName(_pipeName)), mPipeHandle(0L){}

dslIPCPipe::~dslIPCPipe(void)
{
    if(mPipeHandle)
    {
        DisconnectNamedPipe(mPipeHandle);
           CloseHandle(mPipeHandle);
    }
}

string dslIPCPipe::CreatePipeName(const string& sPipeName)
{
    string fullPipeName = "\\\\.\\pipe\\" + sPipeName;
       return fullPipeName;
}

}


