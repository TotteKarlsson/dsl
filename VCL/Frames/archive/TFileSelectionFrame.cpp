#pragma hdrstop
#include <algorithm>
#include "TFileSelectionFrame.h"
#include "dslFileUtils.h"
#include "dslVCLUtils.h"
#include "dslFileSystemTreeItems.h"
#include "dslTreeComponentUtils.h"
#include "dslLogger.h"
#include "dslPackageDefs.h"
using namespace dsl;
using namespace std;
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFileSelectionFrame *FileSelectionFrame;

//---------------------------------------------------------------------------
__fastcall TFileSelectionFrame::TFileSelectionFrame(TComponent* Owner)
:
TFrame(Owner)
{
    mExcludeDirs.push_back(".svn");

    // use to keep track of entry info that has been modified, but not saved into the record
    mNodeToRemember = nullptr;
    //    ImageListTreeViewIcons->Overlay(gDeleted,    0);
}

__fastcall TFileSelectionFrame::~TFileSelectionFrame()
{
    ClearAll(TreeView1->Items);
    TreeViewUndo->Items->Clear();
    TreeViewRedo->Items->Clear();
}

bool __fastcall    TFileSelectionFrame::MonitorFolder(const string& fldr, const string& extension)
{
    mFileRootAndExtentions.push_back( pair<string, string>(fldr, extension));
    return true;
}

bool __fastcall    TFileSelectionFrame::RemoveMonitoredFolders()
{
    mFileRootAndExtentions.clear();
    ClearTree();
    return true;
}

void __fastcall    TFileSelectionFrame::ClearTree()
{
    ClearAll(TreeView1->Items);
}

void __fastcall TFileSelectionFrame::CreateTree()
{
    for(int i = 0 ; i < mFileRootAndExtentions.size(); i++)
    {
        bool res = ScanDataFolder(mFileRootAndExtentions[i].first, mFileRootAndExtentions[i].second);
    }
}

//Move these ones to the tree frame...
dslFileSystemItem* __fastcall TFileSelectionFrame::GetSelectedFileSystemTreeItem()
{
    TTreeNode* aNode = GetSelected();

    if(aNode && aNode->Data)
    {
        dslFileSystemItem* item = static_cast<dslFileSystemItem*>(aNode->Data);
        return item;
    }
    return nullptr;
}

string    __fastcall TFileSelectionFrame::GetSelectedFileInTree()
{
    string aFile;
    dslFileSystemItem* item = GetSelectedFileSystemTreeItem();
    if(item)
    {
           dslFileItem* fItem = dynamic_cast<dslFileItem*>(item);
        if(fItem)
        {
            aFile = fItem->GetFullPath();
        }
    }
    return aFile;
}

//---------------------------------------------------------------------------
void __fastcall TFileSelectionFrame::ActionNodeModifyExecute(TObject *Sender)
{
    if (!mNodeToRemember)
    {
        return;
    }

    TTreeNode *tempnode = mNodeToRemember;

    dslFileItem* info;
    if (tempnode->Data == nullptr)  //  data not already established for this node
    {
//        info = new TPersonalInfo;
        //TransferPersonalInfoFromEditEntry(GetNewID(),text,info);
//        tempnode->Data = info;
    }
    else
    {
        info = (dslFileItem*)(tempnode->Data);      // cast data into TInfo pointer
        //TransferPersonalInfoFromEditEntry(info->ID,text,info);
        if(info)
        {
            mNodeToRemember->Text = info->GetLabel().c_str();
        }
    }

    AddCountToNode(TreeView1->Items);
    ActionNodeModify->Enabled = false;
    mNodeToRemember = nullptr;
}

//---------------------------------------------------------------------------
void __fastcall TFileSelectionFrame::ActionNodeMoveUpExecute(TObject *Sender)
{
     // move the item up.
     MoveUpTree(TreeView1->Selected);
}

//---------------------------------------------------------------------------
void __fastcall TFileSelectionFrame::ActionNodeMoveDownExecute(TObject *Sender)
{
     // move the item down.
     if (!TreeView1->Selected)
     {
        MessageBeep(MB_OK);
        return;
     }

     // move up the item below it..
     TTreeNode *pItem = TreeView1->Selected->getNextSibling();
     if (pItem != nullptr)
     {
          MoveUpTree(pItem);
     }
     else
     {
          MessageBeep(MB_OK);
     }
}

