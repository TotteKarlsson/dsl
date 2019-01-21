#ifndef ShellHelpersH
#define ShellHelpersH
#include <windows.h>
#include <windowsx.h>           // for WM_COMMAND handling macros
#include <shlobj.h>             // shell stuff
#include <shlwapi.h>            // QISearch, easy way to implement QI
#include <strsafe.h>
#include "VCLCommonExporter.h"

//Link to some libs...
//#pragma comment(lib, "shlwapi.lib")     // link to this
//#pragma comment(lib, "comctl32.lib")    // link to this
//#pragma comment(lib, "propsys.lib")     // link to this

HRESULT VCL_COMMON GetIDListName(IShellItem *psi, PWSTR *ppsz);

#define MAP_ENTRY(x) {L"" #x, x}
PCWSTR VCL_COMMON EventName(long lEvent);

__inline HRESULT ResultFromKnownLastError()
{
    const DWORD err = GetLastError();
    return err == ERROR_SUCCESS ? E_FAIL : HRESULT_FROM_WIN32(err);
}

// map Win32 APIs that follow the return BOOL/set last error protocol
// into HRESULT
//
// example: MoveFileEx()

__inline HRESULT ResultFromWin32Bool(BOOL b)
{
    return b ? S_OK : ResultFromKnownLastError();
}

// free the HICON that was set using SetDialogIcon()
__inline void ClearDialogIcon(HWND hdlg)
{
    DestroyIcon((HICON)SendMessage(hdlg, WM_GETICON, ICON_SMALL, 0));
    DestroyIcon((HICON)SendMessage(hdlg, WM_GETICON, ICON_BIG, 0));
}

__inline HRESULT SHILCloneFull(PCUIDLIST_ABSOLUTE pidl, PIDLIST_ABSOLUTE *ppidl)
{
    *ppidl = ILCloneFull(pidl);
    return *ppidl ? S_OK : E_OUTOFMEMORY;
}

__inline HRESULT SHILClone(PCUIDLIST_RELATIVE pidl, PIDLIST_RELATIVE *ppidl)
{
    *ppidl = ILClone(pidl);
    return *ppidl ? S_OK : E_OUTOFMEMORY;
}

__inline HRESULT SHILCombine(PCIDLIST_ABSOLUTE pidl1, PCUIDLIST_RELATIVE pidl2, PIDLIST_ABSOLUTE *ppidl)
{
    *ppidl = ILCombine(pidl1, pidl2);
    return *ppidl ? S_OK : E_OUTOFMEMORY;
}

__inline HRESULT GetItemAt(IShellItemArray *psia, DWORD i, REFIID riid, void **ppv)
{
    *ppv = nullptr;
    IShellItem *psi = nullptr;     // avoid error C4701
    HRESULT hr = psia ? psia->GetItemAt(i, &psi) : E_NOINTERFACE;
    if (SUCCEEDED(hr))
    {
        hr = psi->QueryInterface(riid, ppv);
        psi->Release();
    }
    return hr;
}

//#define MAP_ENTRY(x) {L#x, x}
//
//__inline HRESULT ShellAttributesToString(SFGAOF sfgaof, PWSTR *ppsz)
//{
//    *ppsz = nullptr;
//
//    static const struct {PCWSTR pszName; SFGAOF sfgaof; } c_rgItemAttributes[] =
//    {
//        // note, SFGAO_HASSUBFOLDER is too expesnive to compute
//        // and has been excluded from this list
//        MAP_ENTRY(SFGAO_STREAM),
//        MAP_ENTRY(SFGAO_FOLDER),
//        MAP_ENTRY(SFGAO_FILESYSTEM),
//        MAP_ENTRY(SFGAO_FILESYSANCESTOR),
//        MAP_ENTRY(SFGAO_STORAGE),
//        MAP_ENTRY(SFGAO_STORAGEANCESTOR),
//        MAP_ENTRY(SFGAO_LINK),
//        MAP_ENTRY(SFGAO_CANCOPY),
//        MAP_ENTRY(SFGAO_CANMOVE),
//        MAP_ENTRY(SFGAO_CANLINK),
//        MAP_ENTRY(SFGAO_CANRENAME),
//        MAP_ENTRY(SFGAO_CANDELETE),
//        MAP_ENTRY(SFGAO_HASPROPSHEET),
//        MAP_ENTRY(SFGAO_DROPTARGET),
//        MAP_ENTRY(SFGAO_ENCRYPTED),
//        MAP_ENTRY(SFGAO_ISSLOW),
//        MAP_ENTRY(SFGAO_GHOSTED),
//        MAP_ENTRY(SFGAO_SHARE),
//        MAP_ENTRY(SFGAO_READONLY),
//        MAP_ENTRY(SFGAO_HIDDEN),
//        MAP_ENTRY(SFGAO_REMOVABLE),
//        MAP_ENTRY(SFGAO_COMPRESSED),
//        MAP_ENTRY(SFGAO_BROWSABLE),
//        MAP_ENTRY(SFGAO_NONENUMERATED),
//        MAP_ENTRY(SFGAO_NEWCONTENT),
//    };
//
//    WCHAR sz[512] = {};
//    PWSTR psz = sz;
//    size_t cch = ARRAYSIZE(sz);
//
//    StringCchPrintfEx(psz, cch, &psz, &cch, 0, L"0x%08X", sfgaof);
//
//    for (int i = 0; i < ARRAYSIZE(c_rgItemAttributes); i++)
//    {
//        if (c_rgItemAttributes[i].sfgaof & sfgaof)
//        {
//            StringCchPrintfEx(psz, cch, &psz, &cch, 0, L", %s", c_rgItemAttributes[i].pszName);
//        }
//    }
//    return SHStrDup(sz, ppsz);
//}

template <class T> void SafeRelease(T **ppT)
{
    if (*ppT)
    {
        (*ppT)->Release();
        *ppT = nullptr;
    }
}

// assign an interface pointer, release old, capture ref to new, can be used to set to zero too

template <class T> HRESULT SetInterface(T **ppT, IUnknown *punk)
{
    SafeRelease(ppT);
    return punk ? punk->QueryInterface(ppT) : E_NOINTERFACE;
}

// remote COM methods are dispatched in the context of an exception handler that consumes
// all SEH exceptions including crahses and C++ exceptions. this is undesirable as it
// means programs will continue to run after such an exception has been thrown,
// leaving the process in a inconsistent state.
//
// this applies to COM methods like IDropTarget::Drop()
//
// this code turns off that behavior

__inline void DisableComExceptionHandling()
{
    IGlobalOptions *pGlobalOptions;
    HRESULT hr =  CoCreateInstance(CLSID_GlobalOptions, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pGlobalOptions));
    if (SUCCEEDED(hr))
    {
#if (NTDDI_VERSION >= NTDDI_WIN7)
        hr = pGlobalOptions->Set(COMGLB_EXCEPTION_HANDLING, COMGLB_EXCEPTION_DONOT_HANDLE_ANY);
#else
        hr = pGlobalOptions->Set(COMGLB_EXCEPTION_HANDLING, COMGLB_EXCEPTION_DONOT_HANDLE);
#endif
        pGlobalOptions->Release();
    }
}
#endif
