#ifndef dslTAboutFormH
#define dslTAboutFormH
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <StdCtrls.hpp>
#include <Controls.hpp>
#include <Forms.hpp>
#include <Graphics.hpp>
#include <Classes.hpp>
#include <Windows.hpp>
#include <System.hpp>
#include "dslTURLLabel.h"
#include <ComCtrls.hpp>
#include <ActnList.hpp>
#include <ImgList.hpp>
#include <System.Actions.hpp>
#include "dslApplicationLicenseController.h"
#include <System.ImageList.hpp>
using dsl::ApplicationLicenseController;

//---------------------------------------------------------------------------
class PACKAGE TAboutForm : public TForm
{
__published:
    TLabel *Label2;
    TPanel *Panel2;
    TMemo *verMemo;
    TLabel *Label5;
    TLabel *ProgramLabel;
    TURLLabel *webUrl;
    TImageList *ImageList1;
    TActionList *ActionList1;
    TAction *GoHomeA;
    TStatusBar *StatusBar1;
    TImage *mImage;
    TButton *creditsButton;
    TImage *mCreditsImage;
    TLabel *ProdLicenseLbl;
    TMemo *licenseMemo;
    TLabel *expirationLabel;
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall OKButtonClick(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall GoHomeAExecute(TObject *Sender);
    void __fastcall creditsButtonClick(TObject *Sender);
    void __fastcall FormShow(TObject *Sender);

private:
    ApplicationLicenseController&       mLicenseController;

public:
                __fastcall              TAboutForm(TComponent *Owner, ApplicationLicenseController& licenseController);
                __fastcall              ~TAboutForm();


    unsigned                            mMainFormHandle;
};

extern PACKAGE TAboutForm *AboutForm;
#endif
