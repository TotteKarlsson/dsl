#ifndef TMDIChildH
#define TMDIChildH
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//#include <Dialogs.hpp>
#include <ComCtrls.hpp>
#include "TRegistryForm.h"
#include "dslNotifyEventList.h"
//---------------------------------------------------------------------------

namespace dsl
{
class File;
}

class mtkNotifyEventList;
class TMainForm;
using std::string;
class mtkAppInfo;

class PACKAGE TMDIChild : public TForm
{
    __published:
        void                    __fastcall         FormActivate(TObject *Sender);

    private:
        mtkAppInfo*                                appInfo;
        static int                                 mMDICount;


    public:
        TStatusBar                                 *sBar;
//        dsl::File                                  *aFile;
        TApplication                               *application;
        mtkNotifyEventList                         *mLastChildIsClosingEventList;
        TMainForm                                  *parent;

                                __fastcall         TMDIChild(TApplication* app, const string& caption, const String& name);
        virtual                 __fastcall        ~TMDIChild();

        void                                       SetStatusBar(TStatusBar *sb);
        TStatusBar*                                StatusBar();
//        dsl::File*                                 GetFile();
        virtual void            __fastcall         LastBaseChildIsClosingEvent();
        virtual void            __fastcall         UpdateStatusBar();
        virtual string          __fastcall         GetName();
        virtual bool            __fastcall         Read(const string& fName) = 0;         //Re Implement!!
        virtual bool            __fastcall         Write(const string& fName) = 0;
        virtual void            __fastcall         ResetWindow();
        virtual bool                               ReloadFromFile();
        virtual bool                               IsEmpty();

        mtkNotifyEventList                         mNotifyOnActivate;
        mtkNotifyEventList                         mNotifyOnClosing;
        bool                                       mCanClose;

        __property mtkNotifyEventList*             LastBaseChildIsClosingEventList = {read=mLastChildIsClosingEventList};
};

extern PACKAGE TMDIChild *MDIChild;
#endif
