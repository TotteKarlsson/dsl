#pragma hdrstop
#include <Dialogs.hpp>
#include "dslVCLUtils.h"
#include "dslTURLLabel.h"
#pragma package(smart_init)
using namespace dsl;

//---------------------------------------------------------------------------
__fastcall TURLLabel::TURLLabel(TComponent* Owner)
  : TLabel(Owner)
{
    Font->Color = clBlue;
    Font->Style = TFontStyles()<<fsUnderline;
    Cursor      = crHandPoint;
}

void __fastcall TURLLabel::Click()
{
    RunShellCommand();
}

bool __fastcall TURLLabel::RunShellCommand()
{
    try
    {
        ShellExecuteA(nullptr, nullptr, stdstr(FURLstr).c_str(), 0, 0, SW_SHOWNORMAL);
    }
    catch(...)
    {
        MessageDlg("Failed running shell command", mtError, TMsgDlgButtons() << mbOK, 0);
        return false;
    }
    return true;
}

String __fastcall TURLLabel::GetURL()
{
    return FURLstr;
}

void __fastcall TURLLabel::ClickMe()
{
    RunShellCommand();
}

void __fastcall TURLLabel::SetURL(String value)
{
    FURLstr = value;
}


