#pragma hdrstop
#include "dslTFloatLabeledEdit.h"
#pragma package(smart_init)

using namespace dsl;
//---------------------------------------------------------------------------
__fastcall TFloatLabeledEdit::TFloatLabeledEdit(TComponent* Owner)
  :
TLabeledEdit(Owner),
FNrOfDecimals(2),
mProperty(0),
FValue(&mDummy)
{
//    Text = "0.0";
	mProperty = new Property<double>(-1, "PropertyLabel");
	setReference(mProperty->getValueReference());
}

//---------------------------------------------------------------------------
void __fastcall TFloatLabeledEdit::assignExternalProperty(Property<double>* prop, bool directAccess)
{
	mDirectExternalPropertyAccess = directAccess;
	if(!prop)
	{
		return;
	}

	mProperty = prop;
	if(mDirectExternalPropertyAccess)
	{
		setReference(mProperty->getValueReference());
	}
	else
	{
		setReference(mProperty->getEditValueReference());
	}

	//Transfer external property value to VCL component
	Value = prop->getValue();
}

//---------------------------------------------------------------------------
Property<double>* __fastcall TFloatLabeledEdit::getProperty()
{
	return mProperty;
}

//---------------------------------------------------------------------------
double& __fastcall TFloatLabeledEdit::getReference()
{
    return *FValue;
}

//---------------------------------------------------------------------------
void __fastcall TFloatLabeledEdit::setReference(double& val)
{
    FValue = &val;
    Text = FloatToStrF(*FValue, ffFixed, 4,2);
}

//---------------------------------------------------------------------------
void __fastcall TFloatLabeledEdit::KeyDown(Word &Key, Classes::TShiftState Shift)
{
    if(Key == VK_RETURN)
    {
        SelectAll();
        DoExit();
    }
    TLabeledEdit::KeyDown(Key, Shift);
}

//---------------------------------------------------------------------------
void __fastcall TFloatLabeledEdit::OnChange(TObject *Sender)
{
    if(!GetTextLen() || GetTextLen() == 1 && Text[1] == '-')
    {
        return;
    }

    try
    {
        *FValue = Text.ToDouble();
    }
    catch(Exception &E)
    {}
}

//---------------------------------------------------------------------------
void __fastcall TFloatLabeledEdit::DoExit()
{
    double temp = *FValue;
    try
    {
        *FValue = Text.ToDouble();
    }
    catch(Exception &E)
    {
        *FValue = temp;
        Text = FloatToStrF(temp, ffFixed, 4, 2);
    }
}

double __fastcall TFloatLabeledEdit::getValue()
{
    double temp = *FValue;
    try
    {
        *FValue = Text.ToDouble();
        return *FValue;
    }
    catch(Exception &E)
    {
        *FValue = temp;
        Text = FloatToStrF(temp, ffFixed, 4,2);
        SelectAll();
        SetFocus();
    }
    return *FValue;
}

void __fastcall TFloatLabeledEdit::setValue(double val)
{
    *FValue = val;
    Text = FloatToStrF(*FValue, ffFixed, 18, 4);
}

void __fastcall TFloatLabeledEdit::update(void)
{
    Text = FloatToStrF(*FValue, ffFixed, 18, 4);
    TWinControl::Update();
}



