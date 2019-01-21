
#pragma hdrstop
#include <vcl.h>
#include <algorithm>
#include "dslLogger.h"
#include "dslIniFile.h"
#include "dslStringUtils.h"
#include "dslTabSheetBase.h"
#include "dslTabSheetPlugin.h"
#include "TPCFrame.h"
#include "TBasePlate.h"
#include "dslVCLUtils.h"
#include "dslPCManager.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//
using namespace dsl;
//---------------------------------------------------------------------------
__fastcall dslPCManager::dslPCManager(TComponent* Owner)
    : TComponent(Owner)
{
    if(mPCFrame)
    {
        mPCCategory = stdstr(mPCFrame->GetCategory());
    }
    SetPageControl(FPageControl);

}
//---------------------------------------------------------------------------
__fastcall dslPCManager::~dslPCManager()
{
}
//---------------------------------------------------------------------------

void __fastcall dslPCManager::SetPageControl(TPageControl* aPControl)
{
    FPageControl = aPControl;
    if(FPageControl)
        FPageControl->OnChange = OnTabChange;           //This causes the ontabchange to be called
                                                        //when the tab changes
}

void __fastcall dslPCManager::OnTabChange(TObject *Sender)
{

    Log(lDebug)<<"The Tab changed in PageControl Manager with category:"<<mPCFrame->GetCategory().c_str()<<std::endl;


    TBasePlate*    activePlate = GetActivePlate();
    if(activePlate)
    {
        dslTabSheetPlugin* plugin = activePlate->GetPlugin();

        if(plugin)
        {
            Log(lDebug)<<"The plugin on the current page is: "<<plugin->GetPluginName();
            plugin->OnActivate();
        }
    }
    //Send a message to tell other PC managers that a tab changed on a PageControl
       char msg_buf[256];
    stringstream msg;
    msg<<mPCFrame->GetCategory().c_str();
    strcpy(msg_buf, msg.str().c_str());

       HWND hWnd = Application->MainForm->Handle;
    WPARAM wParam = (WPARAM) (HWND) hWnd;            // handle of sending window
    LPARAM lParam = (LPARAM) msg_buf;             // pointer to data

    LRESULT res = SendMessage(hWnd, UWM_PAGE_CONTROL_CHANGED, wParam, lParam);
    if(res)
    {
        Log(lDebug)<<"Sending set filter message was unsuccesful";
        return;
    }

//    AttachToSubjects();
}

void __fastcall dslPCManager::AttachToSubject(const string& subjectCategory, const string& subjectName)
{
    //Get plugins that attaches to subject category
    list<dslTabSheetPlugin*> observers;
    for(int i = 0; i < PluginManager->PluginCount; i++)
    {
        dslTabSheetPlugin *plugin = dynamic_cast<dslTabSheetPlugin *> (PluginManager->Plugins[i]);
        if(plugin)
        {
            string needSubjectCategory = plugin->GetSubjectCategory();
            if(subjectCategory == needSubjectCategory)
            {
                observers.push_back(plugin);
            }
        }
    }

    list<dslTabSheetPlugin*> subjects;
    for(int i = 0; i < PluginManager->PluginCount; i++)
    {
        dslTabSheetPlugin *plugin = dynamic_cast<dslTabSheetPlugin *> (PluginManager->Plugins[i]);
        if(plugin)
        {
            string ofSubjectCategory = plugin->GetGUICategory();
            if(ofSubjectCategory == subjectCategory)
            {
                if(plugin->GetPluginName() == subjectName)
                    subjects.push_back(plugin);
            }
        }
    }

    //What are the observers going to observe?
    //Find subjects..
    dslTabSheetPlugin *anObserver = nullptr;
    dslTabSheetPlugin *aSubject = nullptr;
    list<dslTabSheetPlugin*>::iterator observerIter;

    if(subjects.size())
    {
        aSubject = (*subjects.begin());
    }

    for(observerIter = observers.begin(); observerIter !=  observers.end(); ++observerIter)
    {
        anObserver = (*observerIter);

        if(anObserver->ObservesSubjectsWithName() == subjectName)
        {
            string name = aSubject->GetMenuText();
            anObserver->AttachToSubject(aSubject);
        }
        else
        {
            anObserver->DetachFromSubject(nullptr);
        }
    }


//    dslTabSheetPlugin* activePlugin = GetActivePlugin();
//
//    //Attach subjects to observers on this PageControl
//  //
//    for(int i = 0; i < PluginManager->PluginCount; i++)
//    {
//        dslTabSheetPlugin *tabPlugin = dynamic_cast<dslTabSheetPlugin *> (PluginManager->Plugins[i]);
//        if(tabPlugin)
//        {
//            //Is this plugin of the right category?
//            string subjectOfCategory = tabPlugin->GetGUICategory();
//            string needSubjectCategory = activePlugin->GetSubjectCategory();
//
//            if(subjectOfCategory == needSubjectCategory)    //When a match is found, associate..
//            {
//                activePlugin->AttachToSubject(tabPlugin);
//            }
//        }
//    }
}

