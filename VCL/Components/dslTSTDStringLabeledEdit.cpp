#pragma hdrstop
#include "dslTSTDStringLabeledEdit.h"
#include "dslVCLUtils.h"
#pragma package(smart_init)

using namespace dsl;
using Sysutils::IntToStr;

//---------------------------------------------------------------------------
__fastcall TSTDStringLabeledEdit::TSTDStringLabeledEdit(TComponent* Owner)
:
TLabeledPropertyEdit(Owner),
FValue(&mDummy)
{
	TLabeledEdit::OnChange = (this->DerivedOnChange);
	mBaseProperty = new Property<string>("", "PropertyLabel");
	setReference(getProperty()->getValueReference());
}

Property<string>* TSTDStringLabeledEdit::getProperty()
{
    return dynamic_cast< Property<string>* >(mBaseProperty);
}

void TSTDStringLabeledEdit::setValueFromString(const string& v)
{
    setValue(v);
}

//---------------------------------------------------------------------------
void TSTDStringLabeledEdit::assignExternalProperty(Property<string>* prop, bool directAccess)
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
}

//---------------------------------------------------------------------------
void TSTDStringLabeledEdit::setReference(string& val)
{
    FValue = &val;
    update();
}

////---------------------------------------------------------------------------
//Property<string>* __fastcall TSTDStringLabeledEdit::getProperty()
//{
//    return mBaseProperty;
//}
//
//---------------------------------------------------------------------------
string& TSTDStringLabeledEdit::getReference()
{
    return *FValue;
}

//---------------------------------------------------------------------------
//void __fastcall TSTDStringLabeledEdit::KeyDown(Word &Key, Classes::TShiftState Shift)
//{
//    if(Key == VK_RETURN)
//    {
//        SelectAll();
//        DoExit();
//    }
//    TLabeledEdit::KeyDown(Key, Shift);
//}

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
        mBaseProperty->setModified();
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

string TSTDStringLabeledEdit::getValue()
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

void TSTDStringLabeledEdit::setValue(const string& val)
{
    if(mBaseProperty->isInEditMode())
    {
    	mBaseProperty->setModified();
    }

    *FValue = val;
    Text = vclstr(*FValue);
}

void __fastcall TSTDStringLabeledEdit::setValueFromUnicodeString(const String& val)
{
    setValue(stdstr(val));
}

void TSTDStringLabeledEdit::update(void)
{
    Text = vclstr(*FValue);
    TWinControl::Update();
}

void TSTDStringLabeledEdit::updateFromCaption()
{
    try
    {
        *FValue = stdstr(Text);
    }
    catch(Exception &E)
    {
    }
}



