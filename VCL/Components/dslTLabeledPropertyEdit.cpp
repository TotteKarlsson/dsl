#pragma hdrstop
#include "dslTLabeledPropertyEdit.h"
#include "dslVCLUtils.h"
#pragma package(smart_init)

using namespace dsl;
using Sysutils::IntToStr;

//---------------------------------------------------------------------------
__fastcall TLabeledPropertyEdit::TLabeledPropertyEdit(TComponent* Owner)
:
TLabeledEdit(Owner),
mBaseProperty(nullptr)//,
//FValue(&mDummy)
{
//	TLabeledEdit::OnChange = (this->DerivedOnChange);
//	mBaseProperty = new Property<string>("", "PropertyLabel");
//	setReference(mBaseProperty->getValueReference());
}

////---------------------------------------------------------------------------
//void __fastcall TLabeledPropertyEdit::assignExternalProperty(Property<string>* prop, bool directAccess)
//{
//    mDirectExternalPropertyAccess = directAccess;
//    if(!prop)
//    {
//        return;
//    }
//
//    mBaseProperty = prop;
//    if(mDirectExternalPropertyAccess)
//    {
//        setReference(mBaseProperty->getValueReference());
//    }
//    else
//    {
//        setReference(mBaseProperty->getEditValueReference());
//    }
//
//    //Transfer external property value to VCL component
//    *FValue = prop->getValue();
//    update();
//}
//
////---------------------------------------------------------------------------
//void __fastcall TLabeledPropertyEdit::setReference(string& val)
//{
//    FValue = &val;
//    update();
//}
//
//---------------------------------------------------------------------------
BaseProperty* TLabeledPropertyEdit::getProperty()
{
    return mBaseProperty;
}

////---------------------------------------------------------------------------
//string& __fastcall TLabeledPropertyEdit::getReference()
//{
//    return *FValue;
//}
//

//---------------------------------------------------------------------------
void __fastcall TLabeledPropertyEdit::KeyDown(Word &Key, Classes::TShiftState Shift)
{
    if(Key == VK_RETURN)
    {
        SelectAll();
        DoExit();
    }
    TLabeledEdit::KeyDown(Key, Shift);
}

////---------------------------------------------------------------------------
//void __fastcall TLabeledPropertyEdit::DerivedOnChange(TObject *Sender)
//{
//    if(!GetTextLen() || GetTextLen() == 1 && Text[1] == '-')
//    {
//        return;
//    }
//
//    try
//    {
//        *FValue = stdstr(Text);
//        mBaseProperty->setModified();
//    }
//    catch(Exception &E)
//    {}
//}

////---------------------------------------------------------------------------
//void __fastcall TLabeledPropertyEdit::DoExit()
//{
//    string temp = *FValue;
//    try
//    {
//        *FValue = stdstr(Text);
//    }
//    catch(Exception &E)
//    {
//        *FValue = temp;
//        Text = vclstr(temp);
//    }
//}

//String __fastcall TLabeledPropertyEdit::getStringValue()
//{
//    string temp = *FValue;
//    try
//    {
//        *FValue =stdstr(Text);
//        return vclstr(*FValue);
//    }
//    catch(Exception &E)
//    {
//        *FValue = temp;
//        Text = vclstr(temp);
//        SelectAll();
//        SetFocus();
//        return vclstr(*FValue);
//    }
//}
//
//string __fastcall TLabeledPropertyEdit::getValue()
//{
//    try
//    {
//        return (FValue) ? (*FValue) : string("");
//    }
//    catch(Exception &E)
//    {
//        ShowMessage("Exception thrown in getValue Edit Control...");
//        SetFocus();
//        return "";
//    }
//}
//
//void __fastcall TLabeledPropertyEdit::setValue(const string& val)
//{
//    if(mBaseProperty->isInEditMode())
//    {
//    	mBaseProperty->setModified();
//    }
//
//    *FValue = val;
//    Text = vclstr(*FValue);
//}
//
//void __fastcall TLabeledPropertyEdit::setStringValue(String val)
//{
//    setValue(stdstr(val));
//}
//
//void __fastcall TLabeledPropertyEdit::update(void)
//{
//    Text = vclstr(*FValue);
//    TWinControl::Update();
//}
//
//void __fastcall TLabeledPropertyEdit::updateFromCaption()
//{
//    try
//    {
//        *FValue = stdstr(Text);
//    }
//    catch(Exception &E)
//    {
//    }
//}



