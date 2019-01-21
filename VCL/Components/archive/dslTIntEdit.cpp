#pragma hdrstop
#include <Dialogs.hpp>
#include "dslIntEdit.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------
__fastcall IntEdit::IntEdit(TComponent* Owner)
  : TEdit(Owner)
{
    FValue = &dummy;
    Text = "0";
}

//---------------------------------------------------------------------------
void __fastcall IntEdit::OnChange(TObject *Sender)
{

    try
    {
        *FValue = Text.ToInt();
    }
    catch(Exception &E)
    {
        ShowMessage("This is not a valid Number!\nPlease try again..");
        SetFocus();
    }
}

void __fastcall IntEdit::DoExit()
{
    int temp = *FValue;
    try
    {
        *FValue = Text.ToInt();
          TEdit::DoExit();
    }
    catch(Exception &E)
    {
        *FValue = temp;
          ShowMessage("This is not a valid Number!\nPlease try again..");
          Text = IntToStr(temp);
          SelectAll();
          SetFocus();
      }
}

void __fastcall IntEdit::KeyDown(Word &Key, Classes::TShiftState Shift){

    if(Key == VK_RETURN)
    {
        SelectAll();
        DoExit();
    }
    TEdit::KeyDown(Key, Shift);
}

const __fastcall int IntEdit::getValue()
{
    int temp = *FValue;
    try
    {
        *FValue = Text.ToInt();
        return *FValue;
    }
    catch(Exception &E)
    {
        *FValue = temp;
        Text = IntToStr(temp);
        SelectAll();
        SetFocus();
    }
    return *FValue;
}

void __fastcall IntEdit::setValue(const int& val)
{
    *FValue = val;
    Text = IntToStr(*FValue);
}

void __fastcall IntEdit::setValueRef(int& val)
{
    FValue = &val;
    Text = IntToStr(*FValue);
}

void __fastcall IntEdit::update(void)
{
    Text = IntToStr(*FValue);
    TWinControl::Update();
}

int& __fastcall IntEdit::getValueRef()
{
    return *FValue;
}
