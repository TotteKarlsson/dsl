#ifndef dslActionToolBarManagerH
#define dslActionToolBarManagerH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Classes.hpp>
#include "DuneComponents.h"
#include "dslActionManagerHelper.h"
//---------------------------------------------------------------------------
class PACKAGE mtkActionToolBarManager : public mtkActionManagerHelper
{
    private:
        int                         __fastcall GetPluginToolBarCategories(vector<string>& cats);
        void                         __fastcall UpdateToolBarSize(TActionToolBar *actionToolBar);        

    protected:
        TActionToolBar                *FActionToolBar;
         IconSize                  FToolBarIconSize;
        virtual TActionToolBar*     __fastcall GetActionToolBar(){return FActionToolBar;}
        virtual void                __fastcall SetActionToolBar(TActionToolBar* aActionToolBar){ FActionToolBar = aActionToolBar;}
        virtual void                __fastcall SetToolBarIconSize(IconSize _size){FToolBarIconSize = _size;}
        bool                         __fastcall SetupIconsToUseOnToolBars();
        void                         __fastcall AddActionsToActionToolBar(TCustomActionList* list, TActionBarItem* actionBarItem, const String& category);
        void                         __fastcall AddActionsToActionToolBar(vector<TContainedAction*> *Actions, TActionBarItem* actionBarItem);

    public:
                                    __fastcall mtkActionToolBarManager(TComponent* Owner);
           bool                        __fastcall PopulateToolBars();
        void                         __fastcall RemoveActionsFromActionToolBar(TCustomActionList* list, TActionToolBar *actionToolBar);
    __published:
        __property TActionToolBar*         ActionToolBar        = {read=GetActionToolBar,          write=SetActionToolBar};
        __property IconSize            IconSize             = {read=FToolBarIconSize,          write=SetToolBarIconSize, default=SIZE_16x16};
};
//---------------------------------------------------------------------------
#endif
