#pragma hdrstop
#include "dslTPropertyCheckBox.h"
#include "dslVCLUtils.h"
#pragma package(smart_init)

using namespace dsl;

//---------------------------------------------------------------------------
__fastcall TPropertyCheckBox::TPropertyCheckBox(TComponent* Owner)
:
TCheckBox(Owner),
mProperty(new Property<bool>(false, "PropertyLabel"))
{
	TCheckBox::OnClick = (this->derivedOnClick);
    FValue = &mDummy;
}

//---------------------------------------------------------------------------
void __fastcall TPropertyCheckBox::assignExternalProperty(Property<bool>* prop, bool directAccess)
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
Property<bool>* __fastcall TPropertyCheckBox::getProperty()
{
    return mProperty;
}

//---------------------------------------------------------------------------
bool& __fastcall TPropertyCheckBox::getReference()
{
    return *FValue;
}

//---------------------------------------------------------------------------
void __fastcall TPropertyCheckBox::setReference(bool& val)
{
    FValue = &val;
    Checked = val;
}

bool __fastcall TPropertyCheckBox::getValue()
{
    return *FValue;
}

void __fastcall TPropertyCheckBox::setValue(bool val)
{
    *FValue = val;
	Checked  = *FValue;
}

//---------------------------------------------------------------------------
void __fastcall TPropertyCheckBox::derivedOnClick(TObject *Sender)
{
	try
	{
		*FValue = Checked;
        mProperty->setValue(*FValue);
	}
	catch(Exception &E)
	{}
}

void __fastcall TPropertyCheckBox::update(void)
{
	Checked  = *FValue;
}


