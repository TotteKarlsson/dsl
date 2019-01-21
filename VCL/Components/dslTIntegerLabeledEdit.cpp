#pragma hdrstop
#include "dslTIntegerLabeledEdit.h"
#pragma package(smart_init)

using namespace dsl;
using Sysutils::IntToStr;

//---------------------------------------------------------------------------
__fastcall TIntegerLabeledEdit::TIntegerLabeledEdit(TComponent* Owner)
:
TLabeledEdit(Owner),
mProperty(nullptr),
FValue(&mDummy)
{
	TLabeledEdit::OnChange = (this->DerivedOnChange);
	mProperty = new Property<int>(-1,"PropertyLabel");
	setReference(mProperty->getValueReference());
}

//---------------------------------------------------------------------------
void __fastcall TIntegerLabeledEdit::assignExternalProperty(Property<int>* prop, bool directAccess)
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
    *FValue = prop->getValue();
    update();
}

//---------------------------------------------------------------------------
void __fastcall TIntegerLabeledEdit::setReference(int& val)
{
    FValue = &val;
    update();
}

//---------------------------------------------------------------------------
Property<int>* __fastcall TIntegerLabeledEdit::getProperty()
{
	return mProperty;
}

//---------------------------------------------------------------------------
int& __fastcall TIntegerLabeledEdit::getReference()
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
        mProperty->setModified();
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

void __fastcall TIntegerLabeledEdit::setValue(int val)
{
    if(mProperty->isInEditMode())
    {
    	mProperty->setModified();
    }

    *FValue = val;
    Text = IntToStr(*FValue);
}

void __fastcall TIntegerLabeledEdit::update(void)
{
    Text = IntToStr(*FValue);
    TWinControl::Update();
}


