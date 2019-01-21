#include <vcl.h>
#pragma hdrstop
#include "dslStringUtils.h"
#include "dslVCLUtils.h"
#include "dslApplicationInfo.h"
#include "dslTAboutFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAboutFrame *AboutFrame;

using namespace dsl;
using namespace std;

//---------------------------------------------------------------------------
__fastcall TAboutFrame::TAboutFrame(TComponent* Owner)
    : TFrame(Owner)
{
    dslApplicationInfo appInfo(Application);

    this->Caption 			= vclstr("About " + appInfo.mProductName);
    ProgramLabel->Caption 	= vclstr(appInfo.mProductName);

    verMemo->Clear();
    stringstream strs;
    strs <<"Product Name:\t"<<stdstr(appInfo.mProductName)<<endl;
    strs <<"Build Version:\t"<<stdstr(appInfo.mVersion)<<endl;
    strs <<"Build Date:\t"<<__DATE__<<endl;
    strs <<"Build Time:\t"<<__TIME__<<endl;
    vector<string> strings = splitString(strs.str(), "\n");

    for(int i = 0; i < strings.size(); i++)
    {
        verMemo->Lines->Add(strings[i].c_str());
    }

}
//---------------------------------------------------------------------------
void __fastcall TAboutFrame::GoHomeAExecute(TObject *Sender)
{
    webUrl->ClickMe();
}
//---------------------------------------------------------------------------
void __fastcall TAboutFrame::mMailBtnClick(TObject *Sender)
{
    mailURL->ClickMe();
}
//---------------------------------------------------------------------------

void __fastcall TAboutFrame::mHomeBtnClick(TObject *Sender)
{
    webUrl->ClickMe();
}
//---------------------------------------------------------------------------
