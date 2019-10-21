#ifndef dslVCLUtilsH
#define dslVCLUtilsH
#include <VCL.CheckLst.hpp>
#include <VCL.Grids.hpp>
#include <VCL.ActnCtrls.hpp>
#include <VCL.ActnMenus.hpp>
#include <set>
#include <list>
#include <sstream>
#include "dslUtils.h"
#include "dslApplicationLicenseController.h"
#include "dslVCLCommonExporter.h"
#include "dslWin32Utils.h"
#include "dslStringList.h"
namespace dsl
{

    //Todo: remove all __fastcall
	using std::string;
	using std::list;
	using std::wstring;
	using std::set;
    using std::ostringstream;
    TRect 						   VCLCOMMON getStretchedDimensions(int width, int height, int maxWidth, int maxHeight);
    bool 				__fastcall VCLCOMMON sortTListBoxNumerically(TListBox* lb);
	void 				__fastcall VCLCOMMON populateStyleMenu(TMenuItem* ThemesMenu, TNotifyEvent ThemesMenuClick);
	void 				__fastcall VCLCOMMON populateStyleRG(TRadioGroup* ThemesCB);
	string				__fastcall VCLCOMMON joinPathU(const string& f1, const string& f2, const UnicodeString& f3);
	string				__fastcall VCLCOMMON joinPathU(const string& f1, const UnicodeString& f2);
//	bool 				__fastcall VCLCOMMON sendApplicationMessage(TApplication* Application, long msg, long data1 = 0, long data2 = 0);

	string              __fastcall VCLCOMMON createWindowTitle(const string& appName, TApplication* app);
	string              __fastcall VCLCOMMON createWindowTitle(const string& appName, TApplication* app, ApplicationLicenseController& lc);
	bool                __fastcall VCLCOMMON clearStringGrid(TStringGrid* grid);
	String              __fastcall VCLCOMMON vclstr(const string& s);
	String              __fastcall VCLCOMMON vclstr(const char* s);
	String              __fastcall VCLCOMMON vclstr(const AnsiString& s);
    String              __fastcall VCLCOMMON vclstr(const ostringstream& s);


    string              __fastcall VCLCOMMON stdstr(const String& str);
	string              __fastcall VCLCOMMON stdstr(const UnicodeString& s);

    String              __fastcall VCLCOMMON vclstr(const ostringstream& s);

    string              __fastcall VCLCOMMON readStringFromRegistry(const string& regRoot, const string& section, const string& key, const string& def = gEmptyString);
    bool                __fastcall VCLCOMMON writeStringToRegistry(const string& regRoot, const string& section, const string& key, const string& value);

    //CheckList Boxes
    StringList          __fastcall VCLCOMMON getCheckedItems(TCheckListBox* listBox);
	int					__fastcall VCLCOMMON getNumberOfCheckedItems(TCheckListBox* lb);
    void                __fastcall VCLCOMMON addItemsToCheckListBox(const StringList& items, TCheckListBox *lb, bool checked = false);
    void                __fastcall VCLCOMMON addCheckedUncheckedItemsToCheckListBox(const StringList& items, TCheckListBox *lb);

    //ListBoxes
    void                __fastcall VCLCOMMON populateListBox(const StringList& items, TListBox *lb);
    StringList          __fastcall VCLCOMMON getStrings(TListBox *lb);
	StringList          __fastcall VCLCOMMON getStrings(TCheckListBox *lb);
    void                __fastcall VCLCOMMON populateCheckListBox(const StringList& items, TCheckListBox *lb);
    int                 __fastcall VCLCOMMON populateDropDown(set<string>& files, TComboBox *CB);
	int                 __fastcall VCLCOMMON populateDropDown(StringList& items, TComboBox *CB, const string& selectItem = gEmptyString);

	//TMemo
    StringList          __fastcall VCLCOMMON getStrings(TMemo* memo);

