
#pragma hdrstop
#include "TIntegerLabeledEdit.h"
#include "dslIntEditPanel.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TIntEditPanel *)
{
    new TIntEditPanel(nullptr);
}
//---------------------------------------------------------------------------
__fastcall TIntEditPanel::TIntEditPanel(TComponent* Owner)
    : TPanel(Owner)
{
    theEdit = new TIntegerLabeledEdit(this);
//    theEdit->EditLabel->Caption = "test";
    theEdit->Parent = this;
//    theEdit->Align = alClient;
}
//---------------------------------------------------------------------------
__fastcall TIntEditPanel::~TIntEditPanel()
{
    delete theEdit;
}

namespace Mtkinteditpanel
{
    void __fastcall PACKAGE Register()
    {
        TComponentClass classes[1] = {__classid(TIntEditPanel)};
        RegisterComponents(dslComponents::gDuneEditPanels, classes, 0);
    }
}
//---------------------------------------------------------------------------
