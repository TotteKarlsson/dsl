
#pragma hdrstop
#include <algorithm>
#include "dslVCLUtils.h"

#include "dslActionToolBarManager.h"
#pragma link "dslActionManagerHelper"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(dslActionToolBarManager *)
{
    new dslActionToolBarManager(nullptr);
}
//---------------------------------------------------------------------------
__fastcall dslActionToolBarManager::dslActionToolBarManager(TComponent* Owner)
    : dslActionManagerHelper(Owner)
{
}
//---------------------------------------------------------------------------
namespace Mtkactiontoolbarmanager
{
    void __fastcall PACKAGE Register()
    {
        TComponentClass classes[1] = {__classid(dslActionToolBarManager)};
        RegisterComponents(dslComponents::gDuneComponents, classes, 0);
    }
}
//---------------------------------------------------------------------------
bool __fastcall dslActionToolBarManager::PopulateToolBars()
{
    //Add actions to action tool bar if set
    if(!FCoolBar && !FActionManager && !FPluginManager)
        return false;

    //First find out how many 'ToolBar" categories we have
    vector<string> cats;
    GetPluginToolBarCategories(cats);    //!Plugins defines a toolbar category if to be placed on a toolbar
    TActionClientItem* lastItem = nullptr;
    TActionClientItem* newItem = FActionToolBar->FindLastVisibleItem();

    for(int categoryIndex = 0; categoryIndex < cats.size(); categoryIndex++)
    {
        String currCat = cats[categoryIndex].c_str();
        if(lastItem != newItem)
        {
            FActionManager->AddSeparator(newItem, true);
            lastItem = FActionToolBar->FindLastVisibleItem();
            newItem = lastItem;

        }

        for(int i = 0; i < FPluginManager->PluginCount; i++)
        {
            dslPluginBase* plugin = FPluginManager->Plugins[i];
            if(plugin->PlaceOnToolBar())
            {
                //Check plugin category, i.e. top menu item name, like File, Help etc
                String category = plugin->GetToolBarCategory();
                if(!CompareText(category, currCat))
                {
                    //Check if there is a toolbar for this category
                    //For now, use FActionToolBar
                    //TActionClientItem* topMenuItem = this->FindItemByCaption(category, FActionMainMenuBar);

                    if(FActionToolBar)
                    {
                        newItem                     = FActionToolBar->ActionClient->Items->Add();
                        newItem->Action             = plugin->GetPluginAction(FToolBarIconSize);
                    }
                }
            }
        }
    }

    UpdateToolBarSize(FActionToolBar);
    return true;
}
void __fastcall    dslActionToolBarManager::UpdateToolBarSize(TActionToolBar *actionToolBar)
{
    switch (FToolBarIconSize)
    {
         case SIZE_16x16:    actionToolBar->Height = 24;    break;
         case SIZE_24x24:    actionToolBar->Height = 34;    break;
         case SIZE_32x32:    actionToolBar->Height = 44;    break;

        default:
        actionToolBar->Height = 44;    break;
    }
}

int __fastcall dslActionToolBarManager::GetPluginToolBarCategories(vector<string>& cats)
{
    int addedCats = 0;
    //Go trough all categories in the plugin manager as well as in the action manager
    for(int I = 0; I < FPluginManager->PluginCount; I++)
    {
        dslPluginBase* plugin = FPluginManager->Plugins[I];
        string category = plugin->GetToolBarCategory();
        if(find(cats.begin(), cats.end(), category) == cats.end())
        {
            if(category.size())
            {
                addedCats++;
                cats.push_back(category);
//                                        LogMessage("Added Plugin Category" + category, dslLogger::Debug);
            }
        }
    }
    return addedCats;
}

void __fastcall dslActionToolBarManager::AddActionsToActionToolBar(vector<TContainedAction*> *list, TActionBarItem* actionBarItem)
{
    if(!actionBarItem || !list)
        return;
    for(unsigned int i = 0; i < list->size(); i++)
    {
        TContainedAction *anAction = list->at(i);
        //Add an ctionclient to the action bar
        TActionClientItem *ActionClient = actionBarItem->Items->Add();
        //Set action to plugin action
        ActionClient->Action = list->at(i);
    }

}
void __fastcall dslActionToolBarManager::RemoveActionsFromActionToolBar(TCustomActionList* list, TActionToolBar *actionToolBar)
{
    if(!actionToolBar || !list)
        return;

    int i = 0;
    while( i < actionToolBar->ActionClient->Items->Count )
    {
        TActionClientItem *actionClient = actionToolBar->ActionClient->Items->ActionClients[i];
        bool found = false;

        for(int j = 0; j < list->ActionCount; ++j)
        {
            if( actionClient->Action == list->Actions[j] )
            {
                found = true;
                break;
            }
        }

        if( found )
            actionToolBar->ActionClient->Items->Delete(i);
        else
            ++i;
    }
}

void __fastcall dslActionToolBarManager::AddActionsToActionToolBar(TCustomActionList* list, TActionBarItem* actionBarItem, const String& category)
{
    if(!actionBarItem || !list)
        return;

    for(unsigned int i = 0; i < list->ActionCount; i++)
    {
        TContainedAction *anAction = list->Actions[i];
        if(!CompareText(anAction->Category, category))
        {
            //Add an ctionclient to the action bar
            TActionClientItem *ActionClient = actionBarItem->Items->Add();
            //Set action to plugin action
            ActionClient->Action = list->Actions[i];
        }

    }
    actionBarItem->Refresh();
}

