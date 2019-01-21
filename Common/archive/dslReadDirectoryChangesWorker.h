#ifndef dslReadDirectoryChangesWorkerH
#define dslReadDirectoryChangesWorkerH
#include <windows.h>
#include <vector>
#include <string>
#include "dslObject.h"
//---------------------------------------------------------------------------
using std::vector;
using std::string;

class ReadDirectoryChangesHost;

// All functions in ReadDirectoryChangesWorker run in the context of the worker thread.
// One instance of this object is created for each call to AddDirectory().
class DSL_COMMON ReadDirectoryChangesWorker : public dsl::DSLObject
{
    public:
                                                ReadDirectoryChangesWorker(ReadDirectoryChangesHost* pServer, const string& folder, bool checkSubFolders, DWORD flags, DWORD bufferSize);
                                                ~ReadDirectoryChangesWorker();
        bool 									getDirectoryHandle();
        void 									beginRead();

										        // The dwSize is the actual number of bytes sent to the APC.
        void 									copyBufferToBackupBuffer(DWORD count);

        void 									processNotifications();
        void 									requestTermination();
        ReadDirectoryChangesHost* 	  			mHost;

    protected:

        static void CALLBACK 					notificationCompletion(	DWORD dwErrorCode,				 // completion code
                										                DWORD dwNumberOfBytesTransfered, // number of bytes transferred
                										                LPOVERLAPPED lpOverlapped);		 // I/O information buffer

        										// Parameters for ReadDirectoryChangesW().
        DWORD		                            mFilterFlags;
        bool		                            mIncludeChildren;
        string		                            mDirectoryName;

        										// Result of calling CreateFile().
        HANDLE									mDirectoryHandle;

        										// Required parameter for ReadDirectoryChangesW().
        OVERLAPPED								mOverlapped;

                                                // Data buffer for the request.
                                                // Since the memory is allocated by malloc, it will always
                                                // be aligned as required by ReadDirectoryChangesW().
        vector<BYTE> 							mBuffer;

                                                // Double buffer strategy so that we can issue a new read
                                                // request before we process the current buffer.
        vector<BYTE> 							mBackupBuffer;
};

#endif
