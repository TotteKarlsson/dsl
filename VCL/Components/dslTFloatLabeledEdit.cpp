#pragma hdrstop
#include "dslTFloatLabeledEdit.h"
#pragma package(smart_init)

using namespace dsl;
//---------------------------------------------------------------------------
__fastcall TFloatLabeledEdit::TFloatLabeledEdit(TComponent* Owner)
  :
TLabeledPropertyEdit(Owner),
FNrOfDecimals(8),
FValue(&mDummy)
{
	mBaseProperty = new Property<double>(-1, "<no label>");
	setReference(getProperty()->getValueReference());
}

void TFloatLabeledEdit::setValueFromString(const string& v)
{
	setValue(toDouble(v));
}

//---------------------------------------------------------------------------
Property<double>* TFloatLabeledEdit::getProperty()
{
	return dynamic_cast< Property<double>* > (mBaseProperty);
}

//---------------------------------------------------------------------------
void TFloatLabeledEdit::assignExternalProperty(Property<double>* prop, bool directAccess)
{
	mDirectExternalPropertyAccess = directAccess;
	if(!prop)
	{
		return;
	}

	mBaseProperty = prop;
	if(mDirectExternalPropertyAccess)
	{
		setReference(getProperty()->getValueReference());
	}
	else
	{
		setReference(getProperty()->getEditValueReference());
	}

	//Transfer external property value to VCL component
	Value = prop->getValue();
	getProperty()->discardEdit();
}

//---------------------------------------------------------------------------
double& TFloatLabeledEdit::getReference()
{
    return *FValue;
}

//---------------------------------------------------------------------------
void TFloatLabeledEdit::setReference(double& val)
{
    FValue = &val;
    Text = FloatToStrF(*FValue, ffFixed, 15, FNrOfDecimals);
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
        Text = FloatToStrF(temp, ffFixed, 15, FNrOfDecimals);
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
        Text = FloatToStrF(temp, ffFixed, 15, FNrOfDecimals);
        SelectAll();
        SetFocus();
    }
    return *FValue;
}

void __fastcall TFloatLabeledEdit::setValue(double val)
{
    *FValue = val;
    Text = FloatToStrF(*FValue, ffFixed, 15, FNrOfDecimals);
}

void TFloatLabeledEdit::update(void)
{
    Text = FloatToStrF(*FValue, ffFixed, 15, FNrOfDecimals);
    TWinControl::Update();
}
