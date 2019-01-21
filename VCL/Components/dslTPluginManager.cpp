#pragma hdrstop
#include <Registry.hpp>
#include <algorithm>
#include "dslTPluginManager.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
using namespace dsl;
using namespace std;

//---------------------------------------------------------------------------
__fastcall TPluginManager::TPluginManager(TComponent* Owner)
:
TComponent(Owner),
FApplication(Application)
{}

__fastcall TPluginManager::~TPluginManager()
{

}

void TPluginManager::setup()
{
    mMainMenuActionList    = new TActionList(this);
    mToolBarActionList     = new TActionList(this);

    mMainMenuIcons         = new TCustomImageList(this);
    mToolBarIcons          = new TCustomImageList(this);

    //The size of icons to use is decided upon runtime..
    mMainMenuActionList->Images = mMainMenuIcons;
    mToolBarActionList->Images  = mToolBarIcons;
}

Plugin* TPluginManager::getPlugin(int index)
{
	return mPM.getPlugin(index);
}

int  TPluginManager::getPluginCount()
{
    return mPM.getNumberOfPlugins();
}

int  TPluginManager::loadPlugins()
{
    return mPM.loadPlugins();
}

bool  TPluginManager::addMainMenuCategory(const string& category)
{
    if(find(mMainMenuCategories.begin(), mMainMenuCategories.end(), category) == mMainMenuCategories.end())
    {
        mMainMenuCategories.append(category);
        return true;
    }
    return false;
}

string  TPluginManager::getMainMenuCategory(int index)
{
    if(index > -1 || index < mMainMenuCategories.size())
    {
        return mMainMenuCategories[index];
    }
    else
        return "";
}

void  TPluginManager::setIconListSize(IconSize iconSize, TCustomImageList* iconList)
{
    if(!iconList)
    {
        return;
    }
    switch(iconSize)
    {
        case SIZE_16x16: iconList->Width     = 16; iconList->Height     = 16; break;
        case SIZE_24x24: iconList->Width     = 24; iconList->Height     = 24; break;
        case SIZE_32x32: iconList->Width     = 32; iconList->Height     = 32; break;
        default: iconList->Width     = 16; iconList->Height     = 16;
    }
}

void  TPluginManager::setupMainMenuActionList(IconSize iconSize)
{
//    SetIconListSize(iconSize, mMainMenuIcons);
//
//    for(int i = 0; i < FPlugins->Count; i++)
//    {
//        Plugin* plugin = Plugins[i];
//        if(plugin && plugin->PlaceOnMenu())
//        {
//            TAction* action     = plugin->GetPluginAction(iconSize);
//            if(action)
//            {
//                action->ActionList    = mMainMenuActionList;
//            }
//
//            TIcon* icon     = plugin->GetPluginIcon(iconSize);
//            if(icon)
//            {
//                action->ImageIndex =  mMainMenuIcons->AddIcon(icon);    //Add the icon to the image list, capture imageindex
//            }
//        }
//    }
}

void  TPluginManager::setupToolBarActionList(IconSize iconSize)
{
//    SetIconListSize(iconSize, mToolBarIcons);
//
//    for(int i = 0; i < FPlugins->Count; i++)
//    {
//        Plugin* plugin = Plugins[i];
//        if(plugin && plugin->PlaceOnToolBar())
//        {
//            TAction* action     = plugin->GetPluginAction(iconSize);
//            if(action)
//            {
//                action->ActionList    = mToolBarActionList;
//            }
//
//            TIcon* icon     = plugin->GetPluginIcon(iconSize);
//            if(icon)
//            {
//                action->ImageIndex =  mToolBarIcons->AddIcon(icon);    //Add the icon to the image list, capture imageindex
//            }
//        }
//    }
}

string TPluginManager::getPluginPath()
{
    string pFolder(stdstr(getPluginFolder()));
    string folder;
    folder = stdstr(ExtractFilePath(FApplication->ExeName)) + pFolder;
    return folder;
}

