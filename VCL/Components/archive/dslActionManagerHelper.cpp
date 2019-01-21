
#pragma hdrstop
#include "dslPluginManager.h"
#include "dslActionManagerHelper.h"
#include "dslVCLUtils.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//
static inline void ValidCtrCheck(dslActionManagerHelper *)
{
    new dslActionManagerHelper(nullptr);
}

namespace Mtkactionmanagerhelper
{
    void __fastcall PACKAGE Register()
    {
        TComponentClass classes[1] = {__classid(dslActionManagerHelper)};
        RegisterComponents(dslComponents::gDuneComponents, classes, 0);
    }
}
//---------------------------------------------------------------------------
__fastcall dslActionManagerHelper::dslActionManagerHelper(TComponent* Owner)
    : TComponent(Owner)
{
}

void __fastcall dslActionManagerHelper::DeleteActionItems(TActionList* aList)
{
    if(!FActionManager)
        return;

    RemoveActionsFromActionManager(aList, FActionManager);
}

TActionClientItem* __fastcall  dslActionManagerHelper::FindItemByCaption(const String& ACaption)
{
    FCompareProc = (dslActionManagerHelper::CompareCaption);
    FCaption = ACaption;
    return FindItem();
}

TActionClientItem* __fastcall dslActionManagerHelper::FindItemByAction(TCustomAction* Action)
{
    FCompareProc = (dslActionManagerHelper::CompareAction);
      FAction = Action;
    return FindItem();
}

TActionClientItem* __fastcall dslActionManagerHelper::FindItem()
{
    TActionClientItem* CI = nullptr;
    if(!FActionManager) return nullptr;

    FFoundClient = nullptr;
    FActionManager->ActionBars->IterateClients(FActionManager->ActionBars, FindClient);
    return FFoundClient;
}

void __fastcall dslActionManagerHelper::FindClient(TActionClient* AClient)
{
    if(AClient && FCompareProc && FFoundClient)
        return;
    (FCompareProc)(AClient);
    CompareCaption(AClient);
}

TActionClientItem* __fastcall dslActionManagerHelper::AddAction(TCustomAction* anAction, TActionClient* anActionClient, bool after)
{
//  Result := nil;
//  if (FActionManager = nil) or (AClient = nil) or
//     (AClient.Collection = nil) then exit;
//  Result := TActionClientItem(AClient.Collection.Add);
//  Result.Index := AClient.Index + Integer(After);
//  Result.Action := AnAction;
    if(!FActionManager || !anActionClient || !anActionClient->Collection)
    return nullptr;
    TActionClientItem* newACI = (TActionClientItem*) anActionClient->Collection->Add();
    newACI->Index = anActionClient->Index + after;
    newACI->Action = anAction;

    return newACI;
}
TActionClientItem* __fastcall dslActionManagerHelper::AddSeperator(TActionClientItem* anActionClientItem, bool after)
{
//function TAMHelp.AddSeparator(
//  AnItem: TActionClientItem; After: Boolean = True): TActionClientItem;
    //begin
//      Result := nil;
//      if (FActionManager = nil) or (AnItem = nil) or
//         (AnItem.ActionClients = nil) then exit;
//      Result := AnItem.ActionClients.Add;
//      Result.Caption := '|';
//      Result.Index := AnItem.Index + Integer(After);
//    end;
    if (!FActionManager && !anActionClientItem && anActionClientItem->ActionClients)//&& !anActionClient->Acor
        return nullptr;

    TActionClientItem *newItem = anActionClientItem->ActionClients->Add();
    newItem->Caption = "|";
    newItem->Index = anActionClientItem->Index + (int) after;
    return newItem;
}

void __fastcall dslActionManagerHelper::CompareCaption(TActionClient* AClient)
{
    if(!AClient)
        return;

    TActionClientItem* item = (TActionClientItem*) AClient;
    if( item && !CompareText(item->Caption, FCaption))
    {
        FFoundClient = (TActionClientItem*) AClient;
    }
}

void __fastcall dslActionManagerHelper::CompareAction(TActionClient* AClient)
{
    if(!AClient)
        return;
}

TActionClientItem* __fastcall dslActionManagerHelper::InsertCategory(const String& aCategory, TActionClient* anActionClient, bool after)
{
    if(!FActionManager || !anActionClient)
        return nullptr;

    vector<TContainedAction*> *Actions = new vector<TContainedAction*>;
    AddActions(Actions, FActionManager, aCategory);

    for(int I = 0; I < FActionManager->LinkedActionLists->Count; I++)
    {
        TActionListItem* actionListItem = FActionManager->LinkedActionLists->ListItems[I];
        AddActions(Actions, actionListItem->ActionList, aCategory);
    }

    TActionClientItem* newClient = FActionManager->DefaultActionBars->Add()->Items->Add();
    newClient->Caption = aCategory;
    newClient->Collection = anActionClient->Collection;
    newClient->Index = anActionClient->Index + after;
    for(unsigned int I = 0; I < Actions->size(); I++)
    {
        newClient->Items->Add()->Action = Actions->at(I);
    }
    if(newClient->Control)
        newClient->Control->Enabled = true;
    return newClient;
}

