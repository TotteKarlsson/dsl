#pragma hdrstop
#include <Dialogs.hpp>
#include "dslTFloatLabel.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall TFloatLabel::TFloatLabel(TComponent* Owner)
:
TLabel(Owner),
mDummy(-1),
FNrOfDecimals(2)
{
    FValue = &mDummy;
//    UpdateFromValue();
}

//---------------------------------------------------------------------------
void __fastcall TFloatLabel::SetValueString(string Value)
{
    SetValueString(String(Value.c_str()));
}

void __fastcall TFloatLabel::SetValueString(String Value)
{
    FValueString = Value;
    UpdateFromString();
}

void __fastcall TFloatLabel::SetValue(double val)
{
    *FValue = val;
    UpdateFromValue();

}

void __fastcall TFloatLabel::UpdateFromValue(void)
{
  //If the pointer has been changed...
      if(FValue)
    {
        FValueString = FloatToStrF(*FValue, ffFixed,7, FNrOfDecimals);
    }
    Caption = FValueString;
}

void __fastcall TFloatLabel::UpdateFromString()
{
    double val = 0;
    Caption = FValueString;
    try
    {
        val = FValueString.ToDouble();
    }
    catch(...)
    {
        return;
    }
    *FValue = val;
}

void __fastcall TFloatLabel::SetReference(double& val)
{
    FValue = &val;
    UpdateFromValue();
}

double __fastcall  TFloatLabel::GetValue()
{
    return *FValue;
}

void __fastcall  TFloatLabel::SetNrOfDecimals(int decimals)
{
    NrOfDecimals = decimals;
    UpdateFromValue();
}

int __fastcall  TFloatLabel::GetNrOfDecimals()
{
    return FNrOfDecimals;
}