void __fastcall dslPCManager::DetachObservers()
{
    dslTabSheetPlugin* activePlugin = GetActivePlugin();

    //Attach observer plugins to the active tab (plate)
    for(int i = 0; i < PluginManager->PluginCount; i++)
    {
        dslPluginBase *plugin = PluginManager->Plugins[i];
        if(plugin)
        {
            //cast to tabsheet plugin
            dslTabSheetPlugin* tPlugin = dynamic_cast<dslTabSheetPlugin*> (plugin);
            if(tPlugin && tPlugin->NeedsASubject())
            {
                string category = stdstr(mPCFrame->GetCategory());
                string needSubjectCategory = tPlugin->GetSubjectCategory();
                if(category == needSubjectCategory)
                {
                    tPlugin->DetachFromSubject(activePlugin);
                }
            }
        }
    }
}

dslTabSheetPlugin* __fastcall dslPCManager::GetActivePlugin()
{
    TBasePlate*    activePlate = GetActivePlate();
    if(activePlate)
    {
        return activePlate->GetPlugin();
    }
    return nullptr;
}

TBasePlate* __fastcall dslPCManager::GetActivePlate()
{
    if(!FPageControl)
        return nullptr;

    TTabSheet* aSheet = FPageControl->ActivePage;
    TBasePlate*    activePlate = nullptr;

    if(aSheet)
        activePlate = GetPlateWithParent(aSheet);
    return activePlate;
}

TTabSheet* __fastcall dslPCManager::CreateSheet()
{
    if(!FPageControl)
    {
        Log(lDebug)<<"No PageControl in PC manager::CreateSheet";
        return nullptr;
    }

    TTabSheet* sheet = new TTabSheet(FPageControl);

    if(sheet)
    {
            sheet->PageControl = FPageControl;
    }

    return sheet;
}

bool __fastcall dslPCManager::DeleteSheet(TTabSheet* sheet)
{
    delete sheet;
    return true;
}

bool __fastcall dslPCManager::LoadHistory()
{
    //The tab history is read from ini file
    int activatePageWithIndex = -1;
    if(!FIniFile)
    {
                                Log(lError)<<"Can't restore tabbed pages: No INI file assigned";
        return false;
    }
    FIniFile->Load();

    if(FIniFile->SectionCount() > 0)
    {
                                                    Log(lDebug)<<"Restoring tabbed pages";
        //Each section corresponds to one tab
        int  pageNr = 0;
        for (int i = 0; i < FIniFile->SectionCount(); i++)
        {
            dslIniSection *section = FIniFile->GetSection(i);
            if(section)
            {
                dslIniKey *key1 = FIniFile->GetKey("PluginName",             section->mName);
                dslIniKey *key2 = FIniFile->GetKey("PageControlFrame",     section->mName);
                dslIniKey *key3 = FIniFile->GetKey("TabActive",             section->mName);
                dslIniKey *key4 = FIniFile->GetKey("FileName",             section->mName);
                string pluginName = key1->mValue;
                                                    Log(lDebug)<<"Creating a " + pluginName + " plugin";
                //Check if the plugin is loaded, otherwise try to load it
                if(FPluginManager)
                {
                    dslPluginBase* thePlugin = FPluginManager->GetPlugin(key1->mValue.c_str());
                    //If we found the plugin, and the plugin is to be shown on this pagecontrol, execute..
                    wstring temp = GetPCFrame()->Name.c_str();
                    string frameName(temp.begin(), temp.end());
                    if(thePlugin && key2->mValue == frameName)
                    {
                        if(key4 != nullptr && key4->mValue.length())
                        {
                            thePlugin->OpenFile(key4->mValue, Application);
                        }
                        else
                        {
                            thePlugin->Execute(Application);    //Executes the plugin
                        }
                        //AttachToSubject();

                        if(!strcmp(key3->mValue.c_str(),"true"))
                        {
                                Log(lDebug)<<"The plugin: " + pluginName + " should be made active";
                                activatePageWithIndex = pageNr;
                        }
                        pageNr++;
                    }
                }
                else
                {
                    Log(lDebug)<<"No plugin manager assigned to PageControl manager. Can't load plugin: " + pluginName;
                }
            }
        }
    }
    ActivatePageWithIndex(activatePageWithIndex);
    return true;
}

