
#pragma hdrstop
#include <vcl.h>
#include "dslTabSheetBase.h"
#include "TPCFrame.h"
#include "dslPageControlManager.h"
#include "dslTabSheetPlugin.h"
#include "DiscoverMessages.h"
#include "dslLogger.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslPCManager"
#pragma resource "*.dfm"
TPCFrame *PCFrame;

int TPCFrame::mFrameNr = 0;
//---------------------------------------------------------------------------
__fastcall TPCFrame::TPCFrame(TComponent* Owner)
:
TFrame(Owner)
{
    mFrameNr++;
    Name = "PCFrame_" + Sysutils::IntToStr(mFrameNr);
    mApplicationInfo = new dslApplicationInfo(Application);
    Setup();
}

__fastcall TPCFrame::~TPCFrame(){}

void __fastcall TPCFrame::Setup()
{
    if(PCManager)
    {
        PCManager->SetIniFile(FIniFile);
        PCManager->SetPCFrame(this);
        PCManager->SetPluginManager(FPluginManager);
    }
}

void __fastcall TPCFrame::SetIniFile(dslIniFileC* aIniFileC)
{
    FIniFile = aIniFileC;
    if(PCManager)
    {
        PCManager->SetIniFile(FIniFile);
    }
}

void __fastcall TPCFrame::Close()
{
    PCManager->SetAppIsClosing(true);
    CloseAllPagesAExecute(nullptr);
}

void __fastcall TPCFrame::AssociatePlugins(dslPluginManager* manager)
{
    int nrOfPlugins = manager->GetNumberOfPlugins();

    for(int i = 0; i < nrOfPlugins; i++)
    {
        dslTabSheetPlugin* plugin = dynamic_cast<dslTabSheetPlugin*> (manager->Plugins[i]);
        if(plugin)
        {
            string Category = stdstr(GetCategory());
            //Associate only plugins with matching categories
            if(plugin->InGUICategory(Category.c_str()))
            {
                plugin->SetPageControl(PageControl);
                plugin->SetTabSheetManager(PCManager);
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TPCFrame::CreatePageAExecute(TObject *Sender)
{
    TTabSheet* sheet = new TTabSheet(PageControl);
    sheet->Parent = PageControl;
    sheet->PageControl = PageControl;
    sheet->Caption ="New tab";
    sheet->Visible = true;

}
//---------------------------------------------------------------------------
void __fastcall TPCFrame::Restore()
{
    if(PCManager)
    {
        PCManager->LoadHistory();
    }
}
//---------------------------------------------------------------------------
TBasePlate* __fastcall TPCFrame::GetContent(TTabSheet* sheet)
{
    //Find which page is on this sheet
    TBasePlate* base = PCManager->GetPlateWithParent(sheet);
    return (base != nullptr) ? base : nullptr;
}
//---------------------------------------------------------------------------
int __fastcall TPCFrame::GetCurrentPageTabIndex()
{
    return PageControl->ActivePageIndex;
}

void __fastcall TPCFrame::HidePageAExecute(TObject *Sender)
{
    TTabSheet* sheet = PageControl->ActivePage;

    if(sheet)
    {
        PCManager->HidePage(sheet);
    }
}

//---------------------------------------------------------------------------
void __fastcall TPCFrame::ClosePageAExecute(TObject *Sender)
{
    //Get the page on the current tabsheet
    TTabSheet* sheet = PageControl->ActivePage;
    int index    = PageControl->ActivePageIndex;

    if(!sheet)
    {
        return;
    }

    //Check for a plate
    TBasePlate* plate = GetContent(sheet);
    if(plate)
    {
           Log(lDebug)<<"The sheet "<<sheet->Caption.c_str()<<" is to be closed";
        if(!PCManager->ClosePlate(plate))
        {
               Log(lDebug)<<"The sheet could not be closed";
        }
    }
    else
    {
        //Just delete the sheet
        sheet->Parent = nullptr;
        delete sheet;
    }

    //Activate the page closest "below" this page
    PCManager->ActivatePageWithIndex(index-1);
}

//---------------------------------------------------------------------------
void __fastcall TPCFrame::CloseAllPagesAExecute(TObject *Sender)
{
    while(PageControl->ActivePageIndex != -1)
    {
        ClosePageAExecute(Sender);
    }
}

void __fastcall TPCFrame::ActivateTabAExecute(TObject *Sender)
{
    if(PCManager)
        PCManager->ActivateCurrentPage();
}

//---------------------------------------------------------------------------
void __fastcall TPCFrame::CloseAllTabsExceptThisAExecute(TObject *Sender)
{
    //This index wil change as other pages are deleted
    TTabSheet* thisSheet = GetCurrentTabSheet();

    for(int i = PageControl->PageCount - 1; i >= 0 ; --i)
    {
        TTabSheet* aSheet = PageControl->Pages[i];
        if(aSheet != thisSheet)
        {
            TBasePlate* plate = PCManager->GetPlateWithParent(aSheet);
            if(plate)
                PCManager->ClosePlate(plate);    //Does delete the sheet
        }
    }
    //To restore any subject observer relationships..
    ActivateTabAExecute(Sender);
}
//---------------------------------------------------------------------------
TTabSheet* __fastcall TPCFrame::GetCurrentTabSheet()
{
    return (GetCurrentPageTabIndex() != -1) ?
        PageControl->Pages[PageControl->ActivePageIndex] : nullptr;
}
void __fastcall TPCFrame::PageControlChanging(TObject *Sender,
      bool &AllowChange)
{
    Log(lDebug)<<"The page control with category name: "<<FCategory.c_str()<<" is about to change"<<std::endl;
}
//---------------------------------------------------------------------------


void __fastcall TPCFrame::PageControlChange(TObject *Sender)
{
       HWND hWnd = Application->MainForm->Handle;

    char fileFilter[256];
    stringstream filterStr;
    filterStr<<"tab changed\n";
    strcpy(fileFilter, filterStr.str().c_str());

    WPARAM wParam = (WPARAM) (HWND) hWnd;            // handle of sending window
    LPARAM lParam = (LPARAM) fileFilter;             // pointer to data

    LRESULT res = SendMessage(hWnd, UWM_PAGE_CONTROL_CHANGED, wParam, lParam);
    if(res)
    {
         Log(lDebug)<<"Sending tab changed message was unsuccesful";
    }

    Log(lDebug)<<"The page control changed";
}

//---------------------------------------------------------------------------
static inline void ValidCtrCheck(TPCFrame *)
{
    new TPCFrame(nullptr);
}

namespace Tpcframe
{
    void __fastcall PACKAGE Register()
    {
//        ShowMessage("Registered TPCFrame");
        TComponentClass classes[1] = {__classid(TPCFrame)};
        RegisterComponents(dslComponents::gDuneComponents, classes, 0);
    }
}


