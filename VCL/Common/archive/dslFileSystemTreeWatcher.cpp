
#pragma hdrstop
#include "dslVCLUtils.h"
#include "dslStringUtils.h"
#include "dslTreeComponentUtils.h"
#include "dslShellHelpers.h"
#include "dslFileSystemTreeWatcher.h"
#include "dslFileSystemTreeItems.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace dsl;

void dslFileSystemTreeWatcher::OnChangeNotify(long lEvent, const string& path1, const string& path2)
{
    Log(lDebug3)<< "Event "<< stdstr(EventName(lEvent)) <<" is to be processed";
    Log(lDebug3)<<"Path1: "<<path1<<"\tPath2: "<<path2;

    //What event are we processing?
    switch(lEvent)
    {
        //------------ Folder stuff..
        case SHCNE_MKDIR:
            Log(lDebug3)<<"Folder was created";
            AddFolderInTree(path1);
        break;

        case SHCNE_RMDIR:
            Log(lDebug3)<<"Folder was removed";
            RemoveFileSystemItemInTree(path1);
        break;

        case SHCNE_UPDATEDIR:
            Log(lDebug3)<<"Updated dir";
        break;
        case SHCNE_RENAMEFOLDER:
            Log(lDebug3)<<"Folder was renamed";
        break;

        //------------- Non folderstuff
        case SHCNE_CREATE:
            Log(lDebug3)<<"File item was created";
            AddFileInTree(path1);
        break;

        case SHCNE_DELETE:
            Log(lDebug3)<<"A File item was deleted";
            RemoveFileSystemItemInTree(path1);
        break;
        case SHCNE_RENAMEITEM:
            Log(lDebug3)<<"File item was renamed";
        break;

        case SHCNE_UPDATEITEM:
            Log(lDebug3)<<"Updateing item";
        break;

        default:
            Log(lDebug3)<<"Event was not handled!";
        break;
    }
}

bool dslFileSystemTreeWatcher::RemoveFileSystemItemInTree(const string& path1)
{
    //Go trough the tree and if found, remove the node...
    Log(lDebug3)<<"Removing file "<<path1<< " from tree";

       TTreeNode* sibling = mTree.GetNodeAt(0,0);
    if(sibling) do

    {

        if(sibling->Data)

        {

            dslFileSystemItem* existingItem =  (dslFileSystemItem*) (sibling->Data);

            if(existingItem)

            {

                string fPath = existingItem->GetFullPath();

                  if(existingItem->GetFullPath() == path1)

                {

                    Log(lDebug5)<<"Found "<<path1;

                    break;

                }

            }

        }

        sibling = sibling->GetNext();

    } while(sibling);


    if(sibling)

    {

        sibling->Delete();

    }

    return true;
}

bool dslFileSystemTreeWatcher::AddFileInTree(const string& path1)
{
    //Get the path to the new folder
    string path = stdstr(ExtractFileDir(path1.c_str()));
    string fName = path1;//stdstr(GetFileName(path1.c_str()));
    dslFileSystemItem* anItem = new dslFileItem(fName, path);

    if(anItem)
    {
        AddFileSystemItem(anItem);
    }

       return true;
}

bool dslFileSystemTreeWatcher::AddFolderInTree(const string& path1)
{
    vector<string> folders =  splitString(path1, "\\");

    string pathTo = extractPathTo(path1);    //Simply remove the file name / or last folder
    string lbl = (folders.size()) ? folders[folders.size()-1] : string("Weird..");

    dslFileSystemItem* anItem = new dslFolderItem(lbl, pathTo);

    if(anItem)
    {
        AddFileSystemItem(anItem);
    }
       return true;
}

bool dslFileSystemTreeWatcher::AddFileSystemItem(dslFileSystemItem* anItem)
{
    if(!anItem)
        return false;

    //Find where to place this item
    String pathTo = vclstr(anItem->GetPathTo());
       TTreeNode* parent = FindTreeFolderNodeBasedOnFullPath(mTree.Items, pathTo);

    if(anItem->IsFileItem())
    {
        //Adding a file item..
        TTreeNode* newNode = mTree.Items->AddChildObjectFirst(parent, anItem->GetLabel().c_str(), anItem);
        if(newNode)
        {
            newNode->ImageIndex     = anItem->GetIconIndex();
            newNode->SelectedIndex  = anItem->GetIconSelectedIndex();
        }
    }
    else
    {
        //Adding a folder item..
        TTreeNode* newNode = mTree.Items->AddChildObject(parent, anItem->GetLabel().c_str(), anItem);
        if(newNode)
        {
            newNode->ImageIndex     = anItem->GetIconIndex();
            newNode->SelectedIndex  = anItem->GetIconSelectedIndex();
        }
    }
    return true;
}
                        dslFileSystemTreeWatcher::dslFileSystemTreeWatcher(TTreeView& tree) : mTree(tree) {}
                   dslFileSystemTreeWatcher::~dslFileSystemTreeWatcher(){}
