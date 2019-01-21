
#pragma hdrstop
#include "dslActionMainMenuManager.h"
#include "dslPackageDefs.h"
#include "dslVCLUtils.h"
#pragma link "dslActionManagerHelper"

#pragma package(smart_init)
//---------------------------------------------------------------------------

static inline void ValidCtrCheck(dslActionMainMenuManager *)
{
    new dslActionMainMenuManager(nullptr);
}
//---------------------------------------------------------------------------
__fastcall dslActionMainMenuManager::dslActionMainMenuManager(TComponent* Owner)
    : dslActionManagerHelper(Owner)
{
}
//---------------------------------------------------------------------------
namespace Mtkactionmainmenumanager
{
    void __fastcall PACKAGE Register()
    {
        TComponentClass classes[1] = {__classid(dslActionMainMenuManager)};
        RegisterComponents(dslComponents::gDuneComponents, classes, 0);
    }
}
//---------------------------------------------------------------------------
TActionClientItem* __fastcall dslActionMainMenuManager::GetFirstItemOnMainMenu()
{
    if(!FActionMainMenuBar)
        return nullptr;

    TActionClientItem* item = nullptr;
    int nrOfTopMenuItems = FActionMainMenuBar->ActionClient->Items->Count;
    if(nrOfTopMenuItems > 0)
        item = FActionMainMenuBar->ActionClient->Items->ActionClients[0];
    return item;
}

TActionClientItem* __fastcall dslActionMainMenuManager::GetLastItemOnMainMenu()
{
    if(!FActionMainMenuBar)
        return nullptr;

    TActionClientItem* item = nullptr;
    int nrOfTopMenuItems = FActionMainMenuBar->ActionClient->Items->Count;
    if(nrOfTopMenuItems > 0)
        item = FActionMainMenuBar->ActionClient->Items->ActionClients[nrOfTopMenuItems - 1];
    return item;
}

TActionClientItem* __fastcall dslActionMainMenuManager::FindTopMenuItemByCaption(const String& _caption, TActionMainMenuBar *actionMainMenuBar)
{
    TActionClientItem* topMenuItem = nullptr;
    String str = _caption;
    string aCaption = stdstr(str);
    int pos = aCaption.find( "&", 0 );
    if(pos != string::npos)
    {
        aCaption.erase(pos, 1);
    }

    int nrOfTopMenuItems = actionMainMenuBar->ActionClient->Items->Count;
    for(int i = 0; i < nrOfTopMenuItems; i++)
    {
        topMenuItem = actionMainMenuBar->ActionClient->Items->ActionClients[i];
        string menuCaption = stdstr(topMenuItem->Caption);
        int pos = menuCaption.find( "&", 0 );
        if(pos != string::npos)
        {
            menuCaption.erase(pos, 1);
        }

        if(menuCaption == aCaption)//The top menu already exists
        {
            return topMenuItem;
        }
    }

    return nullptr;
}

TActionClientItem* __fastcall dslActionMainMenuManager::FindItemByCaption(const String& _caption, TActionMainMenuBar *actionMainMenuBar)
{
    TActionClientItem* topMenuItem = nullptr;
    TActionClientItem* menuItem = nullptr;

    String ACaption = _caption;

    int nrOfTopMenuItems = actionMainMenuBar->ActionClient->Items->Count;
    for(int i = 0; i < nrOfTopMenuItems; i++)
    {
        topMenuItem = actionMainMenuBar->ActionClient->Items->ActionClients[i];
        String Caption = topMenuItem->Caption;
        //Loop down the menu
        for(int j = 0 ;j < topMenuItem->Items->Count; j++)
        {
            menuItem = topMenuItem->Items->ActionClients[j];
            if(menuItem->Caption == ACaption)
            {
                return menuItem;
            }
        }
    }

    return nullptr;
}

TActionClientItem* __fastcall dslActionMainMenuManager::AddMenuCategory(String& category, TActionClient* anActionClient, bool after)
{
    if(!anActionClient || !anActionClient->Collection)
        return nullptr;

    TCustomAction* newTopMenuAction = new TCustomAction(nullptr);
    newTopMenuAction->Caption = category;

    TActionClientItem* newACI = (TActionClientItem*) anActionClient->Collection->Add();
    newACI->Index = anActionClient->Index + after;
    newACI->Action = newTopMenuAction;
    return newACI;
}

