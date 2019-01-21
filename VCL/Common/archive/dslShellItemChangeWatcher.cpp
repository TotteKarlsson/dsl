#pragma hdrstop
#include "dslLogger.h"
#include "dslVCLUtils.h"
#include "dslShellHelpers.h"
#include "dslShellItemChangeWatcher.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
using namespace dsl;

dslShellItemChangeWatcher::dslShellItemChangeWatcher()
:
mRegistrationID(0)
{}

dslShellItemChangeWatcher::~dslShellItemChangeWatcher()
{
    StopWatching();
}

bool dslShellItemChangeWatcher::IsWatching()
{
    return (mRegistrationID != 0) ? true : false;
}

bool dslShellItemChangeWatcher::IsItemNotificationEvent(long lEvent)
{
    return !(lEvent & ( SHCNE_UPDATEIMAGE         |
                        SHCNE_ASSOCCHANGED         |
                        SHCNE_EXTENDED_EVENT     |
                        SHCNE_FREESPACE         |
                        SHCNE_DRIVEADDGUI         |
                        SHCNE_SERVERDISCONNECT));
}

HRESULT dslShellItemChangeWatcher::StartWatching(PIDLIST_ABSOLUTE pidl, HWND hwnd, UINT uMsg, long lEvents, BOOL fRecursive)
{
    if(IsWatching())
    {
        StopWatching();
    }

    SHChangeNotifyEntry const entries[] = {pidl, fRecursive};

    int const nSources =
                SHCNRF_ShellLevel |
                SHCNRF_RecursiveInterrupt |
                SHCNRF_InterruptLevel |
                SHCNRF_NewDelivery;

    int nrOfEntries = ARRAYSIZE(entries);
    mRegistrationID = SHChangeNotifyRegister(hwnd, nSources, lEvents, uMsg, nrOfEntries, entries);

    return mRegistrationID;
}

void dslShellItemChangeWatcher::StopWatching()
{
    if (mRegistrationID)
    {
        SHChangeNotifyDeregister(mRegistrationID);
        mRegistrationID = 0;
    }
}

// in your window procedure call this message to dispatch the events
void dslShellItemChangeWatcher::OnChangeMessage(WPARAM wParam, LPARAM lParam)
{
    long lEvent;
    PIDLIST_ABSOLUTE *rgpidl;
    HANDLE hNotifyLock = SHChangeNotification_Lock((HANDLE)wParam, (DWORD)lParam, &rgpidl, &lEvent);
    if (hNotifyLock)
    {
        if (IsItemNotificationEvent(lEvent))
        {
            IShellItem2 *psi1 = nullptr, *psi2 = nullptr;
            TCHAR  path1[MAX_PATH] = {'\0'};
            TCHAR  path2[MAX_PATH] = {'\0'};
            if(rgpidl[0])
            {
                SHGetPathFromIDList(*rgpidl, path1);

            }

            if (rgpidl[1])
            {
                SHGetPathFromIDList(rgpidl[1], path2);
            }

            // derived class implements this method, that is where the events are delivered
            OnChangeNotify(lEvent, stdstr(path1), stdstr(path2));
        }
        else
        {
            // dispatch non-item events here in the future
        }
        SHChangeNotification_Unlock(hNotifyLock);
    }
}

