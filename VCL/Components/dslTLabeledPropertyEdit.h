#ifndef dslTLabeledPropertyEditH
#define dslTLabeledPropertyEditH
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <StdCtrls.hpp>
#include <ExtCtrls.hpp>
#include "dslBaseProperty.h"
//---------------------------------------------------------------------------
using std::string;
using dsl::BaseProperty;

class PACKAGE TLabeledPropertyEdit : public TLabeledEdit
{
	public:
    	                               __fastcall   TLabeledPropertyEdit(TComponent* Owner);
        virtual void                                setValueFromString(const string& v)  = 0;


//        string&                     __fastcall      getReference();
//        void                        __fastcall      setReference(string& val);

                                                    //When assigning an external property, the directAcess boolean
                                                    //controls how the internal value
                                                    //of the external property is accessed. If directAcess is false, the
                                                    //VCL component is manipulating the propertys internal EDIT value
                                                    //If direct access is true, the VCL component will access the external
                                                    //propertys value directly
//        void                        __fastcall      assignExternalProperty(Property<string>* prop, bool directAccess = false);
//        virtual void                __fastcall      update(void);
//        virtual void                __fastcall      updateFromCaption(void);
//        Property<string>*           __fastcall      getProperty();

        virtual BaseProperty*        			      getProperty();

//        string                      __fastcall      getValue();
//        void                        __fastcall      setValue(const string& value);
 //       void                        __fastcall      DerivedOnChange(TObject *Sender);

    protected:
        BaseProperty*      		                    mBaseProperty;
        bool                                        mDirectExternalPropertyAccess;
        DYNAMIC void                __fastcall      KeyDown(Word &Key, Classes::TShiftState Shift);


    __published:
//                                                    //Use the property to access value directly
//        __property String                           Value = {read=getStringValue, write=setStringValue, default=0, stored=true};
//        __property OnChange;
};

#endif
