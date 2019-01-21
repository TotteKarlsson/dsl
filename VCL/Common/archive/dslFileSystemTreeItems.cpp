#pragma hdrstop
#include "dslFileSystemTreeItems.h"
#include "dslStringUtils.h"
#pragma package(smart_init)

using namespace dsl;

dslFolderItem::dslFolderItem(const string& label, const string& fullPath, const bool& isRoot)
:
dslFileSystemItem(label, fullPath, isRoot)
{
    mIconIndex = 10;
    mIconSelectedIndex = 10;
}

dslFileSystemItem::dslFileSystemItem(const string& label, const string& fullPath, const bool& isRoot)
:
dslTreeItemBase(label, isRoot),
mInFolder(fullPath){}

string dslFileSystemItem::GetFullPath()
{
    // don't do..     return mIsRoot ? mInFolder : joinPath(mInFolder, mLabel); //bugg!!!!!
    if(mIsRoot)
    {
         mInFolder;
    }
    else
    {
        return joinPath(mInFolder, mLabel);
    }
    return string("");
}

bool dslFileSystemItem::IsFileItem()
{
    return dynamic_cast<dslFileItem*>(this) ? true :false;
}

bool dslFileSystemItem::IsFolderItem()
{
    return dynamic_cast<dslFolderItem*>(this) ? true :false;
}
string                dslFileSystemItem::GetPathTo() {return mInFolder;}
dslFileSystemItem::~dslFileSystemItem(){}
dslFolderItem::~dslFolderItem(){}

dslFileItem::dslFileItem(const string& label, const string& fullPath)
:
dslFileSystemItem(label, fullPath)
{
    mIconIndex = 9;
    mIconSelectedIndex = 9;
}

dslFileItem::~dslFileItem(){}