    vector<string>      __fastcall VCLCOMMON stdlines(TStrings* lines);
//    wstring             __fastcall VCLCOMMON ToWStdString(const string& str);

    bool                __fastcall VCLCOMMON isExecutedInProgramFiles();

    string              __fastcall VCLCOMMON getProductVersion(TApplication* app);
    string              __fastcall VCLCOMMON getProductName(TApplication* app);
    string              __fastcall VCLCOMMON getProductRegistryRoot(TApplication* app);
    string              __fastcall VCLCOMMON getApplicationPath();
    string              __fastcall VCLCOMMON getApplicationName();
    string              __fastcall VCLCOMMON getApplicationNameW();


//    string              __fastcall VCLCOMMON getSpecialFolder(int fldr);
    String              __fastcall VCLCOMMON GetCWD();
    bool                __fastcall VCLCOMMON SetCWD(const string& wd);
	void                __fastcall VCLCOMMON enableDisablePageControl(TPageControl *p, bool bEnabled);
	void                __fastcall VCLCOMMON enableDisablePanel(TPanel *p, bool bEnabled);
    void                __fastcall VCLCOMMON enableDisableGroupBox(TGroupBox *GB, bool bEnabled);

    void                __fastcall VCLCOMMON EnableDisableForm(TForm *f, bool bEnabled);
    void                __fastcall VCLCOMMON EnableDisableFrame(TFrame *f, bool bEnabled);

    void                __fastcall VCLCOMMON EnableDisableComponent(TComponent *f, bool bEnabled);
    void                __fastcall VCLCOMMON EnableDisableCControl(TCustomControl *GB, bool bEnabled);

	void                __fastcall VCLCOMMON EnableDisableActions(TActionList *aL, bool bEnabled);
    TStringList*        __fastcall VCLCOMMON GetFilesInDir(const String& folder, const String& fileExtension);
    int                 __fastcall VCLCOMMON GetNrOfFilesInDir(const String& path, const String& searchMask);
    String              __fastcall VCLCOMMON BrowseForDir(void* handle);
	string 				__fastcall VCLCOMMON browseForFolder(const string& startFolder = gEmptyString);
	string 				__fastcall VCLCOMMON browseForFile(const string& startFolder = gEmptyString);
    String              __fastcall VCLCOMMON BrowseForFile(void* handle);
    void                __fastcall VCLCOMMON ShutDownWindows(int operation);
    bool                __fastcall VCLCOMMON IsDirectory(const string & path);

    //Action tool bar functions
    void                __fastcall VCLCOMMON RemoveActionsFromActionToolBar(TCustomActionList* list, TActionToolBar *actionToolBar);
    void                __fastcall VCLCOMMON AddActionsToActionManager(TCustomActionList* actionList, const String& caption, TActionManager *actionManager);
    void                __fastcall VCLCOMMON RemoveActionsFromActionManager(TCustomActionList* actionList, TActionManager *actionManager);
    TActionToolBar*     __fastcall VCLCOMMON CreateActionToolBar(const string& caption, TActionManager *actionManager, TWinControl* parent);
	void                __fastcall VCLCOMMON RemoveActionsFromActionMainMenu(TCustomActionList* actionList, TActionMainMenuBar* mainMenu)	;

    int                 __fastcall VCLCOMMON spawnProcess(const string& path, const string& exeName);
//    String              __fastcall VCLCOMMON getLastWin32Error();
    ostream&            __fastcall VCLCOMMON operator << (ostream& stream, const String& aString);

    //Win32
    void                __fastcall VCLCOMMON findFilesInDirectory(const string &directory, const string& Extension, const bool& searchSubFolders, list<string>& excludeDirs, list<string>& fileList, bool& terminate);

    //Rich Edit
    void                __fastcall VCLCOMMON SetTabStops(TRichEdit* edit, double tabSize);

    //Positioning
    bool                __fastcall VCLCOMMON centerControl(TControl* control);

}
#endif
