#pragma hdrstop
#include <sstream>
#include <algorithm>
#include <Registry.hpp>
#include "dslVCLUtils.h"
#include "dslStringUtils.h"
#include "dslLogger.h"
#include "dslApplicationInfo.h"
#include "dslVersion.h"
//#include <atl/atlbase.h>
#pragma package(smart_init)

namespace dsl
{

using namespace std;

string __fastcall joinPathU(const string& f1, const string& f2, const UnicodeString& f3)
{
	return joinPath(f1, f2, stdstr(f3));
}

string __fastcall joinPathU(const string& f1, const UnicodeString& f2)
{
	return joinPath(f1, stdstr(f2));
}

bool __fastcall sendApplicationMessage(TApplication* Application, long msg, long data1, long data2)
{
	if(!Application)
	{
		return false;
	}

	//Tell the application to go to the home tab
	HWND hWnd = Application->MainForm->Handle;
	LRESULT res = SendMessage(hWnd, msg, data1, data2);
	if(res)
	{
		Log(lError)<<"Sending message was unsuccesful";
		return false;
	}
	return true;
}

int __fastcall compareStringListItems(TStringList* l, int index1, int index2);
bool __fastcall sortTListBoxNumerically(TListBox* lb)
{
	TStringList* tempList = new TStringList;
    tempList->Assign(lb->Items);
    tempList->CustomSort(compareStringListItems);
    lb->Items->Assign(tempList);
    delete tempList;
	return true;
}

int __fastcall compareStringListItems(TStringList* l, int index1, int index2)
{
	int l1 = (l->Strings[index1]).ToInt();
	int l2 = (l->Strings[index2]).ToInt();
    if(l1 < l2)
    {
    	return -1;
    }
    else
    {
	 	if(l1 > l2)
        {
        	return 1;
        }
        else
        {
        	return 0;
        }
    }
}

string __fastcall createWindowTitle(const string& appName, TApplication* app)
{
	stringstream title;
    if(!app)
    {
        return "";
    }
	dslApplicationInfo appInfo(app);

	title << appName;

    Version version(stdstr(appInfo.mVersion));
    title <<" - [Version: "<< version.getMajor() << "." << version.getMinor() << "." << version.getPatch()<<"]";

    return title.str();
}

void __fastcall populateStyleRG(TRadioGroup* ThemesRG)
{
    if(!ThemesRG)
    {
        return;
    }

	String currStyle = TStyleManager::ActiveStyle->Name;
    ThemesRG->Items->Clear();
    StringList s;
	for (int i = 0; i < TStyleManager::StyleNames.Length; i++)
	{
        s.append(stdstr(TStyleManager::StyleNames[i]));
    }

    s.sort();

	for (int i = 0; i < s.count(); i++)
	{
		ThemesRG->Items->Add(s[i].c_str());
        if(stdstr(currStyle) == s[i])
        {
            ThemesRG->ItemIndex = i;
        }
    }
}

void __fastcall populateStyleMenu(TMenuItem* ThemesMenu, TNotifyEvent ThemesMenuClick)
{
    if(!ThemesMenu)
    {
        return;
    }

	String currStyle = TStyleManager::ActiveStyle->Name;
    ThemesMenu->Clear();
	for (int i = 0; i < TStyleManager::StyleNames.Length; i++)
	{
		TMenuItem *Item = new TMenuItem(ThemesMenu);
		Item->Caption = TStyleManager::StyleNames[i];
		Item->OnClick = ThemesMenuClick;
		ThemesMenu->Add(Item);
        if(currStyle == Item->Caption)
        {
            Item->Checked = true;
        }
    }
}

string __fastcall createWindowTitle(const string& appName, TApplication* app, ApplicationLicenseController& lc)
{
	stringstream title;
    if(!app)
    {
        return "";
    }
	dslApplicationInfo appInfo(app);

	title << appName;

	//Check if pre release
	if(lc.getLicenseMode() == lmActivated)
    {
        ////Figure out if this is a lite or standard version
        //title << " Lite";
    }

    Version version(stdstr(appInfo.mVersion));
    title <<" - [Version: "<< version.getMajor() << "." << version.getMinor() << "." << version.getPatch()<<"]";

    //Check if pre release
    if(lc.isPreRelease())
    {
        title << " - (PreRelesase)";
    }

    //Check if pre release
    if(lc.getLicenseMode() == lmTrial)
    {
        title << " - (Trial Mode)";
    }

    return title.str();
}

string __fastcall readStringFromRegistry(const string& regRoot, const string& section, const string& key, const string& def)
{
    std::auto_ptr<TRegIniFile> reg(new TRegIniFile(regRoot.c_str()));
    String str = reg->ReadString(section.c_str(), key.c_str(), def.c_str());
    return stdstr(str);
}

bool __fastcall writeStringToRegistry(const string& regRoot, const string& section, const string& key, const string& value)
{
    std::auto_ptr<TRegIniFile> reg(new TRegIniFile(regRoot.c_str()));

    reg->WriteString(section.c_str(), key.c_str(), value.c_str());
    return true;
}

bool __fastcall clearStringGrid(TStringGrid* grid)
{
    for(int i = 0; i <  grid->RowCount; i++)
    {
        grid->Rows[i]->Clear();
    }
    return true;
}


//string __fastcall getSpecialFolder(int folder)
//{
//    TCHAR szPath[MAX_PATH];
//    if (SUCCEEDED(SHGetFolderPath(nullptr, folder, nullptr, 0, szPath)))
//    {
//        string theFolder = stdstr(szPath);
//        Log(lDebug1) << "Returning special folder: " << theFolder;
//
//        if(!folderExists(theFolder))
//        {
//            Log(lDebug1) << "Special folder: " << folder<< " do not exist";
//        }
//        return theFolder;
//    }
//    else
//    {
//        Log(lDebug1) << "Failed getting folder path for: " << folder;
//        return string("");
//    }
//}


string __fastcall stdstr(const String& str)
{
    wstring test(str.c_str());
    return stdstr(test);
}

String __fastcall vclstr(const char* s)
{
    return String( s );
}

String __fastcall vclstr(const std::string& s)
{
    return String( s.c_str(), s.length() );
}

String __fastcall vclstr(const std::ostringstream& s)
{
    return vclstr(s.str());
}

vector<string> __fastcall stdlines(TStrings* lines)
{
    vector<string> slines;
    for(int i = 0; i < lines->Count; i++)
    {
        slines.push_back(stdstr(lines->Strings[i]));
    }
    return slines;
}

//wstring __fastcall ToWStdString(const string& str)
//{
//    wstring temp(str.begin(), str.end());
//    return temp;
//}
//
//string __fastcall ToSTDString(const UnicodeString& str)
//{
//    wstring temp1 = str.c_str();
//    string temp2(temp1.begin(), temp1.end());
//    return temp2;
//}
//
//string __fastcall ToSTDString(const wstring& str)
//{
//    string temp(str.begin(), str.end());
//    return temp;
//}
//
//String __fastcall ToUIString (const std::string &in)
//{
//    return in.c_str();
//}
//
//String __fastcall ToUIString (const std::wstring &in)
//{
//    return in.c_str();
//}

ostream&  __fastcall operator << (ostream& stream, const String& aString)
{
    stream<<aString.c_str();
    return stream;
}

bool __fastcall isExecutedInProgramFiles()
{
    string appPath = stdstr(getApplicationPath());
    if(appPath.size())
    {
        return contains("Program Files", appPath);
    }
    return false;
}

String __fastcall GetCWD()
{
    String dir = "";
    ::GetCurrentDirectoryW(sizeof(dir) - 1, dir.c_str());
    return dir;
}

bool __fastcall SetCWD(const string& wd)
{
    return SetCurrentDirectoryA(wd.c_str());
}

//Return application path on success, empty string on failure
string __fastcall getApplicationPath()
{
    char buff[MAX_PATH];
    if (!GetModuleFileNameA(nullptr, buff, sizeof(buff)) || (GetLastError() == ERROR_INSUFFICIENT_BUFFER))
    {
        return "";
    }

    string path;
    path = buff;
    string::size_type pos = path.rfind('\\');
    if (pos == string::npos)
    {
        return "";
    }

    path.erase(path.begin() + pos + 1, path.end());

    pos = path.rfind('.');
    if (pos != string::npos)
    {
        path.erase(path.begin() + pos, path.begin() + pos + 2);
    }

//    string temp;
//    temp = ToWStdString(path).c_str();
    return path;
}

string __fastcall getApplicationName()
{
    bool dontCare;
    return stdstr(getApplicationNameW().c_str());
}

string __fastcall getApplicationNameW()
{
    char buff[MAX_PATH];
    if (!GetModuleFileNameA(nullptr, buff, sizeof(buff)) || (GetLastError() == ERROR_INSUFFICIENT_BUFFER))
    {
        return "";
    }

    string path(buff);
    //path = TEXT(buff);
    string::size_type pos = path.rfind('\\');
    if (pos == string::npos)
    {
        return "";
    }

    path.erase(path.begin(), path.begin() + pos + 1);

    string temp (path.c_str());
    return temp;
}

void __fastcall ShutDownWindows(int operation)
{
    HANDLE hToken;
    TOKEN_PRIVILEGES tkp;

    OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);

