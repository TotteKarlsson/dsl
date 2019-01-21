#pragma hdrstop
#include "dslReadDirectoryChangesWorker.h"
#include "dslDirectoryNotifier.h"
#include "dslWin32Utils.h"
//---------------------------------------------------------------------------
typedef std::pair<DWORD, string> DirectoryChangeNotification;
using namespace dsl;

ReadDirectoryChangesWorker::ReadDirectoryChangesWorker(ReadDirectoryChangesHost* pServer, const string& folder, bool checkSubFolders, DWORD flags, DWORD bufferSize)
:
mHost(pServer),
mFilterFlags(flags),
mIncludeChildren(checkSubFolders),
mDirectoryName(folder),
mDirectoryHandle(NULL)
{
	::ZeroMemory(&mOverlapped, sizeof(OVERLAPPED));

	// The hEvent member is not used when there is a completion
	// function, so it's ok to use it to point to the object.
	mOverlapped.hEvent = this;
	mBuffer.resize(bufferSize);
	mBackupBuffer.resize(bufferSize);
}

ReadDirectoryChangesWorker::~ReadDirectoryChangesWorker()
{
	// RequestTermination() must have been called successfully.
	_ASSERTE(mDirectoryHandle == NULL);
}

void ReadDirectoryChangesWorker::copyBufferToBackupBuffer(DWORD count)
{
    // We could just swap back and forth between the two
    // buffers, but this code is easier to understand and debug.
    memcpy(&mBackupBuffer[0], &mBuffer[0], count);
}

void ReadDirectoryChangesWorker::requestTermination()
{
    ::CancelIo(mDirectoryHandle);
    ::CloseHandle(mDirectoryHandle);
    mDirectoryHandle = NULL;
}

bool ReadDirectoryChangesWorker::getDirectoryHandle()
{
	// Allow this routine to be called redundantly.
	if (mDirectoryHandle)
    {
		return true;
    }

	mDirectoryHandle = ::CreateFileA(
		mDirectoryName.c_str(),									// pointer to the file name
		FILE_LIST_DIRECTORY,                					// access (read/write) mode
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		NULL,                               					// security descriptor
		OPEN_EXISTING,                      					// how to create
		FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED,
		NULL);                              					// file with attributes to copy

	return (mDirectoryHandle == INVALID_HANDLE_VALUE) ? false : true;
}

void ReadDirectoryChangesWorker::beginRead()
{
	DWORD dwBytes = 0;

	// This call needs to be reissued after every APC.
	bool success = ::ReadDirectoryChangesW(
		mDirectoryHandle,						// handle to directory
		&mBuffer[0],                       	    // read results buffer
		mBuffer.size(),                    	    // length of buffer
		mIncludeChildren,                 	    // monitoring option
		mFilterFlags,                    	    // filter conditions
		&dwBytes,                               // bytes returned
		&mOverlapped,                      	    // overlapped buffer
		&notificationCompletion);               // completion routine
}

//static
void CALLBACK ReadDirectoryChangesWorker::notificationCompletion(DWORD errorCode, DWORD nrOfBytesTransfered, LPOVERLAPPED overlapped)
{
	ReadDirectoryChangesWorker* pBlock = (ReadDirectoryChangesWorker*) overlapped->hEvent;

	if (errorCode == ERROR_OPERATION_ABORTED)
	{
		::InterlockedDecrement(&pBlock->mHost->mOutstandingRequests);
		delete pBlock;
		return;
	}

	// Can't use sizeof(FILE_NOTIFY_INFORMATION) because
	// the structure is padded to 16 bytes.
	_ASSERTE(nrOfBytesTransfered >= offsetof(FILE_NOTIFY_INFORMATION, FileName) + sizeof(WCHAR));

	// This might mean overflow? Not sure.
	if(!nrOfBytesTransfered)
    {
		return;
    }

	pBlock->copyBufferToBackupBuffer(nrOfBytesTransfered);

	// Get the new read issued as fast as possible. The documentation
	// says that the original OVERLAPPED structure will not be used
	// again once the completion routine is called.
	pBlock->beginRead();
	pBlock->processNotifications();
}

void ReadDirectoryChangesWorker::processNotifications()
{
	BYTE* pBase = &mBackupBuffer[0];

	for(;;)
	{
		FILE_NOTIFY_INFORMATION& fni = (FILE_NOTIFY_INFORMATION&)*pBase;
        DirectoryChangeNotification notification(fni.Action, ws2s(fni.FileName));
		mHost->mTheNotifier->push(notification);

		if (!fni.NextEntryOffset)
        {
			break;
        }
		pBase += fni.NextEntryOffset;
	}

    if(mHost->mTheNotifier->mNotifierCallback)
    {
		mHost->mTheNotifier->mNotifierCallback((int*) (mHost->mTheNotifier));
    }
}