TActionClientItem* __fastcall dslActionManagerHelper::InsertCategory(const String& aCategory, TCollection* collection, int index)
{
    if(!FActionManager)// || !AClient)
        return nullptr;

    if(!collection)
    {
        //Check if there are any clients on the main menu
    }

    vector<TContainedAction*> *Actions = new vector<TContainedAction*>;
    AddActions(Actions, FActionManager, aCategory);

    for(int I = 0; I < FActionManager->LinkedActionLists->Count; I++)
    {
        TActionListItem* actionListItem = FActionManager->LinkedActionLists->ListItems[I];
        AddActions(Actions, actionListItem->ActionList, aCategory);
    }

    TActionClientItem* newClient = FActionManager->DefaultActionBars->Add()->Items->Add();
    newClient->Caption = aCategory;
    newClient->Collection = collection;
    newClient->Index = index;
    for(int I = 0; I < Actions->size(); I++)
    {
        newClient->Items->Add()->Action = Actions->at(I);
    }
    if(newClient->Control)
        newClient->Control->Enabled = true;
    return newClient;
}

TActionClientItem*  __fastcall dslActionManagerHelper::AddToCategory(const String& category)
{
    TActionClientItem*    anActionClientItem = FindItemByCaption(String("&") + category);
    if(!anActionClientItem)
        return nullptr;

       vector<TContainedAction*> *Actions = new vector<TContainedAction*>;
    AddActions(Actions, FActionManager, category);

    for(int I = 0; I < FActionManager->LinkedActionLists->Count; I++)
    {
        TActionListItem* actionListItem = FActionManager->LinkedActionLists->ListItems[I];
        AddActions(Actions, actionListItem->ActionList, category);
    }

    int nrOfActions = Actions->size();
    for(int I = 0; I < Actions->size(); I++)
    {
        //Before adding the action, make sure its not already there
        bool addAction = true;
        for(int i = 0; i < anActionClientItem->Items->Count; i++)
        {
            TContainedAction* action = anActionClientItem->Items->ActionClients[i]->Action;
            if(anActionClientItem->Items->ActionClients[i]->Action == Actions->at(I))
                addAction= false;
        }

        TContainedAction* action = Actions->at(I);
        if(addAction)
            anActionClientItem->Items->Add()->Action = Actions->at(I);
    }
    delete Actions;
    return nullptr;
}

TActionClientItem* __fastcall dslActionManagerHelper::AddCategory(const String& aCategory, bool after)
{
    TActionClientItem*    AClient = FindItemByCaption("&File"); //Fix this!!
    if(!FActionManager)
        return nullptr;

    vector<TContainedAction*> *Actions = new vector<TContainedAction*>;
    AddActions(Actions, FActionManager, aCategory);

    for(int I = 0; I < FActionManager->LinkedActionLists->Count; I++)
    {
        TActionListItem* actionListItem = FActionManager->LinkedActionLists->ListItems[I];
        AddActions(Actions, actionListItem->ActionList, aCategory);
    }

    TActionClientItem* newClient = FActionManager->DefaultActionBars->Add()->Items->Add();
    newClient->Caption = aCategory;
    newClient->Collection = AClient->Collection;
    newClient->Index = 0 + (int) after;
    for(unsigned int I = 0; I < Actions->size(); I++)
    {
        newClient->Items->Add()->Action = Actions->at(I);
    }
    if(newClient->Control)
        newClient->Control->Enabled = true;
    return newClient;
}

int    __fastcall AddActions(vector<TContainedAction*> *Actions, TCustomActionList* ActionList, const String& aCategory)
{
    if(!ActionList)
        return -1;

    for(unsigned int I = 0; I < ActionList->ActionCount; I++)
    {
        String category = ActionList->Actions[I]->Category;
        if(!CompareText(category, aCategory))
        {
            TContainedAction* action = ActionList->Actions[I];
            Actions->push_back(ActionList->Actions[I]);
        }
    }
    return Actions->size();
}

//int    __fastcall RemoveActions(TCustomActionList* ActionList, const String& aCategory)
//{
//    if(!ActionList)
//        return -1;
//    int removed = 0;
//    for(unsigned int I = 0; I < ActionList->ActionCount; I++)
//    {
//        String category = ActionList->Actions[I]->Category;
//        if(!CompareText(category, aCategory))
//        {
//            TContainedAction* action = ActionList->Actions[I];
//            ActionList->Actions->
//            removed++;
//        }
//    }
//    return removed;
//}
//

