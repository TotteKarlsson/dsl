#ifndef dslFloatLabelH
#define dslFloatLabelH
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <StdCtrls.hpp>
#include <string>

using std::string;

//---------------------------------------------------------------------------
class PACKAGE TFloatLabel : public TLabel
{
    private:
        int                                     FNrOfDecimals;

    protected:
        double*                                 FValue;
        double                                  mDummy;
        String                                  FValueString;


    public:
                        __fastcall              TFloatLabel(TComponent* Owner);
        virtual void    __fastcall              UpdateFromValue(void);
        virtual void    __fastcall              UpdateFromString(void);
        void            __fastcall              SetValueString(String str);
        void            __fastcall              SetValueString(string str);

        double          __fastcall              GetValue();
        void            __fastcall              SetValue(double val);

        void            __fastcall              SetReference(double& val);
        void            __fastcall              SetNrOfDecimals(int decimals);
        int             __fastcall              GetNrOfDecimals();
        void            __fastcall              OnChange(TObject *Sender);

    __published:
        __property String       ValueString    = {read=FValueString, write=SetValueString};
        __property double       Value          = {read=GetValue, write=SetValue                     };
        __property int          NrOfDecimals   = {read=FNrOfDecimals, write=FNrOfDecimals,     default=2};
        __property TFont*       TheFont        = {read=FFont, write=FFont};
};

#endif
