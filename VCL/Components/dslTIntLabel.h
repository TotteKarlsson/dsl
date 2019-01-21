#ifndef TIntLabelH
#define TIntLabelH
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------

class PACKAGE TIntLabel : public TLabel
{
    public:
                                    __fastcall      TIntLabel(TComponent* Owner);
        int                         __fastcall      getValue();
        void                        __fastcall      setValue(int val);
        void                        __fastcall      setReference(int& val);
        int&                        __fastcall      getReference();
        virtual void                __fastcall      update(void);

    protected:
        int                        	           	*FValue;
        int                                    	mDummy;
        void __fastcall      					OnChange(TObject *Sender);


    __published:
        __property int          Value           = {read=getValue,       write=setValue};
        __property TFont*       TheFont         = {read=FFont,          write=FFont};
};

#endif
