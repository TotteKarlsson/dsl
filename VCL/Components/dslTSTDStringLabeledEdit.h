#ifndef dslTSTDStringLabeledEditH
#define dslTSTDStringLabeledEditH
#include <SysUtils.hpp>
#include <Controls.hpp>
#include <Classes.hpp>
#include <Forms.hpp>
#include <StdCtrls.hpp>
#include <ExtCtrls.hpp>
#include "dslProperty.h"
//---------------------------------------------------------------------------
using std::string;
using dsl::Property;

class PACKAGE TSTDStringLabeledEdit : public TLabeledEdit
{
    public:
                                    __fastcall      TSTDStringLabeledEdit(TComponent* Owner);


        string&                     __fastcall      getReference();
        void                        __fastcall      setReference(string& val);

                                                    //When assigning an external property, the directAcess boolean
                                                    //controls how the internal value
                                                    //of the external property is accessed. If directAcess is false, the
                                                    //VCL component is manipulating the propertys internal EDIT value
                                                    //If direct access is true, the VCL component will access the external
                                                    //propertys value directly
        void                        __fastcall      assignExternalProperty(Property<string>* prop, bool directAccess = false);
        virtual void                __fastcall      update(void);
        virtual void                __fastcall      updateFromCaption(void);
        Property<string>*           __fastcall      getProperty();

        string                      __fastcall      getValue();
        void                        __fastcall      setValue(const string& value);
        void                        __fastcall      DerivedOnChange(TObject *Sender);

    protected:
        string*                                     FValue;
        string                                      mDummy;
        Property<string>*                           mProperty;

        bool                                        mDirectExternalPropertyAccess;


                                                    //Access value trough the property.

        String                      __fastcall      getStringValue();

        void                        __fastcall      setStringValue(String value);

        DYNAMIC void                __fastcall      DoExit(void);
        DYNAMIC void                __fastcall      KeyDown(Word &Key, Classes::TShiftState Shift);


    __published:
                                                    //Use the property to access value directly
        __property String                           Value = {read=getStringValue, write=setStringValue, default=0, stored=true};
        __property OnChange;
};

#endif
