//---------------------------------------------------------------------------
#ifndef dslFileSystemTreeWatcherH
#define dslFileSystemTreeWatcherH
//---------------------------------------------------------------------------
#include <ComCtrls.hpp>
#include "dslFileSystemWatcher.h"

using std::string;
class mtkFileSystemItem;

class PACKAGE mtkFileSystemTreeWatcher : public mtkFileSystemWatcher
{
    protected:
        TTreeView&            mTree;
        bool                AddFileSystemItem(mtkFileSystemItem* anItem);

    public:
                            mtkFileSystemTreeWatcher(TTreeView& tree);// : mTree(tree) ;
                           ~mtkFileSystemTreeWatcher();
        void                 OnChangeNotify(long lEvent, const string& path1, const string& path2);
        bool                RemoveFileSystemItemInTree(const string& path1);
        bool                AddFileInTree(const string& path1);
        bool                AddFolderInTree(const string& path1);
};


#endif
