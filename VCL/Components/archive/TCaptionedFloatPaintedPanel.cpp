
#pragma hdrstop
//---------------------------------------------------------------------------
#include "TCaptionedFloatPaintedPanel.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TCaptionedFloatPaintedPanel::TCaptionedFloatPaintedPanel(TComponent* Owner)
    :
    TPaintedPanel(Owner),
    FValueLeft(7),
    FValueTop(27),
    mCaptionColor(-1)
{
    this->Color = clMoneyGreen;
    this->ParentBackground = true;
    this->Width = 118;
    this->Height = 57;

    FCaption                    = new TLabel(this);
    FCaption->Caption           = "<none>";
    FCaption->Parent            = this;
    FCaption->Align             = alTop;
    FCaption->Width             = this->Width;
    FCaption->Alignment         = taCenter;
    FCaption->Caption           = this->Caption;//"My Label";

    ///// The Value
    FFloatLabel                 = new dslFloatLabel(this);
    FFloatLabel->Parent         = this;
    FFloatLabel->Alignment      = taLeftJustify;
    FFloatLabel->Top            = FValueTop;
    FFloatLabel->Left           = FValueLeft;

    FFloatLabel->OnClick        = &ValueClicked;
    FCaption->OnClick           = &ValueClicked;
}
//---------------------------------------------------------------------------
__fastcall TCaptionedFloatPaintedPanel::~TCaptionedFloatPaintedPanel()
{
    delete FCaption;
    delete FFloatLabel;
}

void __fastcall TCaptionedFloatPaintedPanel::Enable(bool doWhat)
{
    if(mCaptionColor == -1)
    {
        mCaptionColor = FCaption->Font->Color ;
        mValueColor = FFloatLabel->Font->Color;
    }

    if(doWhat == false)
    {

        FCaption->Font->Color   = clGrayText;
        FFloatLabel->Font->Color  = clGrayText;

        this->Enabled = false;
    }
    else
    {
        FCaption->Font->Color = mCaptionColor;
        FFloatLabel->Font->Color = mValueColor;
        this->Enabled = true;
    }
}

void __fastcall TCaptionedFloatPaintedPanel::ValueClicked(TObject *Sender)
{
    if( FOnValueClick )
    {
        FOnValueClick(this);
    }
}

//---------------------------------------------------------------------------
void __fastcall TCaptionedFloatPaintedPanel::SetValueLabelLeft(int left)
{
    FValueLeft              = left;
    FFloatLabel->Left       = FValueLeft;
}

void __fastcall TCaptionedFloatPaintedPanel::SetValueLabelTop(int top)
{
    FValueTop           = top;
    FFloatLabel->Top    = FValueTop;
}

String __fastcall TCaptionedFloatPaintedPanel::GetLabelCaption()
{
    return (FCaption) ? FCaption->Caption : String("<none>");
}

void __fastcall TCaptionedFloatPaintedPanel::SetLabelCaption(String aString)
{
    if(FCaption)
    {
        FCaption->Caption = aString;
    }
}

String __fastcall TCaptionedFloatPaintedPanel::GetValueCaption()
{
    return FValueCaption;
}

void __fastcall TCaptionedFloatPaintedPanel::SetValueCaption(String aString)
{
    FValueCaption = aString;
    if(FFloatLabel)
    {
        FFloatLabel->SetValueString(FValueCaption);
    }
}

double __fastcall TCaptionedFloatPaintedPanel::GetValue()
{
    return (FFloatLabel) ? FFloatLabel->GetValue() : 0;
}

void __fastcall TCaptionedFloatPaintedPanel::SetValue(double number)
{
    if(FFloatLabel)
    {
        FFloatLabel->SetValue(number);
    }
}

//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TCaptionedFloatPaintedPanel *)
{
    new TCaptionedFloatPaintedPanel(nullptr);
}

namespace Tcaptionedfloatpaintedpanel
{
    void __fastcall PACKAGE Register()
    {
         TComponentClass classes[1] = {__classid(TCaptionedFloatPaintedPanel)};
        RegisterComponents(dslComponents::gDuneEditPanels, classes, 0);
    }
}


