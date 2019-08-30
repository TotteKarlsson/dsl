#ifndef dslTSTDStringLabeledEditH
#define dslTSTDStringLabeledEditH
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <StdCtrls.hpp>
#include <ExtCtrls.hpp>
#include "dslProperty.h"
#include "dslTLabeledPropertyEdit.h"
//---------------------------------------------------------------------------
using std::string;
using dsl::Property;

class PACKAGE TSTDStringLabeledEdit : public TLabeledPropertyEdit
{
    public:
                                    __fastcall      TSTDStringLabeledEdit(TComponent* Owner);
        string&                                     getReference();
        void                                        setReference(string& val);
        void                                        setValueFromString(const string&);

                                                    //When assigning an external property, the directAcess boolean
                                                    //controls how the internal value
                                                    //of the external property is accessed. If directAcess is false, the
                                                    //VCL component is manipulating the propertys internal EDIT value
                                                    //If direct access is true, the VCL component will access the external
                                                    //propertys value directly
        void                                        assignExternalProperty(Property<string>* prop, bool directAccess = false);
        virtual void                                update(void);
        virtual void                                updateFromCaption(void);
        Property<string>*                           getProperty();

        string                      		      	getValue();
        void                              			setValue(const string& value);
        void                        __fastcall      DerivedOnChange(TObject *Sender);

    protected:
        string*                                     FValue;
        string                                      mDummy;

                                                    //Access value trough the property.
        String                      __fastcall      getStringValue();
		void 						__fastcall		setValueFromUnicodeString(const String& val);
        DYNAMIC void                __fastcall      DoExit(void);
//        DYNAMIC void                __fastcall      KeyDown(Word &Key, Classes::TShiftState Shift);


    __published:
                                                    //Use the property to access value directly
        __property String                           Value = {read=getStringValue, write=setValueFromUnicodeString, default=0, stored=true};
        __property OnChange;
};

#endif
