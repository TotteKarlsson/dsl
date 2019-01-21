#ifndef dslIntEditPanelH
#define dslIntEditPanelH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include "DuneComponents.h"
#include "dslPackageDefs.h"

class TIntegerLabeledEdit;
//---------------------------------------------------------------------------
class PACKAGE TIntEditPanel : public TPanel
{
private:

protected:
    TIntegerLabeledEdit *theEdit;
public:
    __fastcall TIntEditPanel(TComponent* Owner);
    __fastcall ~TIntEditPanel();    
__published:
};
//---------------------------------------------------------------------------
#endif
