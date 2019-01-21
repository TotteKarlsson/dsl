
#pragma hdrstop
#include "TCaptionedIntPaintedPanel.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------
__fastcall TCaptionedIntPaintedPanel::TCaptionedIntPaintedPanel(TComponent* Owner)
    :
    TPaintedPanel(Owner),
    FValueLeft(7),
    FValueTop(27),
    mCaptionColor(-1),
    FCaption(nullptr)
{
    this->Color = clMoneyGreen;
    this->ParentBackground = true;
    this->Width = 118;
    this->Height = 57;

    FCaption                = new TLabel(this);
    FCaption->Caption       = "TheCaption";
    FCaption->Parent        = this;
    FCaption->Align         = alTop;
    FCaption->Width         = this->Width;
    FCaption->Alignment     = taCenter;
    FCaption->Caption       = this->Caption;//"My Label";

    FCaption->Visible = FCaptionVisible;

    ///// The Value
    FIntLabel               = new dslIntLabel(this);
    FIntLabel->Parent       = this;
    FIntLabel->Alignment    = taLeftJustify;
    FIntLabel->Top          = FValueTop;
    FIntLabel->Left         = FValueLeft;
    FIntLabel->OnClick      = &ValueClicked;
    if(FCaption)
    {
        FCaption->OnClick       = &ValueClicked;
    }
}

//---------------------------------------------------------------------------
__fastcall TCaptionedIntPaintedPanel::~TCaptionedIntPaintedPanel()
{
    delete FCaption;
    delete FIntLabel;
}

void __fastcall TCaptionedIntPaintedPanel::SetReference(int& val)
{
    if(FIntLabel)
    {
        FIntLabel->SetReference(val);
    }
}

bool __fastcall TCaptionedIntPaintedPanel::GetCaptionVisible()
{
    return (FCaption) ? FCaption->Visible : false;
}

void __fastcall TCaptionedIntPaintedPanel::SetCaptionVisible(bool visible)
{
    if(FCaption)
    {
        FCaption->Visible = visible;
    }
}

TFont* __fastcall TCaptionedIntPaintedPanel::GetCaptionFont()
{
    return FCaption ? FCaption->Font : nullptr;
}

void __fastcall TCaptionedIntPaintedPanel::SetCaptionFont(TFont* aFont)
{
    if(FCaption)
    {
        FCaption->Font = aFont;
    }
}

TFont*  __fastcall TCaptionedIntPaintedPanel::GetValueFont()
{
    return FIntLabel ? FIntLabel->Font : nullptr;
}

void __fastcall TCaptionedIntPaintedPanel::SetValueFont(TFont* aFont)
{
    FIntLabel->Font = aFont;
}

void __fastcall TCaptionedIntPaintedPanel::Enable(bool doWhat)
{
    if(mCaptionColor == -1)
    {
        mCaptionColor = FCaption->Font->Color ;
        mValueColor = FIntLabel->Font->Color;
    }

    if(doWhat == false)
    {
        FCaption->Font->Color   = clGrayText;
        FIntLabel->Font->Color  = clGrayText;
        this->Enabled = false;
    }
    else
    {
        FCaption->Font->Color = mCaptionColor;
        FIntLabel->Font->Color = mValueColor;
        this->Enabled = true;
    }
}

void __fastcall TCaptionedIntPaintedPanel::ValueClicked(TObject *Sender)
{
    if( FOnValueClick )
        FOnValueClick(this);
}

//---------------------------------------------------------------------------
void __fastcall TCaptionedIntPaintedPanel::SetValueLabelLeft(int left)
{
    FValueLeft              = left;
    FIntLabel->Left       = FValueLeft;
}

void __fastcall TCaptionedIntPaintedPanel::SetValueLabelTop(int top)
{
    FValueTop           = top;
    FIntLabel->Top    = FValueTop;
}

String __fastcall TCaptionedIntPaintedPanel::GetLabelCaption()
{
    return (FCaption) ? FCaption->Caption : String("<none>");
}

void __fastcall TCaptionedIntPaintedPanel::SetLabelCaption(String aString)
{
    if(FCaption)
    {
        FCaption->Caption = aString;
    }
}

String __fastcall TCaptionedIntPaintedPanel::GetValueCaption()
{
    return FValueCaption;
}

void __fastcall TCaptionedIntPaintedPanel::SetValueCaption(String aString)
{
    FValueCaption = aString;
    if(FIntLabel)
    {
        FIntLabel->SetValueString(FValueCaption);
    }
}

int __fastcall TCaptionedIntPaintedPanel::GetValue()
{
    return (FIntLabel) ? FIntLabel->GetValue() : 0;
}

void __fastcall TCaptionedIntPaintedPanel::SetValue(int number)
{
    if(FIntLabel)
    {
        FIntLabel->SetValue(number);
    }
}


//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//
static inline void ValidCtrCheck(TCaptionedIntPaintedPanel *)
{
    new TCaptionedIntPaintedPanel(nullptr);
}

namespace Tcaptionedintpaintedpanel
{
    void __fastcall PACKAGE Register()
    {
         TComponentClass classes[1] = {__classid(TCaptionedIntPaintedPanel)};
        RegisterComponents(dslComponents::gDuneEditPanels, classes, 0);
    }
}


