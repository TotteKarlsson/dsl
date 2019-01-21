#ifndef dslIntEditH
#define dslIntEditH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <StdCtrls.hpp>
#include <ExtCtrls.hpp>
#include "dslPackageDefs.h"
//---------------------------------------------------------------------------

/* OBSOLETE... use TIntegerEdit */
class PACKAGE IntEdit : public TEdit
{
private:

protected:
public:
    int *FValue;
    int dummy;
                    __fastcall IntEdit(TComponent* Owner);
    DYNAMIC void    __fastcall DoExit(void);
    DYNAMIC void    __fastcall KeyDown(Word &Key, Classes::TShiftState Shift);
    void            __fastcall OnChange(TObject *Sender);
    virtual void    __fastcall update(void);

    const           __fastcall int getValue();
    int&            __fastcall getValueRef();
    void            __fastcall setValue(const int& val);
    void            __fastcall setValueRef(int& val);
__published:

};

#endif