    LookupPrivilegeValueA(nullptr, "SeShutdownPrivilege",  &tkp.Privileges[0].Luid);

    tkp.PrivilegeCount = 1;
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,(PTOKEN_PRIVILEGES)nullptr, 0);
    //ExitWindowsEx(EWX_FORCE|operation, -1);
    ExitWindowsEx(operation, -1);
}

string __fastcall getProductName(TApplication* Application)
{
    struct TransArray
    {
        WORD LanguageID, CharacterSet;
    };

    string prodName;
    DWORD VerInfo, VerSize;
    HANDLE MemHandle;
    LPVOID MemPtr, BufferPtr;
    UINT BufferLength;
    TransArray *Array;
    char QueryBlock[40];

    // Get the product name and version from the
    // applications version information.
    string  Path;
    Path = stdstr(Application->ExeName);
    VerSize = GetFileVersionInfoSizeA(Path.c_str(), &VerInfo);
    if (VerSize > 0)
    {
        MemHandle     = GlobalAlloc(GMEM_MOVEABLE, VerSize);
        MemPtr         = GlobalLock(MemHandle);
        GetFileVersionInfoA(Path.c_str(), VerInfo, VerSize, MemPtr);
        VerQueryValueA(MemPtr, "\\VarFileInfo\\Translation", &BufferPtr, &BufferLength);
        Array = (TransArray *)BufferPtr;

        // Get the product name.
        sprintf(QueryBlock, "\\StringFileInfo\\%04x%04x\\ProductName", Array[0].LanguageID, Array[0].CharacterSet);
        VerQueryValueA(MemPtr, QueryBlock, &BufferPtr, &BufferLength);
        // Set the product name
        prodName = (char *)BufferPtr;
        GlobalUnlock(MemPtr);
        GlobalFree(MemHandle);
    }
    else
    {
        prodName = "";
    }

    return prodName;
}

