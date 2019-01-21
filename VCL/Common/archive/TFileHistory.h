#ifndef TFileHistoryH
#define TFileHistoryH
#include <menus.hpp>
#include "dslStringList.h"
#include "dslObject.h"

namespace dsl
{
    class IniFile;
}

using dsl::DSLObject;
using dsl::IniFile;
using std::string;

//typedef __closure OnClickHandler
typedef void __fastcall (__closure *OnClickHandler)(System::TObject* Sender);
//---------------------------------------------------------------------------
class PACKAGE TFileHistory : public DSLObject
{
    public:

                                                    TFileHistory(int maxItems, TMenuItem* rootMeny = nullptr,  TMenuItem *topSeperator = nullptr);
                                                    ~TFileHistory();

                                                    //Function for menu item click event handlers to call
        TMenuItem*                                  append(const string& menuItem);
        void                                        maintain();
        TMenuItem*                                  getLastMenuItem();
        int                                         count();
        TMenuItem*                                  operator[](int i);
        TMenuItem*                                  getMenuItem(const string& name);
        TMenuItem*                                  getMenuItem(int i);

        string                                      getFileName(int i);
        string                                      getFileName(TMenuItem* item);
        TMenuItem*                                  insertAtTop(const string& menuItem);
        bool                                        remove(const string& name);
        bool                                        remove(TMenuItem* item);
        void                                        setMaxNumberOfHistoryItems(int count);
        int                                         getMaxNumberOfHistoryItems();
        bool                                        load(IniFile* aIniFile, const string& section, OnClickHandler clickHandler);
        bool                                        save(IniFile* aIniFile, const string& section);
        void                                        clear();

    private:
                                                    //The menu item to add history to
        TMenuItem*                                  mRootMenuItem;

                                                    //Holds maximum number of history items allowed
        int                                         mMaxHistoryItems;

                                                    // Menu seperators that will mark the beginning and end of the history
        TMenuItem*                                  mTopSeparator;
        TMenuItem*                                  mBottomSeparator;

                                                    //Function that rebuilds the history list
        void                                        rebuildHistory();

};

extern PACKAGE TFileHistory *FileHistory;
#endif
