
#pragma hdrstop
#include "dslIPCPipeClient.h"
//---------------------------------------------------------------------------



namespace dsl
{
bool dslIPCPipeClient::SendData(const string& theData, size_t nTimeOut)
{
    DWORD cbBytesRead = 0L;
    CHAR chResult[PIPE_BUFSIZE+2];
    ::memset(chResult, 0, PIPE_BUFSIZE+2);
    string test;
    test.assign(mPipeName.begin(), mPipeName.end());
    return CallNamedPipe(
                            test.c_str(),                // pointer to pipe name
                            LPVOID(theData.c_str()),    // pointer to read buffer
                            DWORD(theData.length()),    // size, in bytes, of read buffer
                            LPVOID(chResult),           // pointer to write buffer
                            DWORD(PIPE_BUFSIZE),        // size, in bytes, of write buffer
                            &cbBytesRead,               // pointer to number of bytes written
                            DWORD(nTimeOut)             // time-out time, in milliseconds
                            );
}

}
