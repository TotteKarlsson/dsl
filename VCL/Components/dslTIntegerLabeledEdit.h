#ifndef TIntegerLabeledEditH
#define TIntegerLabeledEditH
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <StdCtrls.hpp>
#include <ExtCtrls.hpp>
#include "dslTLabeledPropertyEdit.h"
#include "dslProperty.h"
//---------------------------------------------------------------------------

using std::string;
using dsl::Property;

class PACKAGE TIntegerLabeledEdit : public TLabeledPropertyEdit
{
    public:
    	__fastcall    								TIntegerLabeledEdit(TComponent* Owner);

        int&                                        getReference();
        void                                        setReference(int& val);

                                                    //When assigning an external property, the directAcess boolean
                                                    //controls how the internal value of the external property is accessed.
                                                    //If directAcess is false, the
                                                    //VCL component is manipulating the propertys internal TEMPORARY value
                                                    //If direct access is true, the VCL component will access the external
                                                    //propertys value directly
        void                                        assignExternalProperty(Property<int>* prop, bool directAccess = false);
        virtual void                                update(void);


                                                    //Access value trough the property.
        int __fastcall                              getValue();
        void __fastcall                             setValue(int val);
        void                                        setValueFromString(const string& v);
        void __fastcall                             DerivedOnChange(TObject *Sender);
	  	Property<int>* 				          		getProperty();

    protected:

        int*                                        FValue;
        int                                         mDummy;
//        Property<int>*                              mProperty;
        bool                                        mDirectExternalPropertyAccess;
        DYNAMIC void __fastcall                     DoExit(void);
        DYNAMIC void __fastcall                     KeyDown(Word &Key, Classes::TShiftState Shift);


    __published:
                                                    //Use the property to access value directly
        __property int __fastcall                   Value = {read=getValue, write=setValue, default=0, stored=true};
        __property OnChange;
};

#endif