//---------------------------------------------------------------------------
void __fastcall TFileSelectionFrame::ActionNodeFindLabelExecute(TObject *Sender)
{
   // let's call a routine that will build the text label for the node we want to search for
   String search = "Test";//CreateLabel(EditFirstName->Text,EditLastName->Text);
   TTreeNode* aNode = FindTreeNodeBasedOnLabel(TreeView1->Items,search);
   if (aNode)
   {
        // found it
        TreeView1->Items->Item[aNode->AbsoluteIndex]->Selected = true;
        ReflectNodeLabel(TreeView1->Selected);
   }
}

//---------------------------------------------------------------------------
void __fastcall TFileSelectionFrame::ActionNodeAddFileExecute(TObject *Sender)
{
    // let's call a routine that will build the text label for the new tree node
    String text = "File";

    // let's add the node to the tree
    TTreeNode* tempnode = TreeView1->Items->AddChild(TreeView1->Selected, text);

    // select the node we just added
    tempnode->Selected = true;

    TreeView1Click(Sender);  // to refresh
}

TTreeNode* __fastcall TFileSelectionFrame::AddFolder(const string& folder, const string& parentPath, TTreeNode* parent, const bool& isRoot)
{
    dslFileSystemItem* fInfo = new dslFolderItem(folder, parentPath, isRoot);
    TTreeNode* tempNode = nullptr;

    // Add the node to the tree
    tempNode = TreeView1->Items->AddChildObject(parent, folder.c_str(), fInfo);

    SetupNode(tempNode, fInfo);
    return tempNode;
}

TTreeNode* __fastcall TFileSelectionFrame::AddFile(const string& fileName, const string& parentPath, TTreeNode* parent)
{
    dslFileSystemItem* fInfo = new dslFileItem(fileName, parentPath);

    // add the node to the tree
    TTreeNode* tempNode     = TreeView1->Items->AddChildObject(parent, fileName.c_str(), fInfo);

    SetupNode(tempNode, fInfo);
    return tempNode;
}

