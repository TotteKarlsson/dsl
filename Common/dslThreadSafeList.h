#ifndef dslThreadSafeListH
#define dslThreadSafeListH
////#include <windows.h>
//#include <list>
////#include <atl/atlbase.h>
//
//template <class T>
//class ThreadSafeList : protected std::list<T>
//{
//    public:
//        									ThreadSafeList(int nMaxCount);
//									        ~ThreadSafeList();
//        void                                push(T& c);
//        bool                                pop(T& c);
//
//        void                                clear(); // If overflow, use this to clear the queue.
//        bool                                isOverflowed();
//        HANDLE 								getSemaphore();
//
//    protected:
//        HANDLE 								mSemaphore;
//        CComAutoCriticalSection 			mCrit;
//        bool 								mIsOverflowed;
//};
//
//template<class T>
//ThreadSafeList<T>::ThreadSafeList(int nMaxCount)
//{
//    mIsOverflowed = false;
//    mSemaphore = ::CreateSemaphore(
//        NULL,		// no security attributes
//        0,			// initial count
//        nMaxCount,	// max count
//        NULL);		// anonymous
//}
//
//template<class T>
//ThreadSafeList<T>::~ThreadSafeList()
//{
//    ::CloseHandle(mSemaphore);
//    mSemaphore = NULL;
//}
//
//template<class T>
//void ThreadSafeList<T>::push(T& c)
//{
//    mCrit.Lock();
//    push_back( c );
//    mCrit.Unlock();
//
//    if (!::ReleaseSemaphore(mSemaphore, 1, NULL))
//    {
//    	// If the semaphore is full, then take back the entry.
//        mCrit.Lock();
//        pop_back();
//        if (GetLastError() == ERROR_TOO_MANY_POSTS)
//        {
//            mIsOverflowed = true;
//        }
//		mCrit.Unlock();
//    }
//}
//
//template<class T>
//bool ThreadSafeList<T>::pop(T& c)
//{
//	mCrit.Lock();
//
//    // If the user calls pop() more than once after the
//    // semaphore is signaled, then the semaphore count will
//    // get out of sync.  We fix that when the queue empties.
//    if (empty())
//    {
//        while (::WaitForSingleObject(mSemaphore, 0) != WAIT_TIMEOUT)
//        {
//            1;
//        }
//		mCrit.Unlock();
//        return false;
//    }
//
//    c = front();
//    pop_front();
//	mCrit.Unlock();
//    return true;
//}
//
//// If overflow, use this to clear the queue.
//template<class T>
//void ThreadSafeList<T>::clear()
//{
//	mCrit.Lock();
//
//    for (DWORD i = 0; i < size(); i++)
//    {
//        WaitForSingleObject(mSemaphore, 0);
//    }
//
//    std::list<T>::clear();
//    mIsOverflowed = false;
//	mCrit.Unlock();
//}
//
//template<class T>
//bool ThreadSafeList<T>::isOverflowed()
//{
//    return mIsOverflowed;
//}
//
//template<class T>
//HANDLE ThreadSafeList<T>::getSemaphore()
//{
//	return mSemaphore;
//}
//
#endif
