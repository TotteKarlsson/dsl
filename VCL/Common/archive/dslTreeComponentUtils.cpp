#pragma hdrstop
#include "dslTreeComponentUtils.h"
#include "dslVCLUtils.h"
#include "dslTreeItemBase.h"
#include "dslFileSystemTreeItems.h"
#pragma package(smart_init)

using namespace dsl;
//---------------------------------------------------------------------------
void __fastcall MoveUpTree(TTreeNode *item)
{
     if (item == nullptr)
     {
        MessageBeep(MB_OK);
        return;
     }
     TNodeAttachMode AttachMode = naInsert;

     TTreeNode *ppItem = item->getPrevSibling();

     int level = item->Level;
     if (ppItem == nullptr)
     {
          MessageBeep(MB_OK);
          return;
     }

     if (ppItem->Level != level)
     {
          MessageBeep(MB_OK);
          return;
     }
     item->MoveTo(ppItem, AttachMode);
}

//---------------------------------------------------------------------------
TTreeNode* __fastcall FindTreeNodeBasedOnLabel(TTreeNodes *Tree, const String& SearchString)
{
     TTreeNode* CurItem = Tree->GetFirstNode();
     if (CurItem) do
     {
        String title = CurItem->Text;
        StripParenCount(title);
        if (AnsiCompareStr(title,SearchString) == 0)
         {
            return CurItem;//->AbsoluteIndex;
        }
        CurItem = CurItem->GetNext();
     }
     while (CurItem);

    return nullptr;  // couldn't find it..
}

//---------------------------------------------------------------------------
TTreeNode* __fastcall FindTreeFolderNodeBasedOnFullPath(TTreeNodes *Tree, const String& SearchString)
{
    TTreeNode* CurItem = Tree->GetFirstNode();

    dslFileSystemItem* item      ;
    dslFolderItem*     folderItem;

     if (CurItem) do
     {
         item        = static_cast<dslFileSystemItem*>(CurItem->Data);
        folderItem     = dynamic_cast<dslFolderItem*>(item);

        if(folderItem)
        {
            String path = vclstr(folderItem->GetFullPath());
                //StripParenCount(title);
            if (AnsiCompareStr(path,SearchString) == 0)
             {
                return CurItem;
            }
        }
        CurItem = CurItem->GetNext();
     }
     while (CurItem);

    return nullptr;  // couldn't find it..
}

//---------------------------------------------------------------------------
TTreeNode*  __fastcall FindTreeNodeBasedOnID(TTreeNodes *Tree,unsigned int ID)
{
    TTreeNode *CurItem = Tree->GetFirstNode();
    int count =0;
    if (CurItem) do
    {
        if (CurItem->Data)
        {
            if (PTreeItemBase(CurItem->Data)->GetID() == ID)
            {
                return CurItem;//->AbsoluteIndex;
            }
            count++;
        }

        CurItem = CurItem->GetNext();
    }
    while (CurItem);
    return nullptr;
}

//---------------------------------------------------------------------------
void __fastcall AddCountToNode(TTreeNodes* tree)
{
    tree->BeginUpdate();
    TTreeNode *CurItem = tree->GetFirstNode();
    while (CurItem)    //walk down all the nodes of the tree
    {
        CurItem->Count;
           String NewName = CurItem->Text;
           StripParenCount(NewName);

           if (CurItem->Count > 0)
        {
            CurItem->Text = NewName + "  (" + CurItem->Count + ")";
        }
           else
        {
            CurItem->Text = NewName;
        }
           CurItem = CurItem->GetNext();
    }
    tree->EndUpdate();
}

//---------------------------------------------------------------------------
bool __fastcall StripParenCount(String& text)
{
    String NewName;
    bool result = true;
    int location = text.Pos("  (");
    if (location > 0)
    {
        NewName = text.SubString(1,(location-1));
        result = true;
    }
    else  // nothing to strip
    {
        result = false;
        return result;
    }
    text = NewName;
    return result;
}

//---------------------------------------------------------------------------
bool __fastcall AddToUndoRedoList(TTreeNodes * Tree, unsigned int ID, dslTreeItemBase *info, int imageindex, bool deletedflag)
{
  // look for items that already have the ID we're going to insert and delete it...
       int index = 0;
       do
       {
           TTreeNode* aNode = FindTreeNodeBasedOnID(Tree,ID);
        if (aNode)
        {
            aNode->Delete();
        }
       }
    while (index > -1);

       // okay, now we can add it.
       TTreeNode *node = Tree->AddObjectFirst(nullptr, info->GetLabel().c_str(), info);
       node->StateIndex = imageindex;
       node->ImageIndex = imageindex;
       info->SoftDelete(deletedflag);

       return  (bool)Tree->Count;
}

