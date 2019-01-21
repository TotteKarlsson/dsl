#pragma hdrstop
#include "dslTSTDStringEdit.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"


#pragma package(smart_init)

using namespace dsl;
using Sysutils::IntToStr;

//---------------------------------------------------------------------------
__fastcall TSTDStringEdit::TSTDStringEdit(TComponent* Owner)
:
TEdit(Owner),
mProperty(NULL),
FValue(&mDummy)
{
	FChange = OnChange;

    //Need to make this a shared_ptr..
	mProperty = new Property<string>("", "PropertyLabel");
	setReference(mProperty->getValueReference());
}

//---------------------------------------------------------------------------
void __fastcall TSTDStringEdit::assignExternalProperty(Property<string>* prop, bool directAccess)
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
    Value = vclstr(prop->getValue());
}

//---------------------------------------------------------------------------
void __fastcall TSTDStringEdit::setReference(string& val)
{
    FValue = &val;
    Text = vclstr(*FValue);
}

//---------------------------------------------------------------------------
Property<string>* __fastcall TSTDStringEdit::getProperty()
{
    return mProperty;
}

//---------------------------------------------------------------------------
string& __fastcall TSTDStringEdit::getReference()
{
    return *FValue;
}

//---------------------------------------------------------------------------
void __fastcall TSTDStringEdit::KeyDown(Word &Key, Classes::TShiftState Shift)
{
    if(Key == VK_RETURN)
    {
        SelectAll();
        DoExit();
    }
    TEdit::KeyDown(Key, Shift);
}

//---------------------------------------------------------------------------
void __fastcall TSTDStringEdit::OnChange(TObject *Sender)
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
void __fastcall TSTDStringEdit::DoExit()
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

String __fastcall TSTDStringEdit::getStringValue()
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

string __fastcall TSTDStringEdit::getValue()
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

void __fastcall TSTDStringEdit::setValue(const string& val)
{
	try
    {
    	if(val.size())
        {
    		*FValue = val;
		    Text = vclstr(*FValue);
	        mProperty->setModified();
        }
        else
        {
        	*FValue = "";
            Text = "";
        }
    }
    catch(...)
    {
    	Log(lError) << "Bad stuff..";
    }
}

void __fastcall TSTDStringEdit::setStringValue(String val)
{
    setValue(stdstr(val));
}

void __fastcall TSTDStringEdit::update(void)
{
    Text = vclstr(*FValue);
    TWinControl::Update();
}

void __fastcall TSTDStringEdit::updateFromCaption()
{
    try
    {
        *FValue =stdstr(Text);
    }
    catch(Exception &E)
    {
    }
}



