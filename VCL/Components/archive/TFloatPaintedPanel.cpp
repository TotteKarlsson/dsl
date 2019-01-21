
#pragma hdrstop
//---------------------------------------------------------------------------
#include "TFloatPaintedPanel.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TFloatPaintedPanel::TFloatPaintedPanel(TComponent* Owner)
:
TPaintedPanel(Owner),
FLabel(new dslFloatLabel(this)),
FValueCaption(L"10"),
FValueLabelAlign(alClient),
FValueLabelAlignment(taCenter),
FValueLabelLayout(tlCenter),
FNrOfDecimals(2),
FValueTop(27),
FValueLeft(7)
{
    // The Value
    FLabel->Parent         = this;
    FLabel->Align          = FValueLabelAlign;
    FLabel->Alignment      = FValueLabelAlignment;
    FLabel->Layout         = FValueLabelLayout;
    FLabel->Top            = FValueTop;
    FLabel->Left           = FValueLeft;
    FLabel->OnClick        = &ValueClicked;
    FLabel->SetValueString(FValueCaption);
    FLabel->SetNrOfDecimals(FNrOfDecimals);
    FLabel->UpdateFromValue();
}
//---------------------------------------------------------------------------
__fastcall TFloatPaintedPanel::~TFloatPaintedPanel()
{
    delete FLabel;
}

void __fastcall TFloatPaintedPanel::Enable(bool doWhat)
{
    if(doWhat == false)
    {
        FLabel->Font->Color  = clGrayText;
        this->Enabled = false;
    }
    else
    {
        FLabel->Font->Color = mValueColor;
        this->Enabled = true;
    }
}

void __fastcall TFloatPaintedPanel::ValueClicked(TObject *Sender)
{
    if( FOnValueClick )
    {
        FOnValueClick(this);
    }
}

//---------------------------------------------------------------------------
void __fastcall TFloatPaintedPanel::SetValueLabelLeft(int left)
{
    FValueLeft              = left;
    FLabel->Left       = FValueLeft;
}

void __fastcall TFloatPaintedPanel::SetValueLabelTop(int top)
{
    FValueTop           = top;
    FLabel->Top    = FValueTop;
}

String __fastcall TFloatPaintedPanel::GetValueCaption()
{
    return FValueCaption;
}

void __fastcall TFloatPaintedPanel::SetValueCaption(String aString)
{
    FValueCaption = aString;
    if(FLabel)
    {
        FLabel->SetValueString(FValueCaption);
    }
}

double __fastcall TFloatPaintedPanel::GetValue()
{
    return (FLabel) ? FLabel->GetValue() : 0;
}

void __fastcall TFloatPaintedPanel::SetValue(double number)
{
    if(FLabel)
    {
        FLabel->SetValue(number);
    }
}

//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
static inline void ValidCtrCheck(TFloatPaintedPanel *)
{
    new TFloatPaintedPanel(nullptr);
}

namespace Tfloatpaintedpanel
{
    void __fastcall PACKAGE Register()
    {
         TComponentClass classes[1] = {__classid(TFloatPaintedPanel)};
        RegisterComponents(dslComponents::gDuneEditPanels, classes, 0);
    }
}