//---------------------------------------------------------------------------
unsigned int __fastcall GetNewID()
{
    GUID guid;
    ::CoCreateGuid(&guid);
    return guid.Data1;
}

//---------------------------------------------------------------------------
void __fastcall ClearAll(TTreeNodes* tree)
{
    TTreeNode *CurItem = tree->GetFirstNode();
    dslTreeItemBase *info;
    while (CurItem)    //walk down all the nodes of the tree and delete data
    {
        if (CurItem->Data)
           {
            info = (dslTreeItemBase*)(CurItem->Data);
            delete info;
           }
           CurItem = CurItem->GetNext();
    }
    // now that all the data is deleted, the tree can be deleted
    tree->Clear();
}

//---------------------------------------------------------------------------
// makes soft deletes hard deletes
void __fastcall ClearDeletedItems(TTreeNodes* tree)
{
    tree->BeginUpdate();  // prevent screen update of tree view
    TTreeNode *CurItem = tree->GetFirstNode();
    TTreeNode *NextItem;
    dslTreeItemBase *info;

    while (CurItem)    //walk down all the nodes of the tree and delete appropriate nodes
    {
       NextItem = CurItem->GetNext();   // keep track of potential next node
       if (CurItem->Data)
       {
           info = (dslTreeItemBase*)(CurItem->Data);
           if (info->SoftDelete())
           {
               NextItem = DeleteNode(CurItem,false,false,nullptr); // hard delete, no message, no undo list
           }
       }
       CurItem = NextItem;
    }
    tree->EndUpdate();  // enabled screen update
}

//---------------------------------------------------------------------------
TTreeNode* __fastcall DeleteNode(TTreeNode *node, bool displaymessage, bool soft, TTreeNodes * undolist)
{
    // recursive function
    if (!node)
    {
        return nullptr;  // no tree node.. get out
    }

    TTreeNode *tempnode = nullptr;

    // take care of children first
    int count = node->Count;
    while (count > 0)  // can't use HasChildren property for soft deletes
    {
        int response = IDYES;
        if (displaymessage)
        {
               // notify user of branch deletion
            response =
                Application->MessageBox(L"Are you sure you wish to delete the whole folder?", L"Folder contain files", MB_YESNO);
        }
        if (response == IDNO)
        {
            MessageBeep(MB_OK);
            return nullptr;
        }
        else
        {
            displaymessage = false;
            tempnode =  node->GetPrevChild(tempnode);
            if (tempnode == nullptr)
            {
                tempnode = node->GetLastChild();
            }
            if (tempnode)
            {
                DeleteNode(tempnode,false,soft,nullptr);  // call itself with next child,
            }

            //messages are no longer displayed (false), no need for undo list (nullptr)
            if (!soft)
            {
                tempnode = nullptr;
            }
        }
        count--; // decrement children count
    }

    if (soft) // soft delete (undo support)
    {
        dslTreeItemBase *info;
        if (node->Data)
        {
            info = (dslTreeItemBase*)(node->Data);
        }
        else
        {   // better add data in case the user hits undo
            // Here's where we add the information to the tree
//            info = new TPersonalInfo;
//            info->mID = GetNewID();   // get a unique id
//            info->mLabel = stdstr(node->Text);
//            node->Data = (void*)info; // now add it as an object to the node
        }

        info->SoftDelete(true);  // mark it for deletion
        if (undolist)
        {
            AddToUndoRedoList(undolist,info->GetID(), info, node->ImageIndex, true);
        }
        node->OverlayIndex = 0;
        return node->GetNext();  // return the next node
    }
    else // hard delete (no undo support)
    {
        TTreeNode* nextnode = node->GetNext(); // get the next node before we delete it
        if (node->Data)
        {
            dslTreeItemBase * info = (dslTreeItemBase*)(node->Data);
            delete info;           // delete data
        }
        node->Delete();     // delete node
        return nextnode;
    }
}

//---------------------------------------------------------------------------
void __fastcall UndeleteNode(TTreeNode *node)   // this is recursive too
{
    if (!node) return;
       TTreeNode* tempnode = nullptr;
       int count = node->Count;  // check the children
       while (count > 0)
       {
           tempnode =  node->GetNextChild(tempnode);
        if (tempnode == nullptr)
        {
            tempnode = node->getFirstChild();
        }
        if (tempnode)
        {
            UndeleteNode(tempnode);
        }
        count--;
   }
   node->OverlayIndex = -1;
}


