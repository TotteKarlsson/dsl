#ifndef dslTFloatEditH
#define dslTFloatEditH
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <StdCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------

class PACKAGE TFloatEdit : public TEdit
{
    private:

    protected:
        int                     FNrOfDecimals;

    public:
        double                  *FNumber;
        double                  dummy;
                                __fastcall TFloatEdit(TComponent* Owner);
        DYNAMIC void            __fastcall DoExit(void);
        DYNAMIC void            __fastcall KeyDown(Word &Key, Classes::TShiftState Shift);
        void                    __fastcall OnChange(TObject *Sender);
        virtual void            __fastcall Update(void);

        const                   __fastcall double GetNumber();
        double&                 __fastcall GetNumberRef();
        void                    __fastcall SetNumber(const double& val);
        void                    __fastcall SetNumberRef(double& val);
        void                    __fastcall SetNumberOfDecimals(int decimals);

    __published:
        __property int NrOfDecimals = {read=FNrOfDecimals, write=FNrOfDecimals, default=2, stored=true};
};
//---------------------------------------------------------------------------
#endif