string __fastcall getProductVersion(TApplication* Application)
{
    struct TransArray
    {
        WORD LanguageID, CharacterSet;
    };

    // Get the product name and version from the
    // applications version information.
    string Path(stdstr(Application->ExeName));
    DWORD VerInfo;
    DWORD VerSize =  GetFileVersionInfoSizeA(Path.c_str(), &VerInfo);
    string version;

    if (VerSize > 0)
    {
        HANDLE MemHandle = GlobalAlloc(GMEM_MOVEABLE, VerSize);
        LPVOID MemPtr = GlobalLock(MemHandle);
        LPVOID BufferPtr;
        UINT BufferLength;

        GetFileVersionInfoA(Path.c_str(), VerInfo, VerSize, MemPtr);
        VerQueryValueA(MemPtr, "\\VarFileInfo\\Translation", &BufferPtr, &BufferLength);
        TransArray *Array = (TransArray *)BufferPtr;

        // Get the product version.
        char QueryBlock[40];
        sprintf(QueryBlock, "\\StringFileInfo\\%04x%04x\\FileVersion", Array[0].LanguageID, Array[0].CharacterSet);
        VerQueryValueA(MemPtr, QueryBlock, &BufferPtr, &BufferLength);

        // Set the version caption.
        version = (char *)BufferPtr;

        GlobalUnlock(MemPtr);
        GlobalFree(MemHandle);
    }
    else
    {
      version = "";
    }
    return version;
}

