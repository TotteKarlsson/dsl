#ifndef dslTLogMemoFrameH
#define dslTLogMemoFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "dslTLogFileReader.h"
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include "dslLogLevel.h"
//---------------------------------------------------------------------------

//!The LogMemo frame is a simple way to get logs into a window
//!The logfile is taken from the global logger
class PACKAGE TLogMemoFrame : public TFrame
{
    __published:	// IDE-managed Components
	TPanel *LogPanel;
	TGroupBox *LogGroupBox;
        TToolBar *ToolBar1;
        TBitBtn *mClearLogMemoBtn;
        TComboBox *LogLevelCB;
        TMemo *infoMemo;
		TLogFileReader *LogFileReader1;
		void __fastcall mClearLogMemoBtnClick(TObject *Sender);
		void __fastcall LogLevelCBCloseUp(TObject *Sender);

	private:

	public:
						__fastcall TLogMemoFrame(TComponent* Owner);
						__fastcall ~TLogMemoFrame();
        void                       	init();
        void                        setLogLevel(dsl::LogLevel lvl);
};

extern PACKAGE TLogMemoFrame *LogMemoFrame;
#endif
