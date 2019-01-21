//---------------------------------------------------------------------------
#ifndef dslActionManagerHelperH
#define dslActionManagerHelperH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <ActnMan.hpp>
#include <ActnMenus.hpp>
#include <vector>
#include "DuneComponents.h"
#include "dslPluginManager.h"
#include "dslPackageDefs.h"
using std::vector;
//using namespace dsl;

//---------------------------------------------------------------------------
class PACKAGE mtkActionManagerHelper : public TComponent
{
    private:
        TCustomAction*                                            FAction;
        String                                                FCaption;
        TActionProc                                                FCompareProc;
        TActionClientItem                                      *FFoundClient;
        void                         __fastcall                      CompareCaption(TActionClient* AClient);
        void                         __fastcall                      CompareAction(TActionClient* AClient);
        TActionClientItem*             __fastcall                     FindItem();

    protected:
        mtkPluginManager*                                         FPluginManager;
        TActionManager                                           *FActionManager;
        TCoolBar                                                *FCoolBar;            //!The coolbar any actionmenus and action toolbars are placed on

        virtual void                __fastcall                  FindClient(TActionClient* AClient);
        virtual TActionManager*     __fastcall                  GetActionManager(){return FActionManager;}
        virtual void                __fastcall                  SetActionManager(TActionManager* aManager){ FActionManager = aManager;}
        virtual TCoolBar*           __fastcall                  GetCoolBar(){return FCoolBar;}
        virtual void                __fastcall                  SetCoolBar(TCoolBar* coolBar){FCoolBar = coolBar;}

    public:
                                    __fastcall                  mtkActionManagerHelper(TComponent* Owner);
        TActionClientItem*          __fastcall                  AddAction(TCustomAction* anAction, TActionClient* anActionClient, bool after = true);

          TActionClientItem*          __fastcall                  InsertCategory(const String& category, TActionClient* anActionClient, bool after = true);
          TActionClientItem*          __fastcall                  InsertCategory(const String& category, TCollection* AClient, int index);
          TActionClientItem*          __fastcall                  AddSeperator(TActionClientItem* anActionClientItem, bool after = true);
        TActionClientItem*             __fastcall                  FindItemByCaption(const String& ACaption);
        TActionClientItem*             __fastcall                  FindItemByAction(TCustomAction* anAction);

        virtual mtkPluginManager*   __fastcall                  GetPluginManager(){return FPluginManager;}
        virtual void                __fastcall                  SetPluginManager(mtkPluginManager* pluginManager){FPluginManager = pluginManager;}

        //---------------- ActionMainMenuBar stuff
          TActionClientItem*          __fastcall                     AddCategory(const String& category, bool after = false);
          TActionClientItem*          __fastcall                  AddToCategory(const String& category);
        void                        __fastcall                  DeleteActionItems(TActionList* aList);

    __published:
        __property TActionManager*                                  ActionManager      = {read=GetActionManager,             write=SetActionManager};
        __property mtkPluginManager*                             PluginManager      = {read=GetPluginManager,             write=SetPluginManager};
        __property TCoolBar*                                     CoolBar                  = {read=GetCoolBar,                     write=SetCoolBar};
};
//---------------------------------------------------------------------------
int    __fastcall AddActions(vector<TContainedAction*> *Actions, TCustomActionList* ActionList, const String& aCategory);
#endif