string __fastcall getProductRegistryRoot(TApplication* Application)
{
    if(!Application)
    {
        return "";
    }

    return "SOFTWARE\\DuneScientific\\" + getProductName(Application);
}

void __fastcall enableDisablePageControl(TPageControl *p, bool b)
{
    if(!p)
    {
        return;
    }

    p->Enabled = b;
    for(int i = 0; i < p->PageCount; i++)
    {
    	TTabSheet* ts = p->Pages[i];
        if(ts)
        {
//	        ts->Visible = b;
        	ts->Enabled = b;
        }
    }
}

void __fastcall enableDisablePanel(TPanel *p, bool b)
{
    if(!p)
    {
        return;
    }

    for(int x = 0; x < p->ControlCount; x++)
    {
        TControl *control = dynamic_cast<TControl*>(p->Controls[x]);
        if(control)
        {
        	if(dynamic_cast<TGroupBox*>(control))
            {
				enableDisableGroupBox(dynamic_cast<TGroupBox*>(control), b);
            }

            if(dynamic_cast<TPanel*>(control))
            {
				enableDisablePanel(dynamic_cast<TPanel*>(control), b);
            }

            control->Enabled = b;
        }
    }
    p->Enabled = b;
}

void __fastcall enableDisableGroupBox(TGroupBox *GB, bool enable)
{
    if(!GB)
        return;

    for(int x = 0; x < GB->ControlCount; x++)
    {
        TControl *control = dynamic_cast<TControl*>(GB->Controls[x]);
        if(dynamic_cast<TPanel*>(control))
        {
        	enableDisablePanel(dynamic_cast<TPanel*>(control), enable);
        }
        if(dynamic_cast<TGroupBox*>(control))
        {
        	enableDisableGroupBox(dynamic_cast<TGroupBox*>(control), enable);
        }

        if(control)
        {
            control->Enabled = (enable);
        }
    }
    GB->Enabled = enable;
}

void __fastcall EnableDisableCControl(TCustomControl *CC, bool enable)
{
    if(!CC)
        return;

    for(int x = 0; x < CC->ControlCount; x++)
    {
        TCustomControl *control = dynamic_cast<TCustomControl*>(CC->Controls[x]);
        if(control)
        {
            TGroupBox *gb = dynamic_cast<TGroupBox*>(control);
            if(gb)
            {
                enableDisableGroupBox(gb, enable);
            }
            control->Enabled = (enable);
        }
    }
    CC->Enabled = enable;
}

void __fastcall EnableDisableForm(TForm *form, bool enable)
{
    //Enable or Disable all contols on a form..
    //First disable/enable all groupboxes..
    if(!form)
        return;

    for(int x = 0; x < form->ControlCount; x++)
    {
        TGroupBox *control = dynamic_cast<TGroupBox*>(form->Controls[x]);
        if(control)
        {
           enableDisableGroupBox(control, enable);
        }
    }

    for(int x = 0; x < form->ControlCount; x++)
    {
        TCustomControl *control = dynamic_cast<TCustomControl*>(form->Controls[x]);
        if(control)
        {
            TGroupBox *gb = dynamic_cast<TGroupBox*>(control);
            if(gb)
                enableDisableGroupBox(gb, enable);
            control->Enabled = (enable);
        }
    }
    //  form->Enabled = enable;
}

void __fastcall EnableDisableFrame(TFrame *f, bool enable)
{
    //Enable or Disable all contols on a frame..
    //First disable/enable all groupboxes..
    if(!f)
        return;

    for(int x = 0; x < f->ControlCount; x++)
    {
        TGroupBox *control = dynamic_cast<TGroupBox*>(f->Controls[x]);
        if(control)
        {
            enableDisableGroupBox(control, enable);
        }
    }

    for(int x = 0; x < f->ControlCount; x++)
    {
        TCustomControl *control = dynamic_cast<TCustomControl*>(f->Controls[x]);
        if(control)
        {
            TGroupBox *gb = dynamic_cast<TGroupBox*>(control);
            if(gb)
            {
                enableDisableGroupBox(gb, enable);
            }
            control->Enabled = (enable);
        }
    }
    f->Enabled = enable;
}

