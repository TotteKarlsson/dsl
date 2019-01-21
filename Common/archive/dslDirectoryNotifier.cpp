#pragma hdrstop
//#include <windows.h>
//#include <process.h>
//#include "dslDirectoryNotifier.h"
//#include "dslReadDirectoryChangesWorker.h"
////---------------------------------------------------------------------------
//
//// DirectoryNotifier
//DirectoryNotifier::DirectoryNotifier(const string& folder, int nMaxCount)
//	:
//    mNotifications(nMaxCount),
//    mThread(NULL),
//	mThreadId(0),
//    mHost(new ReadDirectoryChangesHost(this)),
//    mNotifierCallback(NULL)
//{
//    addDirectory(folder);
//}
//
//DirectoryNotifier::~DirectoryNotifier()
//{
//	terminate();
//	delete mHost;
//}
//
//void DirectoryNotifier::assignCallback(NotifierCallback cb)
//{
//    mNotifierCallback = cb;
//}
//
//HANDLE DirectoryNotifier::getWaitHandle()
//{
//	return mNotifications.getSemaphore();
//}
//
//unsigned int DirectoryNotifier::getThreadId()
//{
//	return mThreadId;
//}
//
//void DirectoryNotifier::init()
//{
//	// Kick off the worker thread, which will be
//	// managed by ReadDirectoryChangesHost.
//	mThread = (HANDLE)_beginthreadex(NULL,
//		0,
//		ReadDirectoryChangesHost::threadStartProc,
//		mHost,
//		0,
//		&mThreadId
//		);
//}
//
//void DirectoryNotifier::terminate()
//{
//	if (mThread)
//	{
//		::QueueUserAPC(ReadDirectoryChangesHost::terminateProc, mThread, (ULONG_PTR)mHost);
//		::WaitForSingleObjectEx(mThread, 10000, true);
//		::CloseHandle(mThread);
//
//		mThread = NULL;
//		mThreadId = 0;
//	}
//}
//
//void DirectoryNotifier::addDirectory( const string& folder, bool bWatchSubtree, DWORD dwNotifyFilter, DWORD dwBufferSize )
//{
//	if (!mThread)
//    {
//		init();
//    }
//
//	ReadDirectoryChangesWorker* pRequest = new ReadDirectoryChangesWorker(mHost, folder, bWatchSubtree, dwNotifyFilter, dwBufferSize);
//
//	QueueUserAPC(ReadDirectoryChangesHost::addDirectoryProc, mThread, (ULONG_PTR) pRequest);
//}
//
//void DirectoryNotifier::push(const DirectoryChangeNotification& notification)
//{
//	DirectoryChangeNotification obj(notification);
//	mNotifications.push(obj);
//}
//
//bool DirectoryNotifier::pop(DirectoryChangeNotification& notification)
//{
//	return mNotifications.pop(notification) ? true : false;
//}
//
//bool DirectoryNotifier::checkOverflow()
//{
//	bool b = mNotifications.isOverflowed();
//	if(b)
//    {
//		mNotifications.clear();
//    }
//	return b;
//}
//
//string actionToStr(DWORD action)
//{
//	switch (action)
//	{
//        case FILE_ACTION_ADDED:		            return "Added";
//        case FILE_ACTION_REMOVED:	            return "Deleted";
//        case FILE_ACTION_MODIFIED:	            return "Modified";
//        case FILE_ACTION_RENAMED_OLD_NAME:		return "Renamed From";
//        case FILE_ACTION_RENAMED_NEW_NAME:		return "Renamed To";
//        default:      							return "BAD DATA";
//	}
//}
