//#ifndef dslDirectoryNotifierH
//#define dslDirectoryNotifierH
//#include <string>
//#include <boost/function.hpp>
//#include "dslThreadSafeList.h"
//#include "dslReadDirectoryChangesHost.h"
//#include "dslObject.h"
////---------------------------------------------------------------------------
//using std::string;
//DSL_COMMON string actionToStr(DWORD dwAction);
//
//typedef std::pair<DWORD, string> DirectoryChangeNotification;
//typedef boost::function<void(int*)> NotifierCallback;
//
//class DSL_COMMON DirectoryNotifier : public dsl::DSLObject
//{
//    public:
//                                                            DirectoryNotifier(const string& folder, int nMaxChanges = 1000);
//                                                            ~DirectoryNotifier();
//
//        void                                                init();
//        void                                                terminate();
//
//        void 								                addDirectory(const string& folder, bool bWatchSubtree = false, DWORD dwNotifyFilter = FILE_NOTIFY_CHANGE_LAST_WRITE, DWORD dwBufferSize=16384 );
//        HANDLE 								                getWaitHandle();
//
//        bool                                                pop(DirectoryChangeNotification& notification);
//        void                                                push(const DirectoryChangeNotification& notification);
//
//        													// Check if the queue overflowed. If so, clear it and return true.
//        bool 								                checkOverflow();
//        unsigned int 						                getThreadId();
//		void                        						assignCallback(NotifierCallback cb);
//
//        NotifierCallback                                    mNotifierCallback;
//
//    protected:
//        ReadDirectoryChangesHost*	   						mHost;
//        HANDLE												mThread;
//        unsigned int										mThreadId;
//        ThreadSafeList<DirectoryChangeNotification>			mNotifications;
//};
//
//#endif