void __fastcall EnableDisableComponent(TComponent *comp, bool enable)
{
    //Enable or Disable all contols on a comp..
    //First disable/enable all groupboxes..
    if(!comp)
        return;

    for(int x = 0; x < comp->ComponentCount; x++)
    {
        TCustomControl *control = dynamic_cast<TCustomControl*>(comp->Components[x]);
        if(control)
        {
            EnableDisableCControl(control, enable);
        }
    }
}

void __fastcall EnableDisableActions(TActionList *aL, bool enable){

    if(enable)
    {
        for(int i = 0; i < aL->ActionCount; i++)
        {
            TAction* act = (TAction*) aL->Actions[i];
            act->Enabled = true;
        }
    }
    else
    {
        for(int i = 0; i < aL->ActionCount; i++)
        {
            TAction* act = (TAction*) aL->Actions[i];
            act->Enabled = false;
        }
    }
}

TStringList* __fastcall GetFilesInDir(const String& Folder, const String& FileExt)
{
    String folder;
    //If Folder is empty, get current folder
    if(Folder.Length() == 0)
    {
        folder = GetCurrentDir();
    }
    else
    {
        folder = Folder;
    }
    String fExt = FileExt;

    if (folder[folder.Length()] != '\\')
        folder += "\\";

    int nrOfPlugins = 0;

    TStringList* list = new TStringList;
    TSearchRec SearchRecord;
    int Found = FindFirst(folder + "*." + fExt, 0 , SearchRecord);
    while(Found == 0)
    {
        nrOfPlugins++;
        Found = FindNext(SearchRecord);
    }
    FindClose(SearchRecord);

    Found = FindFirst(folder + "*." + fExt, 0 , SearchRecord);
    String FileName = "";

    while(Found == 0)
    {
        FileName = folder + SearchRecord.Name;
        list->Add(FileName);
        Found = FindNext(SearchRecord);
    }
    FindClose(SearchRecord);
    return list;
}

//---------------------------------------------------------------------------
bool __fastcall IsDirectory(const string &path)
{
    DWORD dw =  GetFileAttributesA(path.c_str());
    return ( dw != 0xffffffff  &&  dw & FILE_ATTRIBUTE_DIRECTORY);
}

int __fastcall GetNrOfFilesInDir(const String& path, const String& searchMask)
{
    int iAttributes = 0;
    iAttributes |= faAnyFile;
    String search = path + "\\" + searchMask;
    int FileCount = 0;
    TSearchRec sr;
    if(FindFirst(search, iAttributes, sr) == 0)
    {
        do
        {
            if(sr.Attr != faDirectory)
                FileCount++;
        }
        while (FindNext(sr) == 0);
    }
    FindClose(sr);
    return FileCount;
}

string __fastcall browseForFolder(const string& startFolder)
{
    string result;
 	HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (SUCCEEDED(hr))
    {
        IFileOpenDialog *pfd;

        // Create the FileOpenDialog object.
        hr = CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&pfd));
        if (SUCCEEDED(hr))
        {
            DWORD dwOptions;
            if (SUCCEEDED(pfd->GetOptions(&dwOptions)))
            {
                pfd->SetOptions(dwOptions | FOS_PICKFOLDERS);
            }

            // Show the Open dialog box.

			IShellItem* psiFolder;

        	hr = SHCreateItemFromParsingName ( wstdstr(startFolder).c_str(), NULL, IID_PPV_ARGS(&psiFolder) );

            if ( SUCCEEDED(hr) )
              pfd->SetFolder ( psiFolder );


            hr = pfd->Show(nullptr);

            // Get the file name from the dialog box.
            if (SUCCEEDED(hr))
            {
                IShellItem *pItem;
                hr = pfd->GetResult(&pItem);
                if (SUCCEEDED(hr))
                {
                    PWSTR pszFilePath;
                    hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                    // Display the file name to the user.
                    if (SUCCEEDED(hr))
                    {
                        result = stdstr(String(pszFilePath));
                        CoTaskMemFree(pszFilePath);
                    }
                    pItem->Release();
                }
            }
            pfd->Release();
        }
        else
        {
        	return string("");
        }

        CoUninitialize();
    }
    return result;
}

