#pragma hdrstop
#include <Shlobj.h>
#include <sstream>
#include "dslLogger.h"
#include "dslWin32Utils.h"
#include "dslUtils.h"
#include "dslFileUtils.h"
#include "dslException.h"
//---------------------------------------------------------------------------

namespace dsl
{

std::string ws2s(const std::wstring& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, 0, 0, 0, 0);
    char* buf = new char[len];
    WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, buf, len, 0, 0);
    std::string r(buf);
    delete[] buf;
    return r;
}

//From http://stackoverflow.com/questions/14762456/getclipboarddatacf-text
string getClipBoardText()
{
    // Try opening the clipboard
    if (! OpenClipboard(NULL))
    {
    	return "Clipboard ERROR";
    }

    // Get handle of clipboard object for ANSI text
    HANDLE hData = GetClipboardData(CF_TEXT);
    if (hData == NULL)
    {
    	return "Clipboard ERROR";
    }

    // Lock the handle to get the actual text pointer
    char * pszText = static_cast<char*>( GlobalLock(hData) );
    if (pszText == NULL)
    {
    	return "Clipboard ERROR";
    }

    // Save text in a string class instance
    string text( pszText );

    // Release the lock
    GlobalUnlock( hData );

    // Release the clipboard
    CloseClipboard();
    return text;
}

void sendToClipBoard(const string& str)
{
    const char* output = str.c_str();
    const size_t len = strlen(output) + 1;
    HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, len);
    memcpy(GlobalLock(hMem), output, len);
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();
}

string getTempPath()
{
    DWORD length = GetTempPathA( 0, NULL );
    if( length == 0 )
    {
        return "";
    }
    std::vector<TCHAR> tempPath( length );

    #if defined(_UNICODE)
	    length = GetTempPathW( static_cast<DWORD>( tempPath.size() ), &tempPath[0] );
    #else
	    length = GetTempPathA( static_cast<DWORD>( tempPath.size() ), &tempPath[0] );
    #endif
    if( length == 0 || length > tempPath.size() )
    {
        return "";
    }

    return std::string( tempPath.begin(), tempPath.begin() + static_cast<std::size_t>(length) );
}

string getSpecialFolder(int folder)
{
    TCHAR szPath[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPath(nullptr, folder, nullptr, 0, szPath)))
    {
        string theFolder = stdstr(szPath);

        if(!folderExists(theFolder))
        {
            stringstream msg;
            msg<< "Got folder path, but folder don't exist in function getSpecial folder. Folder was: "<<folder;
            throw(dsl::DSLException(msg.str()));
        }
        return theFolder;
    }
    else
    {
        stringstream msg;
        msg<< "Failed to get path to special folder: "<<folder;
        throw(dsl::DSLException(msg.str()));
    }
}

string getKnownFolder(GUID folderID, DWORD flags)
{
    PWSTR path;
    if (SUCCEEDED(SHGetKnownFolderPath(folderID, flags, nullptr, &path)))
    {
        string theFolder = stdstr(path);

        if(!folderExists(theFolder))
        {
            stringstream msg;
            msg<< "Got folder path, but the folder don't exist in function getSpecial folder. Folder ID was: " << folderID.Data4;
            throw(dsl::DSLException(msg.str()));
        }
        return theFolder;
    }
    else
    {
        stringstream msg;
        msg<< "Failed to get path to folder: " << folderID.Data4;
        throw(dsl::DSLException(msg.str()));
    }
}

string getLastWin32Error()
{
    LPVOID lpMsgBuf;
    DWORD dw = GetLastError();

    FormatMessageW(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPWSTR) &lpMsgBuf,
        0, nullptr );

    LPCTSTR aMsg = (LPCTSTR) lpMsgBuf;
    string msg = stdstr(aMsg);
    LocalFree(lpMsgBuf);
    return msg;
}

bool clickOnWindow(const string& winCaption, int localX, int localY)
{
	bool result(false);
	HWND phwnd = GetForegroundWindow();
    HWND hwnd = FindWindowA(0, (winCaption).c_str());
    if(hwnd)
    {
    	BOOL isIconic(IsIconic(hwnd));
    	if (isIconic)
        {
        	ShowWindow(hwnd, SW_RESTORE);
        }

        SetForegroundWindow(hwnd);
        RECT rect;
        GetWindowRect(hwnd, &rect);
        MouseClick(rect.left + localX, rect.top + localY + 30);
        if(isIconic)
        {
        	ShowWindow(hwnd, SW_SHOWMINIMIZED);
        }
        result = true;
    }
	SetForegroundWindow(phwnd); // To activate previous window
	return result;
}

void MouseClick(int x, int y)
{
    const double XSCALEFACTOR = 65535 / (GetSystemMetrics(SM_CXSCREEN) - 1);
    const double YSCALEFACTOR = 65535 / (GetSystemMetrics(SM_CYSCREEN) - 1);

    POINT cursorPos;
    GetCursorPos(&cursorPos);

    double cx = cursorPos.x * XSCALEFACTOR;
    double cy = cursorPos.y * YSCALEFACTOR;

    double nx = x * XSCALEFACTOR;
    double ny = y * YSCALEFACTOR;

    INPUT Input={0};
    Input.type = INPUT_MOUSE;

    Input.mi.dx = (LONG)nx;
    Input.mi.dy = (LONG)ny;

    Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP;
    SendInput(1,&Input,sizeof(INPUT));

    Input.mi.dx = (LONG)cx;
    Input.mi.dy = (LONG)cy;

    Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
	Sleep(300);
    SendInput(1,&Input,sizeof(INPUT));
}




}//Namespace

