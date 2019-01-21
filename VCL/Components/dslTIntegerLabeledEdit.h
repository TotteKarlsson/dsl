#ifndef TIntegerLabeledEditH
#define TIntegerLabeledEditH
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

class PACKAGE TIntegerLabeledEdit : public TLabeledEdit
{
    public:
                                    __fastcall      TIntegerLabeledEdit(TComponent* Owner);

        int&                        __fastcall      getReference();
        void                        __fastcall      setReference(int& val);

                                                    //When assigning an external property, the directAcess boolean
                                                    //controls how the internal value of the external property is accessed.
                                                    //If directAcess is false, the
                                                    //VCL component is manipulating the propertys internal TEMPORARY value
                                                    //If direct access is true, the VCL component will access the external
                                                    //propertys value directly
        void                        __fastcall      assignExternalProperty(Property<int>* prop, bool directAccess = false);
        virtual void                __fastcall      update(void);
        Property<int>*              __fastcall      getProperty();

                                                    //Access value trough the property.
        int                         __fastcall      getValue();
        void                        __fastcall      setValue(int val);
        void                        __fastcall      DerivedOnChange(TObject *Sender);

    protected:
        int*                                        FValue;
        int                                         mDummy;
        Property<int>*                              mProperty;
        bool                                        mDirectExternalPropertyAccess;
        DYNAMIC void                __fastcall      DoExit(void);
        DYNAMIC void                __fastcall      KeyDown(Word &Key, Classes::TShiftState Shift);


    __published:
                                                    //Use the property to access value directly
        __property int                              Value = {read=getValue, write=setValue, default=0, stored=true};
        __property OnChange;
};

#endif