bool __fastcall dslPCManager::ActivatePageWithIndex(int theIndex)
{
    if(theIndex > -1 && theIndex < FPageControl->PageCount)
        FPageControl->ActivePageIndex = theIndex;

    int index = FPageControl->TabIndex;
    if(index != FPageControl->ActivePageIndex)
    {
        Log(lDebug)<<"Weird";
    }
    FPageControl->OnChange(nullptr);
    return true;
}

//bool __fastcall dslPCManager::ActivatePageWithIndex(int theIndex)
//{
//    if
//}

bool __fastcall dslPCManager::ActivateCurrentPage()
{
//    TTabSheet *aSheet = FPageControl->ActivePage;
    FPageControl->OnChange(nullptr);
    return true;
}

bool __fastcall dslPCManager::ActivatePage(TBasePlate* plate)
{
    int theIndex = GetPageIndexForPlate(plate);
    if(theIndex > -1 && theIndex < FPageControl->PageCount)
        FPageControl->ActivePageIndex = theIndex;

    ShowPage(plate);
    int index = FPageControl->TabIndex;
    if(index != FPageControl->ActivePageIndex)
    {
        Log(lDebug)<<"Weird2";
    }

    FPageControl->OnChange(nullptr);
    return true;

}

int    __fastcall dslPCManager::GetPageIndexForSheet(TTabSheet* aSheet)
{
    int pIndex = -1;
    for(int i = 0; i < FPageControl->PageCount; i++)
    {
        if(aSheet ==  (TTabSheet*)FPageControl->Pages[i])
        {
            pIndex = i;
            break;
        }
    }
    return pIndex;
}

int    __fastcall dslPCManager::GetPageIndexForPlate(TBasePlate* plate)
{
    TTabSheet* aSheet = GetTabSheetWithPlate(plate);
    return (aSheet) ? GetPageIndexForSheet(aSheet) : -1;
}

bool __fastcall dslPCManager::SaveHistory()
{
    if(!FIniFile)
    {
                Log(lDebug)<<"Can't save tabs, ini file not assigned";
        return false;
    }
    //Save any pages to history before closing them
                            Log(lDebug)<<"Saving tabbed pages..";

    //save the open tab sheets to inifile and open on application startup
    FIniFile->DeleteSectionsWithKeyValue("PageControlFrame", stdstr(GetPCFrame()->Name));

    if(FPageControl->PageCount)
    {
        int activePageIndex = FPageControl->ActivePageIndex;
        mPlateIterator = mPlates.begin();
        int i = 0;
        while(mPlateIterator != mPlates.end())
        {
            TBasePlate* aPlate = *mPlateIterator;
            if(!aPlate)
                break;
            TTabSheet* tabSheet = GetTabSheetWithPlate(aPlate);
            if(!tabSheet)
                break;
            int tabIndex = tabSheet->TabIndex;
            bool isActive = (activePageIndex == tabIndex) ? true : false;
            string section = "Plugin " + toString(++i) + ":" + stdstr(GetPCFrame()->Name);
            FIniFile->CreateSection(section, "");
            FIniFile->CreateKey("PluginName",         aPlate->GetPlugin()->GetPluginName(), "", section);
            FIniFile->CreateKey("PageControlFrame", stdstr(GetPCFrame()->Name), "", section);
            FIniFile->CreateKey("TabActive",         dsl::toString(isActive), "", section);
            FIniFile->CreateKey("FileName",         aPlate->GetCurrentFileName().c_str(), "", section);
            mPlateIterator++;
        }
    }
    return FIniFile->Save();
}

