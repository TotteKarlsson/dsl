#ifndef TMainFormH
#define TMainFormH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "dslTPluginManager.h"
#include "dslTLogFileReader.h"
#include <Vcl.ExtCtrls.hpp>
#include "dslTLogFileReader.h"
#include "dslTPluginManager.h"
#include "dslTAboutFrame.h"
#include "dslTPluginInfoFrame.h"
#include "PythonPlugins/dslPythonPluginManager.h"
#include "PythonPlugins/dslPythonInterpreterDSL.h"
#include "dslTLogMemoFrame.h"
//---------------------------------------------------------------------------

using dsl::TPluginInfoFrame;
using dsl::PythonPluginManager;
using dsl::PythonInterpreterDSL;

//---------------------------------------------------------------------------
class TMainForm : public TForm
{
    __published:	// IDE-managed Components
		TTimer *ShutDownTimer;
		TPluginManager *PluginManager1;
		TPanel *Panel1;
		TControlBar *ControlBar1;
		TPanel *Panel2;
		TButton *LoadPluginsBtn;
		TButton *GetPluginsInfoBtn;
		TGroupBox *PythonGB;
		TListBox *PluginsLB;
		TLogMemoFrame *TLogMemoFrame1;
        void __fastcall LoadPluginsBtnClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
		void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
		void __fastcall ShutDownTimerTimer(TObject *Sender);
		void __fastcall PythonPluginsLBClick(TObject *Sender);

    private:
        TPluginInfoFrame*   		PluginInfoFrame;
		Plugin*						getSelectedPlugin();
        PythonPluginManager    		mPythonPM;
        PythonInterpreterDSL        mDSLPython;
        void     					loadPythonPlugins();

    public:
        				__fastcall 	TMainForm(TComponent* Owner);
        				__fastcall 	~TMainForm();

        TPluginInfoFrame*           getPluginInfoFrame(Plugin* p);
        void                        setLogMemoMessage(UnicodeString Msg);
};

extern PACKAGE TMainForm *MainForm;
#endif
