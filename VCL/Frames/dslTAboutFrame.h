#ifndef dslTAboutFrameH
#define dslTAboutFrameH
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <ImgList.hpp>
#include <System.Actions.hpp>
#include <System.ImageList.hpp>
#include "dslTURLLabel.h"
//---------------------------------------------------------------------------
class PACKAGE TAboutFrame : public TFrame
{
__published:    // IDE-managed Components
    TPanel *Panel1;
    TLabel *Label3;
    TLabel *ProgramLabel;
    TLabel *Label2;
    TURLLabel *webUrl;
    TURLLabel *mailURL;
    TLabel *Label1;
    TMemo *verMemo;
    TBitBtn *mHomeBtn;
    TBitBtn *mMailBtn;
    TImage *Image1;
    TPanel *Panel2;
    TActionList *ActionList1;
    TAction *GoHomeA;
    TAction *SendMailA;
    TImageList *ImageList1;
    TMemo *mMiscInfoMemo;
    void __fastcall GoHomeAExecute(TObject *Sender);
    void __fastcall mMailBtnClick(TObject *Sender);
    void __fastcall mHomeBtnClick(TObject *Sender);
private:    // User declarations
public:        // User declarations
    __fastcall TAboutFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAboutFrame *AboutFrame;
//---------------------------------------------------------------------------
#endif
