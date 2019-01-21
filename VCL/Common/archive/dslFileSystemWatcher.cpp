
#pragma hdrstop
//#include <shlobj.h>
//#include <System.hpp>
#include "dslVCLUtils.h"
#include "dslShellHelpers.h"
#include "dslFileSystemWatcher.h"
#include "dslLogger.h"

#pragma package(smart_init)
using namespace dsl;

bool dslFileSystemWatcher::StartWatchingFolder(const string& folder, HWND hwnd, UINT uMsg)
{
    mRootFolder = folder;
    PIDLIST_ABSOLUTE pidl = nullptr;

    String fldr = mRootFolder.c_str();
    HRESULT hr = SHParseDisplayName(fldr.c_str(), nullptr, &pidl, 0, nullptr);
    bool result = false;
    if(SUCCEEDED(hr))
    {
        if(StartWatching(pidl, hwnd, uMsg, SHCNE_ALLEVENTS, true))
        {
            result = true;
            Log(lInfo)<<"Watching folder: "<<mRootFolder<<" for changes";
        }
        else
        {

               Log(lInfo)<<"Failed to start watching folder: "<<mRootFolder<<" for changes";
        }

    }

    //SHChangeNotifyRegister does not take ownership of the pidl
    CoTaskMemFree(pidl);
    return result;
}

void dslFileSystemWatcher::StopWatchingFolder()
{
    this->StopWatching();
       Log(lInfo)<<"Stopped watching folder: "<<mRootFolder<<" for changes";
}

//---------------------------------------------------------------------------
void dslFileSystemWatcher::OnChangeNotify(long lEvent, const string& path1, const string& path2)
{
    Log(lDebug3)<< "Event "<< stdstr(EventName(lEvent)) <<" is to be processed";
    //What event are we processing?
    switch(lEvent)
    {
        //------------ Folder stuff..
        case SHCNE_MKDIR:
            Log(lDebug3)<<"Folder was created";
        break;

        case SHCNE_RMDIR:
            Log(lDebug3)<<"Folder was removed";
        break;

        case SHCNE_UPDATEDIR:
            Log(lDebug3)<<"Updated dir";
        break;
        case SHCNE_RENAMEFOLDER:
            Log(lDebug3)<<"Folder was renamed";
        break;

        //------------- Non folderstuff
        case SHCNE_CREATE:
            Log(lDebug3)<<"File item was created";
        break;

        case SHCNE_DELETE:
            Log(lDebug3)<<"File item was deleted";
        break;
        case SHCNE_RENAMEITEM:
            Log(lDebug3)<<"File item was renamed";
        break;

        case SHCNE_UPDATEITEM:
            Log(lDebug3)<<"Updateing item";
        break;

        default:
            Log(lDebug3)<<"Event was not handled!";
        break;
    }
    Log(lDebug3)<<"Path1: "<<path1<<"\tPath2: "<<path2;
}


dslFileSystemWatcher::dslFileSystemWatcher() : mRootFolder(""){}
dslFileSystemWatcher::~dslFileSystemWatcher(){}