bool  TPluginManager::checkPluginDirectory()
{
    string folder = getPluginPath();
    if(!DirectoryExists(folder.c_str()))
    {
        stringstream msg;
        msg << "The folder for " << Name << " plugins don't exist.\n";
        msg << "The path for this folder needs to be : ";
        msg << folder;
        msg << "\nThis folder typically stores plugins as DLL files.";
        return false;
    }
    return true;
}

void  TPluginManager::unLoadPluginGroups()
{
//    WriteSettingsToRegistry();
    unLoadAllPlugins();
}

//---------------------------------------------------------------------------
void __fastcall TPluginManager::setPluginExtension(String  value)
{
    if(FPluginExtension != value)
    {
        if((value.Length()> 0) && (value.Length() <= 3))
        {
            FPluginExtension = value;
        }
        else
        {
            ShowMessage("Error! FileExtension needs to be 1 to 3 characters");
            return;
        }
    }
}
//----------------------------------------------------------------------------
bool  TPluginManager::unLoadPlugin(const string&  plugin)
{
    //Find at which index the plugin is
//    string fName;
//    string path = stdstr(FPluginFolder) + "\\";
//    for(int i = 0; i < FPlugins->Count; i++)
//    {
//        fName = path + ((Plugin*) FPlugins->Items[i])->getLibraryName();
//        if(fName == plugin)
//        {
//            unLoadPlugin(i);
//            return true;
//        }
//    }
    return false;
}

StringList TPluginManager::getLoadedPluginsNames()
{
    return mPM.getPluginNames();
}

StringList  TPluginManager::getLoadedPluginLibsFileNames()
{
//    PluginList->Clear();
//    for (int i = 0; i <= (FPlugins->Count - 1); i++)
//    {
//        PluginList->Add(((Plugin*)FPlugins->Items[i])->getLibraryName().c_str());
//    }
    return StringList();
}


string  TPluginManager::getLastLoadedPluginName()
{
//    return (FPlugins->Count) ?
//    string (((Plugin*) FPlugins->Items[FPlugins->Count - 1])->getName())
//    : string("");

}
//---------------------------------------------------------------------------
Plugin*  TPluginManager::getPlugin(const string&  pluginName)
{
//    //Go trough list to find name
//    for(int i = 0; i < FPlugins->Count; i++)
//    {
//        string str = ((Plugin*)FPlugins->Items[i])->getName();
//        if(str == pluginName)
//        {
//            return ((Plugin*)FPlugins->Items[i]);
//        }
//    }
    return nullptr;
}
//----------------------------------------------------------------------------
void  TPluginManager::fireStartLoadEvent(String  FileName, bool &CanLoad)
{
    CanLoad = true;
    if(FOnStartLoadEvent)
    {
        FOnStartLoadEvent(this,FileName,CanLoad);
    }
}
//----------------------------------------------------------------------------
void  TPluginManager::fireFinishedLoadEvent(String  PluginName, HICON PluginGlyph)
{
    if(FOnFinishedLoadEvent)
    {
        FOnFinishedLoadEvent(this, PluginName, PluginGlyph);
    }
}
//----------------------------------------------------------------------------
Plugin*  TPluginManager::loadPlugin(const string& FileName)
{
    if(FileName.size() < 1)
    {
        return nullptr;
    }

    Plugin* plugin = nullptr;
    if(this->FPluginExtension == "dll")
    {
        HINSTANCE dllInstance;
//        plugin = loadDLLPlugin(FileName, dllInstance);
        if(!plugin)
        {
            return nullptr;
        }
//        plugin->setPluginType(Plugin::DLL);
//        plugin->saveDLLInstance(dllInstance);
    }

//    else if(this->FPluginExtension == "bpl")
//    {
//        Windows::HINST package;
//        plugin = loadBPLPlugin(FileName, package);
//        if(!plugin)
//        {
//            return nullptr;
//        }
//        plugin->setPluginType(Plugin::BPL);
//        plugin->saveBPLInstance(package);
//    }
    else
    {
            MessageDlg("Please enter a valid extension for the plugins to be loaded", mtWarning, TMsgDlgButtons() << mbOK, 0);
        return nullptr;
    }

//    FPlugins->Add(plugin);
//    FireFinishedLoadEvent(plugin->getName(), (HICON__*) plugin->GetPluginGlyph());
//    fireFinishedLoadEvent(plugin->getName(), (HICON) plugin->getPluginGlyph());
    return plugin;
}


