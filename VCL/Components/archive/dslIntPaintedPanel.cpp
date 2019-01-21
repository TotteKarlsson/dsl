
#pragma hdrstop
#include "TIntPaintedPanel.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------
__fastcall TIntPaintedPanel::TIntPaintedPanel(TComponent* Owner)
:
TPaintedPanel(Owner),
FLabel(new dslIntLabel(this)),
FValueCaption(L"100"),
FValueLabelAlign(alClient),
FValueLabelAlignment(taCenter),
FValueLabelLayout(tlCenter)
{
    this->Color = clMoneyGreen;
    this->ParentBackground = true;
    this->Width = 118;
    this->Height = 57;

    /// The Value
    FLabel->Top              = FValueTop;
    FLabel->Left             = FValueLeft;
    FLabel->Parent           = this;
    FLabel->Align            = FValueLabelAlign;
    FLabel->Alignment        = FValueLabelAlignment;
    FLabel->Layout           = FValueLabelLayout;
    FLabel->Caption          = FValueCaption;
    FLabel->OnClick          = &ValueClicked;
}

//---------------------------------------------------------------------------
__fastcall TIntPaintedPanel::~TIntPaintedPanel()
{
    delete FLabel;
}

void __fastcall TIntPaintedPanel::SetReference(int& val)
{
    if(FLabel)
    {
        FLabel->SetReference(val);
    }
}

TFont*  __fastcall TIntPaintedPanel::GetValueFont()
{
    return FLabel ? FLabel->Font : nullptr;
}

void __fastcall TIntPaintedPanel::SetValueFont(TFont* aFont)
{
    FLabel->Font = aFont;
}

void __fastcall TIntPaintedPanel::ValueClicked(TObject *Sender)
{
    if( FOnValueClick )
    {
        FOnValueClick(this);
    }
}

//---------------------------------------------------------------------------
void __fastcall TIntPaintedPanel::SetValueLabelLeft(int left)
{
    FValueLeft              = left;
    FLabel->Left       = FValueLeft;
}

void __fastcall TIntPaintedPanel::SetValueLabelTop(int top)
{
    FValueTop           = top;
    FLabel->Top    = FValueTop;
}

String __fastcall TIntPaintedPanel::GetValueCaption()
{
    return FValueCaption;
}

void __fastcall TIntPaintedPanel::SetValueCaption(String aString)
{
    FValueCaption = aString;
    if(FLabel)
    {
        FLabel->SetValueString(FValueCaption);
    }
}

int __fastcall TIntPaintedPanel::GetValue()
{
    return (FLabel) ? FLabel->GetValue() : 0;
}

void __fastcall TIntPaintedPanel::SetValue(int number)
{
    if(FLabel)
    {
        FLabel->SetValue(number);
    }
}

//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//
static inline void ValidCtrCheck(TIntPaintedPanel *)
{
    new TIntPaintedPanel(nullptr);
}

namespace Tintpaintedpanel
{
    void __fastcall PACKAGE Register()
    {
        TComponentClass classes[1] = {__classid(TIntPaintedPanel)};
        RegisterComponents(dslComponents::gDuneEditPanels, classes, 0);
    }
}