bool __fastcall dslActionMainMenuManager::HideCategory(const String& category)
{
    //Get the top menu item "Development"
    TActionClientItem* actClient = FindTopMenuItemByCaption(category, FActionMainMenuBar);

    if(actClient)
    {
        actClient->Visible = false;
        return true;
    }
    return false;
}

bool __fastcall dslActionMainMenuManager::PopulateMainMenusWithPluginActions()
{
    if(!FActionMainMenuBar || !FPluginManager)
    {
        return false;
    }

    SetupIconsToUseOnMainMenu();

    for(int i = 0; i < FPluginManager->PluginCount; i++)
    {
        dslPluginBase* plugin = FPluginManager->Plugins[i];
        if(plugin->PlaceOnMenu())
        {
            //Check plugin category, i.e. top menu item name, like File, Help etc
            String category = plugin->GetMainMenuCategory();
            if(category.Length())
            {
                //Check if category exists on the menu
                TActionClientItem* topMenuItem = this->FindTopMenuItemByCaption(category, FActionMainMenuBar);

                if(!topMenuItem)    //Category is not on the menu yet
                {
                    //Create it before help. If help don't exists, create it last
                    TActionClientItem* helpItem = this->FindTopMenuItemByCaption("Help", FActionMainMenuBar);
                    if(helpItem)
                    {
                        topMenuItem                     = AddMenuCategory(category, helpItem, false);
                    }
                    else
                    {
                        TActionClientItem* lastItem     = GetLastItemOnMainMenu();
                        topMenuItem                     = AddMenuCategory(category, lastItem);
                      }
                }

                if(topMenuItem)
                {
                    TActionClientItem* newItem     = topMenuItem->Items->Add();
                    TAction* anAction             = plugin->GetAction16x16();
                    String actionCaption         = anAction->Caption;
                    newItem->Action             = plugin->GetAction16x16();
                    newItem->Caption            = actionCaption;

                    String beforeItem(plugin->PlaceBeforeMenuItem());
                    if(beforeItem.Length())
                    {
                        //Look for item
                        TActionClientItem*     item = FindItemByCaption(beforeItem, FActionMainMenuBar);
                        if(item)
                        {
                            newItem->Index    = item->Index;
                        }
                    }
                }
            }
        }
    }

    return true;
}

void __fastcall dslActionMainMenuManager::RemoveActionsFromActionMainMenuBar(TCustomActionList* list)
{
    if(!FActionMainMenuBar || !list)
        return;

    int i = 0;
    while( i < FActionMainMenuBar->ActionClient->Items->Count )
    {
        //These are the top menu items, we need to go down in the menu..
        TActionClientItem *actionClient = FActionMainMenuBar->ActionClient->Items->ActionClients[i];

        bool found = false;
        for(int i = 0; i < actionClient->Items->Count; i++)
        {
            TActionClientItem *subMenuItem = actionClient->Items->ActionClients[i];

            for(int j = 0; j < list->ActionCount; ++j)
            {
                if( subMenuItem->Action == list->Actions[j] )
                {
                    found = true;
                    subMenuItem->Free();
                    break;
                }
            }
        }
        if( !found )
            ++i;
    }
}


bool __fastcall dslActionMainMenuManager::SetupIconsToUseOnMainMenu()
{
//    //Action category is only set for actions that are to be placed on the menu.
//    for(int i = 0; i < FPluginManager->PluginCount; i++)
//    {
//        dslPluginBase* plugin = FPluginManager->Plugins[i];
//        switch (FMainMenuIconSize)
//        {
//
//            case SIZE_16x16:
//            {
//                plugin->GetAction16x16()->Category    = plugin->GetMainMenuCategory();     //This goes to the menu
//                plugin->GetAction24x24()->Category    = "Plugins";
//                plugin->GetAction32x32()->Category    = "Plugins";
//            }
//            break;
//            case SIZE_24x24:
//            {
//                    plugin->GetAction16x16()->Category    = "Plugins";
//                    plugin->GetAction24x24()->Category    = plugin->GetMainMenuCategory();
//                    plugin->GetAction32x32()->Category    = "Plugins";
//            }
//            break;
//            case SIZE_32x32:
//            {
//                    plugin->GetAction16x16()->Category    = "Plugins";
//                    plugin->GetAction24x24()->Category    = "Plugins";
//                    plugin->GetAction32x32()->Category    = plugin->GetMainMenuCategory();
//            }
//            break;
//            default:
//                return false;
//        }
//    }
    return true;
}

