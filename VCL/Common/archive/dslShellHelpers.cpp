
#pragma hdrstop
#include "dslShellItemIterator.h"
#include "dslShellHelpers.h"
#pragma package(smart_init)

PCWSTR EventName(long lEvent)
{
    PCWSTR psz = L"";
    static const struct { PCWSTR pszName; long lEvent; }
    c_rgEventNames[] =
    {
        MAP_ENTRY(SHCNE_RENAMEITEM),
        MAP_ENTRY(SHCNE_CREATE),
        MAP_ENTRY(SHCNE_DELETE),
        MAP_ENTRY(SHCNE_MKDIR),
        MAP_ENTRY(SHCNE_RMDIR),
        MAP_ENTRY(SHCNE_MEDIAINSERTED),
        MAP_ENTRY(SHCNE_MEDIAREMOVED),
        MAP_ENTRY(SHCNE_DRIVEREMOVED),
        MAP_ENTRY(SHCNE_DRIVEADD),
        MAP_ENTRY(SHCNE_NETSHARE),
        MAP_ENTRY(SHCNE_NETUNSHARE),
        MAP_ENTRY(SHCNE_ATTRIBUTES),
        MAP_ENTRY(SHCNE_UPDATEDIR),
        MAP_ENTRY(SHCNE_UPDATEITEM),
        MAP_ENTRY(SHCNE_SERVERDISCONNECT),
        MAP_ENTRY(SHCNE_DRIVEADDGUI),
        MAP_ENTRY(SHCNE_RENAMEFOLDER),
        MAP_ENTRY(SHCNE_FREESPACE),
        MAP_ENTRY(SHCNE_UPDATEITEM),
    };

    for (size_t i = 0; i < ARRAYSIZE(c_rgEventNames); i++)
    {
        if (c_rgEventNames[i].lEvent == lEvent)
        {
            psz = c_rgEventNames[i].pszName;
            break;
        }
    }
    return psz;
}

// debugging helper that returns a string that represents the IDList in
// this form "[computer][C:][Foo][bar.txt]".
HRESULT GetIDListName(IShellItem *psi, PWSTR *ppsz)
{
//    *ppsz = nullptr;
    HRESULT hr = E_FAIL;
//
//    WCHAR szFullName[2048];
//    szFullName[0] = 0;
//    PWSTR pszOutput = szFullName;
//    size_t cchOutput = ARRAYSIZE(szFullName);

//    dslShellItemIterator itemIterator(psi);
//    while (itemIterator.MoveNext())
//    {
//        IShellItem2 *psi;
//        hr = itemIterator.GetCurrent(IID_PPV_ARGS(&psi));
//        if (SUCCEEDED(hr))
//        {
//            PWSTR pszName;
//            hr = psi->GetDisplayName(SIGDN_PARENTRELATIVE, &pszName);
//            if (SUCCEEDED(hr))
//            {
//                // ignore errors, this is for debugging only
//                StringCchCatEx(pszOutput, cchOutput, L"[", &pszOutput, &cchOutput, 0);
//                StringCchCatEx(pszOutput, cchOutput, pszName, &pszOutput, &cchOutput, 0);
//                StringCchCatEx(pszOutput, cchOutput, L"]", &pszOutput, &cchOutput, 0);
//                CoTaskMemFree(pszName);
//            }
//
//            psi->Release();
//        }
//    }
//
//    if (SUCCEEDED(hr))
//    {
//        hr = SHStrDup(szFullName, ppsz);
//    }
    return hr;
}

