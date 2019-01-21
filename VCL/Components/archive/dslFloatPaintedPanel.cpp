
#pragma hdrstop
//---------------------------------------------------------------------------
#include "dslFloatPaintedPanel.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall dslFloatPaintedPanel::dslFloatPaintedPanel(TComponent* Owner)
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
__fastcall dslFloatPaintedPanel::~dslFloatPaintedPanel()
{
    delete FCaption;
    delete FFloatLabel;
}

void __fastcall dslFloatPaintedPanel::ShowEnabled(bool what)
{
    this->Enabled = what;
    if(what)
    {
        mValueColor = clWhite;
    }
    else
    {
        mValueColor = clGray;
    }
}

void __fastcall dslFloatPaintedPanel::SetReference(double& val)
{
    if(FFloatLabel)
        FFloatLabel->SetReference(val);
}

void __fastcall dslFloatPaintedPanel::SetValueReference(double& val)
{
    if(FFloatLabel)
        FFloatLabel->SetReference(val);
}

void __fastcall dslFloatPaintedPanel::SetNrOfDecimals(int decimals)
{
    if(FFloatLabel)
    {
        FFloatLabel->SetNrOfDecimals(decimals);
    }
}

void __fastcall dslFloatPaintedPanel::UpdateFromValue()
{
    FFloatLabel->UpdateFromValue();
}

int __fastcall dslFloatPaintedPanel::GetNrOfDecimals()
{
    return FFloatLabel ? FFloatLabel->NrOfDecimals : 2;
}

TFont* __fastcall dslFloatPaintedPanel::GetCaptionFont()
{
    return FCaption ? FCaption->Font : nullptr;
}

void __fastcall dslFloatPaintedPanel::SetCaptionFont(TFont* aFont)
{
    FCaption->Font = aFont ? aFont : nullptr;
}

TFont* __fastcall dslFloatPaintedPanel::GetValueFont()
{
    return FFloatLabel ? FFloatLabel->Font : nullptr;
}

void __fastcall dslFloatPaintedPanel::SetValueFont(TFont* aFont)
{
    FFloatLabel->Font = aFont ? aFont : nullptr;
}

void __fastcall dslFloatPaintedPanel::Enable(bool doWhat)
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

void __fastcall dslFloatPaintedPanel::ValueClicked(TObject *Sender)
{
    if( FOnValueClick )
    {
        FOnValueClick(this);
    }
}

//---------------------------------------------------------------------------
void __fastcall dslFloatPaintedPanel::SetValueLabelLeft(int left)
{
    FValueLeft              = left;
    FFloatLabel->Left       = FValueLeft;
}

void __fastcall dslFloatPaintedPanel::SetValueLabelTop(int top)
{
    FValueTop           = top;
    FFloatLabel->Top    = FValueTop;
}

String __fastcall dslFloatPaintedPanel::GetLabelCaption()
{
    return (FCaption) ? FCaption->Caption : String("<none>");
}

void __fastcall dslFloatPaintedPanel::SetLabelCaption(String aString)
{
    if(FCaption)
    {
        FCaption->Caption = aString;
    }
}

String __fastcall dslFloatPaintedPanel::GetValueCaption()
{
    return FValueCaption;
}

void __fastcall dslFloatPaintedPanel::SetValueCaption(String aString)
{
    FValueCaption = aString;
    if(FFloatLabel)
    {
        FFloatLabel->SetValueString(FValueCaption);
    }
}

double __fastcall dslFloatPaintedPanel::GetValue()
{
    return (FFloatLabel) ? FFloatLabel->GetValue() : 0;
}

void __fastcall dslFloatPaintedPanel::SetValue(double number)
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

static inline void ValidCtrCheck(dslFloatPaintedPanel *)
{
    new dslFloatPaintedPanel(nullptr);
}

namespace Mtkfloatpaintedpanel
{
    void __fastcall PACKAGE Register()
    {
         TComponentClass classes[1] = {__classid(dslFloatPaintedPanel)};
        RegisterComponents(dslComponents::gDuneEditPanels, classes, 0);
    }
}


