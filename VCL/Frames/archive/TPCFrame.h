//---------------------------------------------------------------------------

#ifndef TPCFrameH
#define TPCFrameH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include "dslApplicationInfo.h"
#include "dslPCManager.h"
#include "dslPluginManager.h"
#include "DuneComponents.h"
using std::list;
class TTabSheetBase;
class mtkPageControlManager;
class mtkPluginManager;
//---------------------------------------------------------------------------
class PACKAGE TPCFrame : public TFrame
{
    __published:
        TPageControl                            *PageControl;
        TActionList                            *PageActions;
        TAction                                *CreatePageA;
        TPopupMenu                                *PageControlPopup;
        TAction                                *ClosePageA;
        TAction                                *CloseAllPagesA;
        TMenuItem                                *ClosePage1;
        TMenuItem                                *CloseAll1;
        mtkPCManager                            *PCManager;
        TAction                                *CloseAllTabsExceptThisA;
        TMenuItem                                *CloseAllOtherTabs1;
        TAction                                *ActivateTabA;
        TMenuItem                                *Activate1;
        TAction                                *HidePageA;
        TMenuItem                                *N1;
        TMenuItem                                *Hide1;
        void                         __fastcall    CreatePageAExecute(TObject *Sender);
        void                        __fastcall  ClosePageAExecute(TObject *Sender);
        void                        __fastcall  CloseAllPagesAExecute(TObject *Sender);
        void                        __fastcall  CloseAllTabsExceptThisAExecute(TObject *Sender);
        void                        __fastcall  PageControlChanging(TObject *Sender, bool &AllowChange);
        void                        __fastcall  PageControlChange(TObject *Sender);
        void                        __fastcall  ActivateTabAExecute(TObject *Sender);
        void                        __fastcall  HidePageAExecute(TObject *Sender);

    private:    // User declarations
        static int                                   mFrameNr;
        mtkPluginManager*                          FPluginManager;
        mtkIniFileC*                            FIniFile;
        String                                     FHistoryFileName;
        int                                     FTestInt;
        String                                    FCategory;
        mtkApplicationInfo*                          mApplicationInfo;
        list<mtkPluginManager*>                 mPluginManagers;

    protected:
        virtual mtkPluginManager*    __fastcall    GetPluginManager(){return FPluginManager;}
        virtual void                __fastcall  SetPluginManager(mtkPluginManager* aManager){ FPluginManager = aManager;}
        String                        __fastcall  GetHistoryFileName(){return FHistoryFileName;}
        void                        __fastcall  SetHistoryFileName(String fName){FHistoryFileName = fName;}
        int                         __fastcall  GetTestInt(){return FTestInt;}
        void                        __fastcall  SetTestInt(const int aInt){FTestInt = aInt;}
        virtual mtkIniFileC*         __fastcall  GetIniFile(){return FIniFile;}
        virtual void                __fastcall  SetIniFile(mtkIniFileC* aIniFileC);
        int                         __fastcall  GetCurrentPageTabIndex();
        TTabSheet*                    __fastcall  GetCurrentTabSheet();
        TBasePlate*                 __fastcall  GetContent(TTabSheet* sheet);
//        void                         __fastcall  SetCategory(int Index, String value);
        void                         __fastcall  SetCategory(String value){FCategory = value;}

    public:
                                    __fastcall  TPCFrame(TComponent* Owner);
                                    __fastcall  ~TPCFrame();
        void                         __fastcall  Setup();
        mtkPCManager*                 __fastcall  GetTabManager(){return PCManager;}
        void                         __fastcall  Close();
        void                         __fastcall  AssociatePlugins(mtkPluginManager* manager);
        void                         __fastcall  Restore();
        String                        __fastcall  GetName(){return Name;}
//        void                        __fastcall  AddCategory(const String& cat){SetCategory(-1, cat);}
        bool                        __fastcall  SaveHistory(){return PCManager->SaveHistory();}
        String                         __fastcall  GetCategory(){return FCategory;}

    __published:
        __property mtkPluginManager*     PluginManager     = {read=GetPluginManager,              write=SetPluginManager};
        __property mtkIniFileC*         IniFile             = {read=GetIniFile,                      write=SetIniFile, stored=true};
           __property String                 Category         = {read=FCategory,                     write=SetCategory};
};
//---------------------------------------------------------------------------
//extern PACKAGE TPCFrame *PCFrame;
//---------------------------------------------------------------------------
#endif
