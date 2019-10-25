#pragma hdrstop
#include <string>
#include <vector>
#include <sstream>
#include <Dialogs.hpp>
#include "dslTAboutForm.h"
#include "dslStringUtils.h"
#include "dslVCLUtils.h"
#include "dslApplicationInfo.h"
#include "dslVersion.h"
//#include "TCreditsForm.h"
#include "pngimage.hpp"
#pragma package(smart_init)
#pragma resource "*.dfm"

using namespace std;
using namespace dsl;
using namespace Poco;
TAboutForm *AboutForm;

//---------------------------------------------------------------------
__fastcall TAboutForm::TAboutForm(TComponent *Owner, ApplicationLicenseController& licenseController)
:
TForm(Owner),
mLicenseController(licenseController)
{
//    long style = GetWindowLong(verMemo->Handle, GWL_STYLE);
//    style = style | WS_DISABLED;
//    SetWindowLong(verMemo->Handle,GWL_STYLE, style);
}

__fastcall TAboutForm::~TAboutForm()
{}

void __fastcall TAboutForm::FormCreate(TObject *Sender)
{
    dslApplicationInfo appInfo(Application);
    stringstream strs;

    Version version(stdstr(appInfo.mVersion));
    strs <<version.getMajor()<<"."<<version.getMinor()<<"."<<version.getPatch();
    String versionMajorMinorPatch(strs.str().c_str());

    this->Caption = "About " + vclstr(appInfo.mProductName);
    ProgramLabel->Caption = vclstr(appInfo.mProductName) + String(" Version: ") + versionMajorMinorPatch;

    strs.str("");
    verMemo->Clear();

    strs <<"Product Name:\t"<<stdstr(appInfo.mProductName)<<endl;
    strs <<"Build Version:\t"<<stdstr(appInfo.mVersion)<<endl;
    strs <<"Build Date:\t"<<__DATE__<<endl;
    strs <<"Build Time:\t"<<__TIME__<<endl;
    vector<string> strings = splitString(strs.str(), "\n");

    for(unsigned int i = 0; i < strings.size(); i++)
    {
        verMemo->Lines->Add(strings[i].c_str());
    }
}

//---------------------------------------------------------------------------
void __fastcall TAboutForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if(Key == VK_ESCAPE)
        Close();
}

//---------------------------------------------------------------------------
void __fastcall TAboutForm::OKButtonClick(TObject *Sender)
{
    Application->OnIdle = nullptr;
    Close();
}

//---------------------------------------------------------------------------
void __fastcall TAboutForm::FormClose(TObject *Sender, TCloseAction &Action)
{
    Application->OnIdle = nullptr;
}

//---------------------------------------------------------------------------
void __fastcall TAboutForm::GoHomeAExecute(TObject *Sender)
{
    webUrl->ClickMe();
}

void __fastcall TAboutForm::creditsButtonClick(TObject *Sender)
{
//    TResourceStream *rStream = nullptr;
//    TStringList *sList 		= nullptr;
//    TPngImage   *pngImage	= nullptr;
//
//    try
//    {
//        rStream     = new TResourceStream(mMainFormHandle, "CREDITS", RT_RCDATA);
//        sList       = new TStringList;
//
//        sList->LoadFromStream(rStream, TEncoding::UTF8);
//
//        //Open the credits form
//        TCreditsForm* credits = new TCreditsForm(nullptr);
//
//        for(int i = 0; i < sList->Count; i++)
//        {
//            String line;
//            line =  sList->Strings[i];
//            credits->creditsMemo->Lines->Add(line);
//        }
//
////        pngImage    = new TPngImage;
////        pngImage->LoadFromResourceName(mMainFormHandle, "APP_IMAGE");
////        credits->creditsImage->Picture->Graphic = pngImage;
//        credits->creditsImage->Picture = this->mCreditsImage->Picture;
//
//        credits->ShowModal();
//    }
//    catch(...)
//    {
//        delete sList;
//        delete pngImage;
//        delete rStream;
//        return;
//    }
//
//    delete sList;
//    delete pngImage;
//    delete rStream;
}


void __fastcall TAboutForm::FormShow(TObject *Sender)
{
    stringstream ss;
    //Setup license info
    if(mLicenseController.getLicenseMode() == lmTrial)
    {
        ProdLicenseLbl->Caption = "Trial mode license";

        ss<<"This product is executing under a Trial Mode License\n";
        ss<<" \n \nThere are "
        <<Poco::DateTimeFormatter::format(mLicenseController.getTrialPeriodLeft(), "%d")
        <<" days left out of a "
        <<Poco::DateTimeFormatter::format(mLicenseController.getTrialPeriod(), "%d")
        <<" days trial";

        StringList lines(ss.str(), '\n');
        for(dsluint i = 0; i < lines.count(); i++)
        {
            licenseMemo->Lines->Add(lines[i].c_str());
        }
    }

    ss.str("");
    if(mLicenseController.hasExpirationDate())
    {
        expirationLabel->Visible = true;
        ss<<"This product is a pre-release version and will expire on "<<Poco::DateTimeFormatter::format(mLicenseController.getExpirationDate(), "%b %e, %Y");
        expirationLabel->Caption = vclstr(ss.str());
    }


}
//---------------------------------------------------------------------------

