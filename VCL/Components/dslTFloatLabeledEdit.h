#ifndef dslTFloatLabeledEditH
#define dslTFloatLabeledEditH
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <StdCtrls.hpp>
#include <ExtCtrls.hpp>
#include "dslProperty.h"
#include "dslTLabeledPropertyEdit.h"
//---------------------------------------------------------------------------

using dsl::Property;
//---------------------------------------------------------------------------
class PACKAGE TFloatLabeledEdit : public TLabeledPropertyEdit
{
    public:
        double*                                     FValue;
                                    __fastcall      TFloatLabeledEdit(TComponent* Owner);

        double&                                     getReference();
        void                                        setReference(double& val);
        void                                        setValueFromString(const string&);

                                                    //When assigning an external property, the directAcess boolean
                                                    //controls how the internal value of the external property is accessed.
                                                    //If directAcess is false, the
                                                    //VCL component is manipulating the propertys internal TEMPORARY value
                                                    //If direct access is true, the VCL component will access the external
                                                    //propertys value directly
        void                                        assignExternalProperty(Property<double>* prop, bool directAccess = false);
        virtual void                                update(void);
        Property<double>*                           getProperty();

                                                    //Access value trough the property.
        double                      __fastcall      getValue();
        void                        __fastcall      setValue(double val);

    protected:
	 	int                                     	FNrOfDecimals;

        double                                      mDummy;
        DYNAMIC void                __fastcall      DoExit(void);
        void                        __fastcall      OnChange(TObject *Sender);
        void                        			    setNumberOfDecimals(int decimals);
        operator const double();

    __published:
        __property int 			NrOfDecimals 	= {read=FNrOfDecimals, write=FNrOfDecimals, default=2};
        __property double       Value 			= {read=getValue, write=setValue, default=0, stored=true};
};


#endif
