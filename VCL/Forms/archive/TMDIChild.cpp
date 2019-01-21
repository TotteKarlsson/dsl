#pragma hdrstop
#include "TMDIChild.h"
//#include "dslFile.h"
#include "dslNotifyEventList.h"
#include "dslStringUtils.h"
#include "dslUserMessages.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TRegistryForm"
#pragma resource "*.dfm"
TMDIChild *MDIChild;

using namespace dsl;

int TMDIChild::mMDICount = 0;
//---------------------------------------------------------------------------
__fastcall TMDIChild::TMDIChild(TApplication* app, const string& caption, const String& regSection)
:
TForm(Owner),
//TRegistryForm(app, regSection),
appInfo(nullptr),
//aFile(new File("")),
application(app),
mCanClose(true)
{
    this->Caption = (caption.c_str());
    mMDICount++;

    mLastChildIsClosingEventList = new dslNotifyEventList();
}

//---------------------------------------------------------------------------
__fastcall TMDIChild::~TMDIChild()
{
    mMDICount--;
    if(mMDICount < 1)
    {
        mLastChildIsClosingEventList->NotifyClients(0);
    }
    delete mLastChildIsClosingEventList;
//      delete aFile;
}

//---------------------------------------------------------------------------//---------------------------------------------------------------------------
void __fastcall TMDIChild::LastBaseChildIsClosingEvent()
{
    mLastChildIsClosingEventList->NotifyClients(nullptr);
}

////---------------------------------------------------------------------------
//File* TMDIChild::GetFile()
//{
//    if(aFile == nullptr)
//        aFile = new File("");
//    return aFile;
//}

//---------------------------------------------------------------------------
void __fastcall TMDIChild::UpdateStatusBar()
{
//  String str;
//    str = dslGetFileName(GetFile()->GetFileName()).c_str();
////  sBar->Panels->Items [FILE_NAME]->Text = str;
//
//  str = dslDataFormatToStr(GetFile()->DataFormat()).c_str();
////  sBar->Panels->Items [DATAFORMAT]->Text = str;
//
//  str = dslFileFormatToStr(GetFile()->FileFormat()).c_str();
////  sBar->Panels->Items [FILEFORMAT]->Text = str;
//
////  if(GetData()->IsModified())
////    str = "Modified";
////  else
////    str = "Unmodified";
//  sBar->Panels->Items[MODIFIED]->Text = str;
}

//---------------------------------------------------------------------------
void __fastcall TMDIChild::FormActivate(TObject *Sender)
{
    HWND hWnd = Application->MainForm->Handle;
    if(SendMessage(hWnd, UWM_MDICHILDONACTIVATE, 0, 0))
    {
        Log(lError)<<"Sending message from TMDIChild was unsuccesful";
    }

    mNotifyOnActivate.NotifyClients(Sender);
}



bool                                        TMDIChild::ReloadFromFile(){return false;}
void                                     TMDIChild::SetStatusBar(TStatusBar *sb){sBar= sb;}
TStatusBar*                             TMDIChild::StatusBar(){return sBar;}
string                 __fastcall     TMDIChild::GetName(){return nullptr;}
void                 __fastcall     TMDIChild::ResetWindow(){}
bool                                TMDIChild::IsEmpty(){return true;}