string __fastcall browseForFile(const string& startFolder)
{
    string result;
 	HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (SUCCEEDED(hr))
    {
        IFileOpenDialog *pfd;

        // Create the FileOpenDialog object.
        hr = CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&pfd));
        if (SUCCEEDED(hr))
        {
            DWORD dwOptions;
            if (SUCCEEDED(pfd->GetOptions(&dwOptions)))
            {
                pfd->SetOptions(dwOptions);
            }

            // Show the Open dialog box.
            hr = pfd->Show(nullptr);

            // Get the file name from the dialog box.
            if (SUCCEEDED(hr))
            {
                IShellItem *pItem;
                hr = pfd->GetResult(&pItem);
                if (SUCCEEDED(hr))
                {
                    PWSTR pszFilePath;
                    hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                    // Display the file name to the user.
                    if (SUCCEEDED(hr))
                    {
                        result = stdstr(String(pszFilePath));
                        CoTaskMemFree(pszFilePath);
                    }
                    pItem->Release();
                }
            }
            pfd->Release();
        }
        else
        {
        	return string("");
        }

        CoUninitialize();
    }
    return result;
}

String __fastcall BrowseForDir(void* Handle)
{
    //Browse for folder...
    _browseinfoA BInfo;

    char DirPath[MAX_PATH] = "";
    char FolderName[MAX_PATH];
    LPITEMIDLIST ItemID;
    memset(&BInfo, 0, sizeof(BInfo));
    BInfo.hwndOwner = (HWND) Handle;
    BInfo.pszDisplayName = FolderName;
    LPCSTR szCurrent = "p:\\models";
    BInfo.lParam    = (LPARAM) szCurrent;
    BInfo.lpszTitle = "Select a folder";

    ItemID = SHBrowseForFolderA(&BInfo);

    if(ItemID)
    {
        String folder;
        SHGetPathFromIDListA(ItemID, DirPath);
        folder = DirPath;
        folder += "\\";
        //    OutPutDirEdit->Text = MinimizeName(workingDir, Canvas, 250);
        return folder.Length() ? String(folder) : String(0);
    }
    return "";
}

TActionToolBar * __fastcall CreateActionToolBar(const string& caption, TActionManager *actionManager, TWinControl* parent)
{
    // Create my own TAction Tool Bar
    TActionToolBar *myActionToolBar = new TActionToolBar(parent);
    myActionToolBar->Parent     = parent;
    myActionToolBar->Align         = alTop;
    myActionToolBar->Caption     = caption.c_str();
    myActionToolBar->Hint         = caption.c_str();
    myActionToolBar->ShowHint     = true;

    myActionToolBar->ActionManager                 = actionManager;
    return myActionToolBar;
}

void __fastcall AddActionsToActionManager(TCustomActionList* actionList, const String& caption, TActionManager *actionManager)
{
    if(!actionList || !actionManager)
        return ;

    TCollectionItem* coll = actionManager->LinkedActionLists->Add();
    TActionListItem* actionListItem = actionManager->LinkedActionLists->ListItems[actionManager->LinkedActionLists->Count -1];
    actionListItem->ActionList     = actionList;
    actionListItem->Caption     = caption;
}

void __fastcall RemoveActionsFromActionManager(TCustomActionList* actionList, TActionManager *actionManager)
{
    //Find a TActionListItem that have the same actionlist as actionList
    TActionListItem* actionListItem = nullptr;
    for(int i = 0; i < actionManager->LinkedActionLists->Count; i++)
    {
        actionListItem = actionManager->LinkedActionLists->ListItems[i];
        if(actionListItem->ActionList == actionList)
        {
            actionManager->LinkedActionLists->Delete(i);
        }
    }
}

void __fastcall RemoveActionsFromActionToolBar(TCustomActionList* list, TActionToolBar *actionToolBar)
{
    if(!actionToolBar || !list)
        return;

    int i = 0;
    while(i < actionToolBar->ActionClient->Items->Count)
    {
        TActionClientItem *actionClient = actionToolBar->ActionClient->Items->ActionClients[i];
        bool found = false;

        for(int j = 0; j < list->ActionCount; ++j)
        {
            if( actionClient->Action == list->Actions[j] )
            {
                found = true;
                break;
            }
        }

        if(found)
            actionToolBar->ActionClient->Items->Delete(i);
        else
            ++i;
    }
}

