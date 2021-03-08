#ifndef dslTPropertyCheckBoxH
#define dslTPropertyCheckBoxH
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include "dslProperty.h"
using dsl::Property;

//---------------------------------------------------------------------------
class PACKAGE TPropertyCheckBox : public TCheckBox
{

    public:
        bool*                                       FValue;
                                    __fastcall      TPropertyCheckBox(TComponent* Owner);

        bool&                       __fastcall      getReference();
        void                        __fastcall      setReference(bool& val);

                                                    //When assigning an external property, the directAcess boolean
                                                    //controls how the internal value
                                                    //of the external property is accessed. If directAcess is false, the
                                                    //VCL component is manipulating the propertys internal TEMPORARY value
                                                    //If direct access is true, the VCL component will access the external
                                                    //propertys value directly
        void                        __fastcall      assignExternalProperty(dsl::Property<bool>* prop, bool directAccess = false);

        Property<bool>*             __fastcall      getProperty();
        void               			__fastcall      derivedOnClick(TObject *Sender);
        virtual void                __fastcall      update(void);

    protected:
        Property<bool>*                             mProperty;
        bool                                        mDirectExternalPropertyAccess;
        bool                                        mDummy;

                                                    //Access value trough the property.
        bool                        __fastcall      getValue();
        void                        __fastcall      setValue(bool val);


                                                    //Use the property to access value directly
    __published:
//        __property      							OnClick;
        __property bool                             Value = {read=getValue, write=setValue, default=false, stored=true};


};

#endif
