#ifndef Unit1H
#define Unit1H
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>

#include "dslTSTDStringLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
#include "dslProcess.h"

#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include "dslTLogMemoFrame.h"

using dsl::Process;
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
    __published:	// IDE-managed Components
        TSTDStringLabeledEdit *ExecutableE;
        TSTDStringLabeledEdit *ParametersE;
        TButton *RunBtn;
	TLogMemoFrame *LogMemoFrame1;
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
        void __fastcall RunBtnClick(TObject *Sender);

    private:	// User declarations
        Process         mAProcess;
        void            onProcessStarted(void* arg1, void* arg2);
        void            onProcessProgress(void* arg1, void* arg2);
        void            onProcessFinished(void* arg1, void* arg2);

    public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
