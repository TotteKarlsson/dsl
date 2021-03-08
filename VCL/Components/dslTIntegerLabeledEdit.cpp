#pragma hdrstop
#include "dslTIntegerLabeledEdit.h"
#pragma package(smart_init)

using namespace dsl;
using Sysutils::IntToStr;

//---------------------------------------------------------------------------
__fastcall TIntegerLabeledEdit::TIntegerLabeledEdit(TComponent* Owner)
:
TLabeledPropertyEdit(Owner),
//mProperty(nullptr),
FValue(&mDummy)
{
	TLabeledEdit::OnChange = (this->DerivedOnChange);

	mBaseProperty = new Property<int>(-1,"PropertyLabel");
	setReference(getProperty()->getValueReference());

    //The above updates the graphical component, causing the isModified flag to be set. Discard this..
    mBaseProperty->discardEdit();
}

Property<int>* TIntegerLabeledEdit::getProperty()
{
    return dynamic_cast< Property<int>* >(mBaseProperty);
}


//---------------------------------------------------------------------------
void TIntegerLabeledEdit::assignExternalProperty(Property<int>* prop, bool directAccess)
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
    *FValue = prop->getValue();
    update();
	getProperty()->discardEdit();
}

//---------------------------------------------------------------------------
void TIntegerLabeledEdit::setReference(int& val)
{
    FValue = &val;
    update();
}

//---------------------------------------------------------------------------
int& TIntegerLabeledEdit::getReference()
{
    return *FValue;
}

//---------------------------------------------------------------------------
void __fastcall TIntegerLabeledEdit::KeyDown(Word &Key, Classes::TShiftState Shift)
{
    if(Key == VK_RETURN)
    {
        SelectAll();
        DoExit();
    }
    TLabeledEdit::KeyDown(Key, Shift);
}

//---------------------------------------------------------------------------
void __fastcall TIntegerLabeledEdit::DerivedOnChange(TObject *Sender)
{
    if(!GetTextLen() || GetTextLen() == 1 && Text[1] == '-')
    {
        return;
    }

    try
    {
        *FValue = Text.ToInt();
        mBaseProperty->setModified();
    }
    catch(Exception &E)
    {}
}

//---------------------------------------------------------------------------
void __fastcall TIntegerLabeledEdit::DoExit()
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

int __fastcall TIntegerLabeledEdit::getValue()
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

void TIntegerLabeledEdit::setValueFromString(const string& v)
{
    setValue(toInt(v));
}

void __fastcall TIntegerLabeledEdit::setValue(int val)
{
    if(mBaseProperty->isInEditMode())
    {
    	mBaseProperty->setModified();
    }

    *FValue = val;
    Text = IntToStr(*FValue);
}

void TIntegerLabeledEdit::update(void)
{
    Text = IntToStr(*FValue);
    TWinControl::Update();
}