void __fastcall RemoveActionsFromActionMainMenu(TCustomActionList* actionList, TActionMainMenuBar* actionMM)
{
    if(!actionMM || ! actionList)
        return;
}

StringList __fastcall getCheckedItems(TCheckListBox* listBox)
{
    //Go trough the listbox and return checked items
    StringList checked;
    for(int i = 0; i < listBox->Count; i++)
    {
        if(listBox->Checked[i])
        {
            String anItem = listBox->Items->Strings[i];
            checked.append(stdstr(anItem));
        }
    }
    return checked;
}

int __fastcall getNumberOfCheckedItems(TCheckListBox* listBox)
{
    //Go trough the listbox and return checked items
	int checked(0);
    for(int i = 0; i < listBox->Count; i++)
    {
        if(listBox->Checked[i])
        {
            checked++;
        }
    }
    return checked;
}

StringList __fastcall getStrings(TMemo* memo)
{
    //Go trough the listbox and return checked items
    StringList strings;
    for(int i = 0; i < memo->Lines->Count; i++)
    {
    	String anItem = memo->Lines->Strings[i];
        strings.append(stdstr(anItem));
    }
    return strings;
}

void __fastcall addItemsToCheckListBox(const StringList& items, TCheckListBox *lb, bool checked)
{
    for(size_t i = 0; i < items.count(); i++)
    {
        int index = lb->Items->Add(items[i].c_str());
        lb->Checked[index] = checked;
    }
}

void __fastcall addCheckedUncheckedItemsToCheckListBox(const StringList& items, TCheckListBox *lb)
{
    for(size_t i= 0; i < items.count(); i++)
    {
        StringList item(items[i], '-');
        int nrOfItems = item.size();
        if(item.size() != 2)
        {
            Log(lError) << "Bad format of fileMask db record";
            if(item.size())
            {
                int index = lb->Items->Add(item[0].c_str());
                lb->Checked[index] = true;
            }
        }
        else
        {
            int index = lb->Items->Add(item[0].c_str());
            lb->Checked[index] = toBool(item[1]);
        }
    }
}

void __fastcall populateListBox(const StringList& items, TListBox *lb)
{
	lb->Clear();
    for(size_t i = 0; i < items.count(); i++)
    {
        int index = lb->Items->Add(items[i].c_str());
    }
}

StringList __fastcall getStrings(TListBox *listBox)
{
    //Go trough the listbox and return items
    StringList items;
    for(int i = 0; i < listBox->Count; i++)
    {
    	String anItem = listBox->Items->Strings[i];
        if(anItem.Length())
        {
            items.append(stdstr(anItem));
        }
    }
    return items;
}

StringList __fastcall getStrings(TCheckListBox *listBox)
{
    //Go trough the listbox and return items
    StringList items;
    for(int i = 0; i < listBox->Count; i++)
    {
    	String anItem = listBox->Items->Strings[i];
        if(anItem.Length())
        {
            items.append(stdstr(anItem));
        }
    }
    return items;
}

void __fastcall populateCheckListBox(const StringList& items, TCheckListBox *lb)
{
	lb->Clear();
    for(size_t i = 0; i < items.count(); i++)
    {
        lb->Items->Add(items[i].c_str());
    }
}

int __fastcall populateDropDown(set<string>& files, TComboBox *CB)
{
	String sItem;
    if(CB->ItemIndex != -1)
    {
    	sItem = CB->Items->Strings[CB->ItemIndex];
    }
    CB->Clear();

    set<string>::iterator it = files.begin();
    for (; it != files.end(); ++it)
    {
        string file  = getFileNameNoExtension(*it);
        CB->Items->Add(file.c_str());
    }
    return CB->Items->IndexOfName(sItem);
}

int __fastcall populateDropDown(StringList& items, TComboBox *CB, const string& selectItem)
{
    //Instead of clearing, we could add and remove items on a per item basis instead
    CB->Clear();
    for (size_t i = 0; i <  items.size(); ++i)
    {
        string item  = items[i];
        CB->Items->Add(item.c_str());
    }

    return CB->Items->IndexOf(selectItem.c_str());
}

