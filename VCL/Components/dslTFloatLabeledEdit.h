#ifndef dslTFloatLabeledEditH
#define dslTFloatLabeledEditH
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <StdCtrls.hpp>
#include <ExtCtrls.hpp>
#include "dslProperty.h"
//---------------------------------------------------------------------------

using dsl::Property;
//---------------------------------------------------------------------------
class PACKAGE TFloatLabeledEdit : public TLabeledEdit
{
    public:
        double*                                     FValue;
                                    __fastcall      TFloatLabeledEdit(TComponent* Owner);

        double&                     __fastcall      getReference();
        void                        __fastcall      setReference(double& val);

                                                    //When assigning an external property, the directAcess boolean
                                                    //controls how the internal value of the external property is accessed.
                                                    //If directAcess is false, the
                                                    //VCL component is manipulating the propertys internal TEMPORARY value
                                                    //If direct access is true, the VCL component will access the external
                                                    //propertys value directly
        void                        __fastcall      assignExternalProperty(Property<double>* prop, bool directAccess = false);
        virtual void                __fastcall      update(void);
        Property<double>*           __fastcall      getProperty();

                                                    //Access value trough the property.
        double                      __fastcall      getValue();
        void                        __fastcall      setValue(double val);

    protected:
        Property<double>*                           mProperty;
	 	int                                     	FNrOfDecimals;
        bool                                        mDirectExternalPropertyAccess;
        double                                      mDummy;
        DYNAMIC void                __fastcall      DoExit(void);
        DYNAMIC void                __fastcall      KeyDown(Word &Key, Classes::TShiftState Shift);
        void                        __fastcall      OnChange(TObject *Sender);

        void                        __fastcall      SetNumberOfDecimals(int decimals);
        operator const double();

    __published:
        __property int 			NrOfDecimals 	= {read=FNrOfDecimals, write=FNrOfDecimals, default=2};
        __property double       Value 			= {read=getValue, write=setValue, default=0, stored=true};
};


#endif
