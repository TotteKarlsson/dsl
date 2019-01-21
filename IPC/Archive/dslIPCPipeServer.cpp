#pragma hdrstop
#include "dslIPCPipeServer.h"
#include <windows.h>
#include <shellapi.h>
#include <fstream>
#include "dslLogger.h"
//---------------------------------------------------------------------------


namespace dsl
{
dslIPCPipeServer::dslIPCPipeServer(const string& _pipeName) : dslIPCPipe(_pipeName) {}

bool dslIPCPipe::DeletePipe()
{
    int     retVal = DeleteFileA(mPipeName.c_str());
    return  retVal == 0 ? false : true;
}

bool dslIPCPipeServer::PeekPipe()
{
    CHAR chRequest[PIPE_BUFSIZE+2];
    ::memset(chRequest, 0, PIPE_BUFSIZE+2);

    DWORD cbBytesRead, cbReplyBytes, cbWritten, cbAvailable, cbUnreadBytes;

    //Check if there is anything to read on the pipe
    int val = PeekNamedPipe (   mPipeHandle,                    // handle to pipe to copy from
                                chRequest,                        // pointer to data buffer no data is to be read though
                                1,                               // size, in bytes, of data buffer
                                &cbBytesRead,                      // pointer to number of bytes read
                                &cbAvailable,                      // pointer to total number of bytes available
                                &cbUnreadBytes                    // pointer to unread bytes in this message
                            );
    long availBytes = (long) &cbAvailable;
    return (availBytes > 0) ? true : false;
}

bool dslIPCPipeServer::ReadClientPipeData(string& _pipeData, size_t timeout)
{
    //The ReadFile function below is blocking
    //Therefore, before calling WaitParam check if there is anything to read on the pipe before
    //calling WaitParam
    if(!mPipeHandle)
    {
        _pipeData = "Error: Pipe not created.";
        return false;
    }

    // Wait for a client to connect;
    if(!ConnectNamedPipe(mPipeHandle, nullptr))
    {
        _pipeData = "Error: No client.";
        CloseHandle(mPipeHandle);
        mPipeHandle = 0L;
        return false;
    }

    CHAR chRequest[PIPE_BUFSIZE+2];
    ::memset(chRequest, 0, PIPE_BUFSIZE + 2);
    DWORD cbBytesRead, cbReplyBytes, cbWritten;

    // Read client requests from the pipe. BLOCKING...
    BOOL fSuccess = ReadFile(   mPipeHandle,    // handle to pipe
                                chRequest,      // buffer to receive data
                                PIPE_BUFSIZE,   // size of buffer
                                &cbBytesRead,   // number of bytes read
                                nullptr            // not overlapped I/O
                            );

    bool returnResult = true;
    if (!fSuccess || cbBytesRead == 0)
    {
        returnResult = false;
        _pipeData = "Error: Pipe read error.";
    }
    else
    {
        _pipeData = chRequest;   //Get the data
        // Write a reply on the pipe.
        fSuccess = WriteFile(   mPipeHandle,        // handle to pipe
                                "Okay!",            // buffer to write from
                                5,                  // number of bytes to write
                                &cbWritten,         // number of bytes written
                                nullptr                // not overlapped I/O
                            );

        if (!fSuccess)
        {
            _pipeData = "Error: Pipe write error.";
            returnResult = false;
        }
    }

    FlushFileBuffers(mPipeHandle);      // Flush the pipe to allow the client to read the pipe's contents before disconnecting.
    DisconnectNamedPipe(mPipeHandle);   // The server process must call DisconnectNamedPipe to disconnect a pipe handle from its
                                        // previous client before the handle can be connected to another client by using
                                        // the ConnectNamedPipe function.
    return returnResult;
}

bool dslIPCPipeServer::CreatePipe()
{
    string fullPipeName = GetPipeName();
    string tempName;
    tempName.assign(fullPipeName.begin(), fullPipeName.end());
    if(!mPipeHandle)
    {
         mPipeHandle = CreateNamedPipe(
         tempName.c_str(),          // pipe name
         PIPE_ACCESS_DUPLEX,       // read/write access
         PIPE_TYPE_MESSAGE |       // message type pipe
         PIPE_READMODE_MESSAGE |   // message-read mode
         PIPE_WAIT,                // blocking mode
         PIPE_UNLIMITED_INSTANCES, // max. instances
         PIPE_BUFSIZE,                  // output buffer size
         PIPE_BUFSIZE,                  // input buffer size
         PIPE_WAIT,                // time-out
         nullptr);                    // no security attribute
    }
    else
    {
        Log(lInfo)<<"Pipe handle is not nullptr";
    }

    if (mPipeHandle == INVALID_HANDLE_VALUE)
    {
        mPipeHandle = 0L;
        return false;
    }

    Log(lInfo)<<"Created a named pipe: "<<fullPipeName;
    return true;
}


}
