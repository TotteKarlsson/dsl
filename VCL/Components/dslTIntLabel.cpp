#pragma hdrstop
#include "dslTIntLabel.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------
__fastcall TIntLabel::TIntLabel(TComponent* Owner)
:
TLabel(Owner),
mDummy(-1),
FValue(&mDummy)
{}

//---------------------------------------------------------------------------
void __fastcall TIntLabel::setValue(int val)
{
    *FValue = val;
    Caption = IntToStr(*FValue);
}

int __fastcall TIntLabel::getValue()
{
	return *FValue;
}
//---------------------------------------------------------------------------
void __fastcall TIntLabel::setReference(int& val)
{
    FValue = &val;
    Caption = IntToStr(*FValue);
}

//---------------------------------------------------------------------------
int& __fastcall TIntLabel::getReference()
{
	return *FValue;
}

//---------------------------------------------------------------------------
void __fastcall TIntLabel::update(void)
{
    Caption = IntToStr(*FValue);
}

//---------------------------------------------------------------------------
void __fastcall TIntLabel::OnChange(TObject *Sender)
{
    if(!GetTextLen() || GetTextLen() == 1 && Caption[1] == '-')
    {
        return;
    }

    try
    {
        *FValue = Caption.ToInt();
    }
    catch(Exception &E)
    {}
}


