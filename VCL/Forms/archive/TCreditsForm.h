#ifndef TCreditsFormH
#define TCreditsFormH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------

class TCreditsForm : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TPanel *Panel2;
    TImage *creditsImage;
    TLabel *ProgramLabel;
    TMemo *creditsMemo;
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall Panel2Click(TObject *Sender);

private:	// User declarations
public:		// User declarations
    __fastcall TCreditsForm(TComponent* Owner);
};

extern PACKAGE TCreditsForm *CreditsForm;

#endif
