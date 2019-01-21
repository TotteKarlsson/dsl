#ifndef dslTPluginInfoFrameH
#define dslTPluginInfoFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "dslTSTDStringLabeledEdit.h"
#include <Vcl.ComCtrls.hpp>
//---------------------------------------------------------------------------

namespace dsl
{

class Plugin;
class Properties;
class PACKAGE TPluginInfoFrame : public TFrame
{
    __published:
        TGroupBox *GroupBox2;
		TSTDStringLabeledEdit *PluginNameE;
		TGroupBox *GroupBox1;
		TPanel *Panel1;
		TFlowPanel *PropertiesPanel;
		TTimer *RunningTimer;
		TButton *WorkerButton;
	TProgressBar *ProgressBar1;
		void __fastcall RunningTimerTimer(TObject *Sender);
		void __fastcall WorkerButtonClick(TObject *Sender);

    private:
        Plugin*         		mPlugin;
        Properties*     		mProperties;
        vector<TPanel*>     	mVisualControls;
        bool                    clearVisualControls();

    public:
        __fastcall 	TPluginInfoFrame(Plugin* p, TComponent* Owner);
        bool        populate(Plugin* p);
        void        showProgress(int pos);
};

extern PACKAGE TPluginInfoFrame *PluginInfoFrame;
}

#endif
