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
        virtual BaseProperty*        		      	getProperty();

    protected:
        BaseProperty*      		                    mBaseProperty;
        bool                                        mDirectExternalPropertyAccess;
        DYNAMIC void                __fastcall      KeyDown(Word &Key, Classes::TShiftState Shift);

    __published:
};

#endif