//Plugin*  TPluginManager::loadDLLPlugin(const string& FileName, HINSTANCE& dllInstance)
//{
//    dllInstance = ::LoadLibraryA(stdstr(FileName).c_str());
//    if(!dllInstance)
//    {
//        Log(lError)<<"Couldn't not load the Plugin: " <<FileName.c_str();
//        return nullptr;
//    }
//    DLLPROCADDRESS RegisterPluginAddress = (DLLPROCADDRESS) ::GetProcAddress(dllInstance, "_RegisterPlugin");
//
//    if (!RegisterPluginAddress)
//    {
//        ::FreeLibrary(dllInstance);
//        Log(lDebug)<<"Couldn't find RegisterPlugin function in plugin";
//        return nullptr;
//    }
//    Plugin* tempPlugin = nullptr;
//    tempPlugin = dynamic_cast<Plugin*> (RegisterPluginAddress(FApplication->Handle));
//
//    if (!tempPlugin)
//    {
//        ShowMessage("Couldn't register the plugin! Error!");
//        return nullptr;
//    }
//    return tempPlugin;
//}

//Plugin*  TPluginManager::loadBPLPlugin(const String& FileName, Windows::HINST& package)
//{
//    try
//    {
//        package = ::LoadPackage(FileName.c_str());
//    }
//    catch(...)
//    {
//        LPVOID lpMsgBuf;
//        DWORD dw = GetLastError();
//
//        FormatMessage(
//        FORMAT_MESSAGE_ALLOCATE_BUFFER |
//        FORMAT_MESSAGE_FROM_SYSTEM |
//        FORMAT_MESSAGE_IGNORE_INSERTS,
//        nullptr,
//        dw,
//        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
//        (LPTSTR) &lpMsgBuf,
//        0, nullptr );
//
//
//        String aMsg = (LPCTSTR) lpMsgBuf;
//        LocalFree(lpMsgBuf);
//
//        Log(lError)<<"Failed to load the plugin: " << FileName.c_str();
//        Log(lError)<<"The Error message was: "<<stdstr(aMsg);
//
//        return nullptr;
//    }
//
//    if(!package)
//    {
//        ShowMessage("Couldn't not load the package: " + FileName);
//        return nullptr;
//    }
//
//    DLLPROCADDRESS RegisterPluginAddress = (DLLPROCADDRESS) ::GetProcAddress((HINSTANCE) package, "RegisterPlugin");
//    if (!RegisterPluginAddress)
//    {
//        Log(lDebug)<<(string("Couldn't find RegisterPlugin function in plugin") + stdstr(FileName));
//        return nullptr;
//    }
//
//    Plugin* tempPlugin = RegisterPluginAddress(FApplication->Handle);
//
//    if (!tempPlugin)
//    {
//        Log(lDebug)<<"Couldn't register the plugin: " << stdstr(FileName);
//        return nullptr;
//    }
////    tempPlugin->AssignLogger(gLogger);
//    return tempPlugin;
//}

//----------------------------------------------------------------------------
bool  TPluginManager::unLoadPlugin(int Index)
{
    Plugin* plugin = Plugins[Index];
    string pName = plugin->getName();
    if(!plugin)
        return true;

//    if(Plugins[Index]->GetBPLInstance())
//    {
//        Windows::HINST inst = Plugins[Index]->GetBPLInstance();
//        //delete plugin;
//        UnloadPackage(inst);
//    }
//    if (Plugins[Index]->getDLLInstance())
//    {
//        HINSTANCE inst = Plugins[Index]->getDLLInstance();
//        //delete plugin;
//        FreeLibrary(inst);
//    }
    return false;
}

bool TPluginManager::unLoadAllPlugins()
{
    return mPM.unloadAll();
}


