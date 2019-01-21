#pragma hdrstop
#include "dslTIntegerEdit.h"
#pragma package(smart_init)

using namespace dsl;
using Sysutils::IntToStr;

//---------------------------------------------------------------------------
__fastcall TIntegerEdit::TIntegerEdit(TComponent* Owner)
:
TEdit(Owner),
mProperty(NULL),
mDummy(0),
FValue(&mDummy)
{
	mProperty = new Property<int>(-1, "PropertyLabel");
	mProperty->setValueReference(*FValue);
    this->Text = "0";
    this->NumbersOnly = true;
}

//---------------------------------------------------------------------------
void __fastcall TIntegerEdit::assignExternalProperty(Property<int>* prop, bool directAccess)
{
	mDirectExternalPropertyAccess = directAccess;
	if(!prop)
	{
		return;
	}

    if(mProperty)
    {
    	delete mProperty;
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
void __fastcall TIntegerEdit::setReference(int& val)
{
    FValue = &val;
	mProperty->setValueReference(*FValue);
    Text = IntToStr(*FValue);
}

//---------------------------------------------------------------------------
Property<int>* __fastcall TIntegerEdit::getProperty()
{
	return mProperty;
}

//---------------------------------------------------------------------------
int& __fastcall TIntegerEdit::getReference()
{
    return *FValue;
}

//---------------------------------------------------------------------------
void __fastcall TIntegerEdit::KeyDown(Word &Key, Classes::TShiftState Shift)
{
    if(Key == VK_RETURN)
    {
        SelectAll();
        DoExit();
    }
    TEdit::KeyDown(Key, Shift);
}

//---------------------------------------------------------------------------
void __fastcall TIntegerEdit::OnChange(TObject *Sender)
{
    if(!GetTextLen() || GetTextLen() == 1 && Text[1] == '-')
    {
        return;
    }

    try
    {
        *FValue = Text.ToInt();
    }
    catch(Exception &E)
    {}
}

//---------------------------------------------------------------------------
void __fastcall TIntegerEdit::DoExit()
{
    int temp = *FValue;
    try
    {
        *FValue = Text.ToInt();
    }
    catch(Exception &E)
    {
        *FValue = temp;
        Text = IntToStr(temp);
    }
}

int __fastcall TIntegerEdit::getValue()
{
    int temp = *FValue;
    try
    {
        *FValue = Text.ToInt();
        return *FValue;
    }
    catch(const Exception& E)
    {
        *FValue = temp;
        Text = IntToStr(temp);
        SelectAll();
        SetFocus();
    }
    return *FValue;
}

void __fastcall TIntegerEdit::setValue(int val)
{
    *FValue = val;
    Text = IntToStr(*FValue);
}

void __fastcall TIntegerEdit::update(void)
{
    Text = IntToStr(*FValue);
    TWinControl::Update();
}