void __fastcall TFileSelectionFrame::SetupNode(TTreeNode* tempNode, dslFileSystemItem* fInfo)
{
    tempNode->ImageIndex     = fInfo->GetIconIndex();
    tempNode->SelectedIndex = fInfo->GetIconSelectedIndex();
    ActionNodeDeleteSoft->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TFileSelectionFrame::ActionEditUndoExecute(TObject *Sender)
{
    // take top item of undo tree and set it's delete flag to false.
    TTreeNode *undonode = TreeViewUndo->Items->GetFirstNode();
    if (!undonode)
    {
        MessageBeep(MB_OK);
        return;
    }

    dslTreeItemBase* info = PTreeItemBase(undonode->Data);

    TTreeNode* aNode =  FindTreeNodeBasedOnID(TreeView1->Items, info->GetID());
    if (aNode)
    {
//          TTreeNode * node = TreeView1->Items->Item[absindex];

         // put it on top of redo tree view
//         ActionEditRedo->Enabled = AddToUndoRedoList(TreeViewRedo->Items, info->GetID(), info, aNode->ImageIndex, false);
         UndeleteNode(aNode);   // need to turn off the overlayindex... this takes care of children too.
         undonode->Delete();  // remove it out of the undo tree
         // refresh everything
         TreeView1Click(Sender);
    }
}

//---------------------------------------------------------------------------
void __fastcall TFileSelectionFrame::ActionEditRedoExecute(TObject *Sender)
{
    // take top item of redo tree and set it's delete flag to true.
    TTreeNode *redonode = TreeViewRedo->Items->GetFirstNode();
    if (!redonode)
    {
        MessageBeep(MB_OK);
        return;
    }
    dslTreeItemBase* info = PTreeItemBase(redonode->Data);

    TTreeNode* aNode =  FindTreeNodeBasedOnID(TreeView1->Items, info->GetID());
    if(aNode)
    {
//         TTreeNode * node = TreeView1->Items->Item[absindex];
         ActionEditRedo->Enabled = DeleteNode(aNode, true, true, TreeViewUndo->Items);
         redonode->Delete();  // remove it out of the redo tree
         TreeView1Click(Sender);    // refresh everything
    }
}

//---------------------------------------------------------------------------
void __fastcall TFileSelectionFrame::ActionFileClearExecute(TObject *Sender)
{
    ClearAll(TreeView1->Items);
    TreeViewUndo->Items->Clear();
    TreeViewRedo->Items->Clear();
}

//---------------------------------------------------------------------------
void __fastcall TFileSelectionFrame::ActionEditRefreshExecute(TObject *Sender)
{
    // this routine will refresh the tree view
    // causing any "soft" deleted nodes to be permanetly deleted
    if (TreeViewUndo->Items->Count > 0)
    {
        TreeViewUndo->Items->Clear();
    }

    if (TreeViewRedo->Items->Count > 0)
    {
        TreeViewRedo->Items->Clear();
    }

    ClearDeletedItems(TreeView1->Items);
    TreeView1Click(Sender);    // refresh everything
}

//---------------------------------------------------------------------------
void __fastcall TFileSelectionFrame::ActionTreeExpandExecute(TObject *Sender)
{
    TreeView1->FullExpand();
}

//---------------------------------------------------------------------------
void __fastcall TFileSelectionFrame::ActionTreeCollapseExecute(TObject *Sender)
{
    TreeView1->FullCollapse();
}

void __fastcall TFileSelectionFrame::TreeView1Click(TObject *Sender)
{
    // first save any information that was just modifed  (but what was that node?)
    ActionNodeModifyExecute(Sender);

    if (!TreeView1->Selected)
    {
        if (TreeView1->Items->Count == 0)
        {
            return;
        }
        TTreeNode *TopNode = TreeView1->Items->GetFirstNode();
        TopNode->Selected = true;
    }

    ReflectNodeLabel(TreeView1->Selected);
}

//---------------------------------------------------------------------------
//Update UI to reflect currently clicked, selected node
void __fastcall TFileSelectionFrame::ReflectNodeLabel(TTreeNode* node)
{
    String label = node->Text;
    StripParenCount(label);

    if (node->Data)
    {
        dslFileSystemItem *info  = (dslFileSystemItem*)(node->Data);    // cast data into dslTreeItemBase pointer

        if (info)
        {
            if(mAMemo)
            {
                mAMemo->Lines->Add(info->GetLabel().c_str());
                mAMemo->Lines->Add(info->GetPathTo().c_str());
            }
            DeleteFileA->Enabled = (info->IsFileItem()) ? true : false;
            Log(lInfo)<<"User selected file item:"<<info->GetLabel()<<" in folder "<<info->GetPathTo();
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TFileSelectionFrame::DeleteFileAExecute(TObject *Sender)
{
    TTreeNode* theNode             = TreeView1->Selected;
    dslFileSystemItem *info      = (dslFileSystemItem*)(theNode->Data);    // cast data into dslTreeItemBase pointer

    if(!info)
    {
        //Not a filesystem item... move on...
        return;
    }

    string fPath = info->GetFullPath();


    string msg = "Are you sure you want to permanently delete the file: ";
    msg += getFileName(fPath);
    if(MessageDlg(vclstr(msg), mtWarning, TMsgDlgButtons() << mbYes<<mbCancel, 0) == mrYes)
    {
        //Check return for user feedback..
        TTreeNode* newSelection = DeleteNode(theNode, true, false);
        if(newSelection)
        {
            removeFile(fPath);
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TFileSelectionFrame::ActionNodeDeleteSoftExecute(TObject *Sender)
{
    TTreeNode* theNode         = TreeView1->Selected;
    TTreeNode* parentnode     = TreeView1->Selected->Parent;
    TTreeNode* siblingnode     = TreeView1->Selected->getNextSibling();

    ActionEditUndo->Enabled = DeleteNode(theNode, true, true, TreeViewUndo->Items);

    if (siblingnode)
    {
        siblingnode->Selected = true;
    }
    else if (parentnode)
    {
        parentnode->Selected = true; // select the parent
    }
    else
    {
        DeleteFileA->Enabled = false;
        ActionNodeDeleteSoft->Enabled = false;
    }
    TreeView1Click(Sender);
}

//---------------------------------------------------------------------------
bool __fastcall    TFileSelectionFrame::ScanDataFolder(const string& path, const string& extensions)
{
    Cursor = crHourGlass;

    string fileMask = extensions;
    string folder = path;

//    if (folder [folder.size() - 1] != '\\')
//    {
//        folder = folder + "\\" ;
//    }

    //Create root
    TTreeNode* parent = AddFolder(folder, path, nullptr, true);

    //Add root folder
    FindFilesInDirectory(folder, fileMask, parent);

    // Put things back the way they were.
    Cursor = crDefault;
    return true;
}

void __fastcall TFileSelectionFrame::FindFilesInDirectory(const string &folder, const string& Extension, TTreeNode* parentNode)
{
    if(!parentNode)
    {
        return;
    }
    // This method searches the folder specified by the parameter and all
    // of its subdirectories for the file matching the value in SearchCustomEdit.
    // The folder name is assumed to end with a backslash.
    WIN32_FIND_DATAA filedata ;  // Structure for file data

    // Pass 1 - Search for the files within the folder.
    string fName = joinPath(folder, Extension);
    HANDLE filehandle = FindFirstFileA (fName.c_str(), &filedata);
    if (filehandle != INVALID_HANDLE_VALUE)
    {
        do
        {
            string theFile = stdstr(filedata.cFileName);
            AddFile(theFile, folder, parentNode);
        }
        while (FindNextFileA (filehandle, &filedata));
        FindClose(filehandle) ;
    }

    string dir = joinPath(folder.c_str(), "*.*");
    filehandle = FindFirstFileA (dir.c_str (), &filedata) ;
    if (filehandle != INVALID_HANDLE_VALUE)
    {
        do
        {
            if ( (filedata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0
                 && String (filedata.cFileName) != "."
                 && String (filedata.cFileName) != "..")
            {
                // Recursive call here
                string theDir = stdstr(filedata.cFileName);
                bool exclude = inStringList(theDir, mExcludeDirs);
                if(!exclude)
                {
                    //Add folder to tree
                    string fullPath = joinPath(folder, stdstr(filedata.cFileName));
                    TTreeNode* newParent = AddFolder(theDir, folder, parentNode);
                    FindFilesInDirectory(fullPath, Extension, newParent);
                }
            }
        }
        while (FindNextFileA (filehandle, &filedata)) ;
        FindClose(filehandle) ;
    }
}

TTreeNode* __fastcall TFileSelectionFrame::InTree(const string& fName, TTreeNode* parentFolder)
{
    if(!parentFolder)
    {
        return nullptr;
    }

    Log(lDebug5)<<"Checking "<<fName;
     TTreeNode* sibling = parentFolder->GetNext();

    if(sibling) do
    {
        if(sibling->Data)
        {
            dslFileSystemItem* existingItem =  (dslFileSystemItem*) (sibling->Data);
            if(existingItem)
            {
                  if(existingItem->GetLabel() == fName)
                {
                    Log(lDebug5)<<"Found "<<fName;
                    return sibling;
                }
            }
        }
        sibling = sibling->GetNext();
    } while(sibling);

    return nullptr;
}

void __fastcall TFileSelectionFrame::ReScanDataFolderAExecute(TObject *Sender)
{
    TreeView1->Items->BeginUpdate();
    ClearTree();

    //ScanDataFolder(mFileRoot, mFileExentsions);
    CreateTree();

    TreeView1->FullCollapse();
    TreeView1->Items->EndUpdate();

    if(TreeView1->GetNodeAt(0,0))
    {
        TreeView1->GetNodeAt(0,0)->Expanded = true;
    }
}

//---------------------------------------------------------------------------
void __fastcall TFileSelectionFrame::RefreshFolderExecute(TObject *Sender)
{
    //Rescan the currently selected folder
    TTreeNode* aNode = TreeView1->Selected;    //Selected may be a file or folder
    TTreeNode* parentFolderNode;
    if (aNode && aNode->Data)
    {
        dslFileSystemItem *info  = (dslFileSystemItem*)(aNode->Data);    // cast data into dslTreeItemBase pointer
        if(!info)
            return;

        //To finf correct folder, find out if item is a file or folder
        dslFolderItem*     folderItem     = dynamic_cast<dslFolderItem*>(info);
        dslFileItem*     fileItem     = dynamic_cast<dslFileItem*>(info);

        string folder;
        if(folderItem)
        {
            folder = (aNode == TreeView1->GetNodeAt(0,0)) ? info->GetPathTo() : info->GetFullPath();
            parentFolderNode = aNode;
        }
        else if(fileItem)
        {
            //Get parent theNode for the file item
            parentFolderNode = aNode->Parent;
            folder = info->GetPathTo();
        }

        Log(lInfo)<<"Refreshing folder: "<<folder;

        //Check if clicked item is a folder or not
        Log(lDebug1)<<"Updating files in "<<folder;
//        UpdateFilesInDirectory(folder, mFileExentsions.GetValue(), parentFolderNode);
        Log(lDebug1)<<"Finished updating files in "<<folder;

        //Check if any items need to be removed
           Log(lDebug1)<<"Removing file items in "<<folder;
//        RemoveFileItems(aNode);
           Log(lDebug1)<<"Finished removing file items in "<<folder;
        Log(lInfo)<<"Finished refreshing folder: "<<folder;
       }
}

void __fastcall TFileSelectionFrame::RemoveFileItems(TTreeNode* aNode)
{
    if(!aNode)
    {
        return;
    }

    for(int i = 0; i < aNode->Count; i++)
    {
        TTreeNode* sibling = aNode->Item[i];
        if(sibling)
        {
            dslFileSystemItem* existingItem =  (dslFileSystemItem*) (sibling->Data);
            if(existingItem)
            {
                string fileItem = (sibling ==  TreeView1->GetNodeAt(0,0)) ? existingItem->GetPathTo() : existingItem->GetFullPath();

                if(!fileExists(fileItem))
                {
                    sibling->Enabled = false;
                }
            }
        }

        if(sibling->HasChildren)
        {
            Log(lInfo)<<"Removing in folder: "<<stdstr(sibling->Text.c_str());
            RemoveFileItems(sibling);    //Recursive call
        }
    }
}

//---------------------------------------------------------------------------
void __fastcall TFileSelectionFrame::TreeView1ContextPopup(TObject *Sender, TPoint &MousePos, bool &Handled)
{
    TTreeNode* aNode = TreeView1->Selected;

    if (aNode && aNode->Data)
    {
        dslFileSystemItem *info  = (dslFileSystemItem*)(aNode->Data);    // cast data into dslTreeItemBase pointer

        //Check if clicked item is a filesystem item  or not
        RefreshFolder->Enabled = info ? true : false;
    }
}

void __fastcall TFileSelectionFrame::TreeView1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Button == mbRight)
    {
        TTreeNode* aNode = TreeView1->GetNodeAt(X, Y);
        if(aNode)
        {
            Log(lDebug)<<"Mouse Down: clicked on: " <<stdstr(aNode->Text.c_str());

            dslFileSystemItem* item = (dslFileSystemItem*)(aNode->Data);
            if(item)
            {
                Log(lDebug)<<"NodeMouseUp..."<<item->GetLabel();
                Log(lDebug)<<"Selection count..."<<TreeView1->SelectionCount;
            }

            aNode->Selected = true;
            ReflectNodeLabel(aNode);
        }
    }
}

void __fastcall TFileSelectionFrame::TreeView1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    TTreeNode* aNode  = (TTreeNode*) (Sender);
    if(Button == mbRight)
    {
    }
}

TTreeNode* __fastcall TFileSelectionFrame::GetSelected()
{
    return TreeView1->Selected;
}

static inline void ValidCtrCheck(TFileSelectionFrame *)
{
    new TFileSelectionFrame(nullptr);
}

namespace Tfileselectionframe
{
    void __fastcall PACKAGE Register()
    {
        //ShowMessage("Registered Tfileselectionframe");
        TComponentClass classes[1] = {__classid(TFileSelectionFrame)};
        RegisterComponents("Dune Components", classes,0);
    }
}

