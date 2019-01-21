#ifndef dslFileSystemTreeItemsH
#define dslFileSystemTreeItemsH
#include <string>
#include "dslTreeItemBase.h"
using std::string;
class mtkFileItem;
//---------------------------------------------------------------------------
class PACKAGE mtkFileSystemItem : public mtkTreeItemBase
{
    protected:
        mtkTreeItemBase         *mParent;          // pointer to parent
        string                  mInFolder;      //Where is it

    public:
                                mtkFileSystemItem(const string& label, const string& fullPath, const bool& isRoot = false);
        virtual                 ~mtkFileSystemItem();
        string                  GetPathTo() ;
        string                  GetFullPath();
        bool                    IsFileItem();
        bool                    IsFolderItem();
};

class PACKAGE mtkFolderItem : public mtkFileSystemItem
{
    protected:


    public:
                                mtkFolderItem(const string& label, const string& fullPath, const bool& isRoot = false);
                                ~mtkFolderItem();
};

class PACKAGE mtkFileItem : public mtkFileSystemItem
{
    public:
                                mtkFileItem(const string& label, const string& fullPath);
                                ~mtkFileItem();
};

#endif
