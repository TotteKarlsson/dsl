#ifndef dslFileSystemWatcherH
#define dslFileSystemWatcherH
#include <string>
#include "dslShellItemChangeWatcher.h"
using std::string;

class PACKAGE mtkFileSystemWatcher : public mtkShellItemChangeWatcher
{
    protected:
        string                mRootFolder;

    public:
                            mtkFileSystemWatcher();// : mRootFolder("");
                           ~mtkFileSystemWatcher();
        virtual void        OnChangeNotify(long lEvent, const string& path1, const string& path2);
        bool                StartWatchingFolder(const string& folder, HWND hwnd, UINT uMsg);
        void                StopWatchingFolder();
};

#endif
