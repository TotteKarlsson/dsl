#ifndef dslActionMainMenuManagerH
#define dslActionMainMenuManagerH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Classes.hpp>
#include "DuneComponents.h"
#include "dslActionManagerHelper.h"
//---------------------------------------------------------------------------
class PACKAGE mtkActionMainMenuManager : public mtkActionManagerHelper
{
private:
        TActionMainMenuBar*            FActionMainMenuBar;
         IconSize                 FMainMenuIconSize;

protected:
        virtual TActionMainMenuBar* __fastcall GetActionMainMenuBar(){return FActionMainMenuBar;}
        virtual void                __fastcall SetActionMainMenuBar(TActionMainMenuBar* aMenu){FActionMainMenuBar = aMenu;}
        TActionClientItem*             __fastcall AddMenuCategory(String& category, TActionClient* anActionClient, bool after = true);

public:
                                    __fastcall mtkActionMainMenuManager(TComponent* Owner);
        bool                        __fastcall PopulateMainMenusWithPluginActions();
        bool                        __fastcall AddActions();
        void                         __fastcall RemoveActionsFromActionMainMenuBar(TCustomActionList* list);
        TActionClientItem*             __fastcall GetFirstItemOnMainMenu();
        TActionClientItem*             __fastcall GetLastItemOnMainMenu();
        TActionClientItem*             __fastcall FindItemByCaption(const String& ACaption, TActionMainMenuBar *actionMainMenuBar);
        TActionClientItem*             __fastcall FindTopMenuItemByCaption(const String& ACaption, TActionMainMenuBar *actionMainMenuBar);
        virtual void                __fastcall SetMainMenuIconSize(IconSize _size){FMainMenuIconSize = _size;}
        bool                         __fastcall SetupIconsToUseOnMainMenu();
        bool                         __fastcall HideCategory(const String& category);

__published:
        __property TActionMainMenuBar*     ActionMainMenuBar  = {read=GetActionMainMenuBar,        write=SetActionMainMenuBar};
        __property IconSize          MainMenuIconSize   = {read=FMainMenuIconSize,            write=SetMainMenuIconSize, default=SIZE_16x16};
};
//---------------------------------------------------------------------------
#endif
