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
mBaseProperty(nullptr)
{}

//---------------------------------------------------------------------------
BaseProperty* TLabeledPropertyEdit::getProperty()
{
    return mBaseProperty;
}

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



