#pragma hdrstop
#include <Dialogs.hpp>
#include "dslTFloatEdit.h"
#include "dslComponentsPackageDefs.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------
__fastcall TFloatEdit::TFloatEdit(TComponent* Owner)
  : TEdit(Owner)
{
    FNrOfDecimals = 2;
      FNumber = &dummy;

//    OnChange(nullptr);
//      Text = "0.0";
}
//---------------------------------------------------------------------------

double& __fastcall TFloatEdit::GetNumberRef()
{
    return *FNumber;
}

void __fastcall TFloatEdit::SetNumberOfDecimals(int decimals)
{
    FNrOfDecimals = decimals;
}

//---------------------------------------------------------------------------
void __fastcall TFloatEdit::OnChange(TObject *Sender)
{
    try
    {
        *FNumber = Text.ToDouble();
    }
    catch(Exception &E)
    {
        ShowMessage("This is not a valid Number!\nPlease try again..");
        SetFocus();
    }
}

void __fastcall TFloatEdit::DoExit()
{
    double temp = *FNumber;
    try
    {
        *FNumber = Text.ToDouble();
          TEdit::DoExit();
    }
    catch(Exception &E)
    {
        *FNumber = temp;
//          ShowMessage("This is not a valid Number!\nPlease try again..");
          Text = FloatToStrF(temp, ffFixed,7, FNrOfDecimals);

          SelectAll();
        SetFocus();
    }
}

void __fastcall TFloatEdit::KeyDown(Word &Key, Classes::TShiftState Shift)
{
    if(Key == VK_RETURN)
    {
        SelectAll();
        DoExit();
    }
    TEdit::KeyDown(Key, Shift);
}

const __fastcall double TFloatEdit::GetNumber()
{
    try
    {
        *FNumber = Text.ToDouble();
        return *FNumber;
    }
    catch(Exception &E)
    {
        SetFocus();
    }
    return *FNumber;
}

void __fastcall TFloatEdit::SetNumber(const double& val)
{
      *FNumber = val;
      Text = FloatToStrF(*FNumber, ffFixed,7, FNrOfDecimals);
      //SetFocus();
}

void __fastcall TFloatEdit::Update(void)
{
    //If the pointer has been changed...
      Text = FloatToStrF(*FNumber, ffFixed,7, FNrOfDecimals);
      TWinControl::Update();
}

void __fastcall TFloatEdit::SetNumberRef(double& val)
{
  FNumber = &val;
  Text = FloatToStrF(*FNumber, ffFixed,7, FNrOfDecimals);
}