//int __fastcall VCLCOMMON spawnProcess(const string& path, const string& exeName)
//{
//    FileName exe(exeName, path);
//    dslProcess process(exe);
//    process.Create();
//    process.Run();
//    return process.PID();
//}


void __fastcall findFilesInDirectory(const string &directory, const string& Extension, const bool& searchSubFolders, list<string>& excludeDirs, list<string>& fileList, bool& terminate)
{

//Replace this with POCO

//    // This method searches the directory specified by the parameter and all
//    // of its subdirectories for the file matching the value in SearchCustomEdit.
//    // The directory name is assumed to end with a backslash.
//
//    WIN32_FIND_DATA filedata ;  // Structure for file data
//    HANDLE filehandle ;         // Handle for searching
//
//    // Pass 1 - Search for the files within the directory.
//    #if defined(_UNICODE)
//        wstring tempFilter = wstdstr(directory + Extension);
//        wstring searchFilter(tempFilter.c_str());
//    #else
//        string searchFilter(directory + Extension);
//    #endif
//
//    filehandle = FindFirstFile (searchFilter.c_str(), &filedata);
//    if (filehandle != INVALID_HANDLE_VALUE)
//    {
//        do
//        {
//            if(terminate)
//            {
//              	FindClose (filehandle);
//                return;
//            }
//            //Don't append the file if the file is a directory
//            if((filedata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)
//            {
//            	string fldr = (directory) + (stdstr (filedata.cFileName));
//                fileList.push_back(fldr);
//            }
//        }
//        while (FindNextFile (filehandle, &filedata));
//        FindClose (filehandle) ;
//    }
//
//    // Pass 2 - Search for subdirectories within this directory
//    if(searchSubFolders)
//    {
//        string dir = directory + "*.*" ;
//        #if defined(_UNICODE)
//            filehandle = FindFirstFile (vclstr(directory + "*.*").c_str (), &filedata) ;
//        #else
//            filehandle = FindFirstFile ((directory + "*.*").c_str (), &filedata) ;
//        #endif
//        if (filehandle != INVALID_HANDLE_VALUE)
//        {
//          	do
//          	{
//                if(terminate)
//                {
//                   	FindClose (filehandle) ;
//                    return;
//                }
//
//            	if ((filedata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0
//                 	&& String (filedata.cFileName) != "."
//                 	&& String (filedata.cFileName) != "..")
//            	{
//					// Recursive call here
//                    //Don't do it if the dir is in the don't search list box
//                	string theDir = stdstr(filedata.cFileName);
//                    if(find(excludeDirs.begin(), excludeDirs.end(), theDir) != excludeDirs.end())
//                    {
//                       //Skip this
//                    }
//                    else
//                    {
//              			string subFolder = directory + stdstr(String(filedata.cFileName) + "\\");
//
//                        //RECURSIVE call here
//                    	findFilesInDirectory(subFolder, Extension, searchSubFolders, excludeDirs, fileList, terminate);
//              		}
//            	}
//          	}
//            while (FindNextFile (filehandle, &filedata)) ;
//          	FindClose (filehandle) ;
//		}
//	}
//    return;
}

//Rich Edit
//---------------------------------------------------------------------------
void __fastcall SetTabStops(TRichEdit* rEdit, double tabSize)
{
	vector<double> tabStops;
    tabStops.resize(MAX_TAB_STOPS);
    for(size_t i = 1; i < tabStops.size() -1; i++)
    {
    	tabStops[i-1] = tabSize*i;
    }

    rEdit->SelectAll();
    TParaFormat pf = {};
    pf.cbSize = sizeof( pf );
    pf.dwMask = PFM_TABSTOPS;
    pf.cTabCount = MAX_TAB_STOPS;

    for(int i= 0; i < pf.cTabCount; i++)
    {
        pf.rgxTabs[i] = tabStops[i] * 1440;
    }
    rEdit->Perform(EM_SETPARAFORMAT, 0, (int) &pf);
}

bool __fastcall centerControl(TControl* control)
{
    if(!control || !control->Parent)
    {
        return false;
    }
    control->Top    = (control->Parent->Height - control->Height) /2;
    control->Left   = (control->Parent->Width -  control->Width) / 2;
    return true;
}

}//Namespace

