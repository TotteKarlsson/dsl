#ifndef dslURLLabelH
#define dslURLLabelH
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------

class PACKAGE TURLLabel : public TLabel
{
private:
      String                            FURLstr;

protected:
    DYNAMIC void      __fastcall        Click();
    void              __fastcall        SetURL(String value);
    String            __fastcall        GetURL();
    bool              __fastcall        RunShellCommand();

public:
                      __fastcall        TURLLabel(TComponent* Owner);
      void               __fastcall     ClickMe();

      __published:
          __property String             URLstr = {read = FURLstr, write = SetURL};
};

#endif