bool __fastcall dslPCManager::AddPlate(TBasePlate* plate)
{
    //Add the plugin to list of plugins
    if(plate)
    {
        mPlates.push_back(plate);
    }
    FPageControl->OnChange(nullptr);
    return true;
}

bool __fastcall dslPCManager::RemovePlate(TBasePlate* plate)
{
    mPlates.remove(plate);
    FPageControl->OnChange(nullptr);
    return true;
}

bool __fastcall dslPCManager::HidePage(TBasePlate* plate)
{
    //We are hiding the tab sheet, not the plate itself
    TTabSheet* aSheet = GetTabSheetWithPlate(plate);
    HidePage(aSheet);

    return true;
}

bool __fastcall dslPCManager::HidePage(TTabSheet* aSheet)
{
    if(aSheet)
        aSheet->TabVisible = false;

    return true;
}

bool __fastcall dslPCManager::ShowPage(TBasePlate* plate)
{
    TTabSheet* aSheet = GetTabSheetWithPlate(plate);
    ShowPage(aSheet);
    return true;
}

bool __fastcall dslPCManager::ShowPage(TTabSheet* aSheet)
{
    if(aSheet)
        aSheet->TabVisible = true;

    return true;        
}


bool __fastcall dslPCManager::ClosePlate(TBasePlate* basePlate)
{
    dslTabSheetPlugin* plugin = dynamic_cast<dslTabSheetPlugin*> (basePlate->GetPlugin());

    if(!plugin)
    {
        return false;
    }
    else
    {
        DetachObservers();
        Log(lDebug)<<"The plate "<<basePlate->GetCurrentFileName()<<" is closing";
        TTabSheet* sheet = GetTabSheetWithPlate(basePlate);
        plugin->ClosePlate(basePlate);
        DeleteSheet(sheet);

        mPlates.remove(basePlate);
        return true;
    }
}

dslTabSheetPlugin* __fastcall dslPCManager::GetPluginForTabSheetBase(TTabSheetBase* baseSheet)
{
    return dynamic_cast<dslTabSheetPlugin*> (baseSheet->GetPlugin());
}

TBasePlate* __fastcall dslPCManager::GetPlateWithParent(TTabSheet* tabSheet)
{
    //Cycle trough the plugins sheets to find this sheet
    if(tabSheet)
    {
        mPlateIterator = mPlates.begin();
        while(mPlateIterator != mPlates.end())
        {
            TBasePlate* plate = *(mPlateIterator);
            if(plate)
            {
                if (plate->Parent == tabSheet)
                {
                    return plate;
                }
            }
            mPlateIterator++;
        }
    }
    return nullptr;
}

TTabSheet* __fastcall dslPCManager::GetTabSheetWithPlate(TBasePlate* plate)
{
    if(!plate)
        return nullptr;

    //The owner of each base plate is a tabshhet
    TTabSheet* sheet = dynamic_cast<TTabSheet*> (plate->GetTheOwner());
    if(!sheet)
        return nullptr;

    //Go trough the PageControl and find this sheet
    for(int i = 0; i < FPageControl->PageCount; i++)
    {
        TTabSheet* aSheet = FPageControl->Pages[i];
        if(aSheet == sheet)
            return sheet;
    }
    return nullptr;
}

static inline void ValidCtrCheck(dslPCManager *)
{
    new dslPCManager(nullptr);
}

namespace Mtkpcmanager
{
    void __fastcall PACKAGE Register()
    {
        TComponentClass classes[1] = {__classid(dslPCManager)};
        RegisterComponents(dslComponents::gDuneComponents, classes, 0);
    }
}
//---------------------------------------------------------------------------

