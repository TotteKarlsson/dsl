#pragma hdrstop
#include "dslTSTDStringLabeledEdit.h"
#include "dslVCLUtils.h"
#pragma package(smart_init)

using namespace dsl;
using Sysutils::IntToStr;

//---------------------------------------------------------------------------
__fastcall TSTDStringLabeledEdit::TSTDStringLabeledEdit(TComponent* Owner)
:
TLabeledEdit(Owner),
mProperty(nullptr),
FValue(&mDummy)
{
	TLabeledEdit::OnChange = (this->DerivedOnChange);
	mProperty = new Property<string>("", "PropertyLabel");
	setReference(mProperty->getValueReference());
}

//---------------------------------------------------------------------------
void __fastcall TSTDStringLabeledEdit::assignExternalProperty(Property<string>* prop, bool directAccess)
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
void __fastcall TSTDStringLabeledEdit::setReference(string& val)
{
    FValue = &val;
    update();
}

//---------------------------------------------------------------------------
Property<string>* __fastcall TSTDStringLabeledEdit::getProperty()
{
    return mProperty;
}

//---------------------------------------------------------------------------
string& __fastcall TSTDStringLabeledEdit::getReference()
{
    return *FValue;
}

//---------------------------------------------------------------------------
void __fastcall TSTDStringLabeledEdit::KeyDown(Word &Key, Classes::TShiftState Shift)
{
    if(Key == VK_RETURN)
    {
        SelectAll();
        DoExit();
    }
    TLabeledEdit::KeyDown(Key, Shift);
}

//---------------------------------------------------------------------------
void __fastcall TSTDStringLabeledEdit::DerivedOnChange(TObject *Sender)
{
    if(!GetTextLen() || GetTextLen() == 1 && Text[1] == '-')
    {
        return;
    }

    try
    {
        *FValue = stdstr(Text);
        mProperty->setModified();
    }
    catch(Exception &E)
    {}
}

//---------------------------------------------------------------------------
void __fastcall TSTDStringLabeledEdit::DoExit()
{
    string temp = *FValue;
    try
    {
        *FValue = stdstr(Text);
    }
    catch(Exception &E)
    {
        *FValue = temp;
        Text = vclstr(temp);
    }
}

String __fastcall TSTDStringLabeledEdit::getStringValue()
{
    string temp = *FValue;
    try
    {
        *FValue =stdstr(Text);
        return vclstr(*FValue);
    }
    catch(Exception &E)
    {
        *FValue = temp;
        Text = vclstr(temp);
        SelectAll();
        SetFocus();
        return vclstr(*FValue);
    }
}

string __fastcall TSTDStringLabeledEdit::getValue()
{
    try
    {
        return (FValue) ? (*FValue) : string("");
    }
    catch(Exception &E)
    {
        ShowMessage("Exception thrown in getValue Edit Control...");
        SetFocus();
        return "";
    }
}

void __fastcall TSTDStringLabeledEdit::setValue(const string& val)
{
    if(mProperty->isInEditMode())
    {
    	mProperty->setModified();
    }

    *FValue = val;
    Text = vclstr(*FValue);
}

void __fastcall TSTDStringLabeledEdit::setStringValue(String val)
{
    setValue(stdstr(val));
}

void __fastcall TSTDStringLabeledEdit::update(void)
{
    Text = vclstr(*FValue);
    TWinControl::Update();
}

void __fastcall TSTDStringLabeledEdit::updateFromCaption()
{
    try
    {
        *FValue = stdstr(Text);
    }
    catch(Exception &E)
    {
    }
}



