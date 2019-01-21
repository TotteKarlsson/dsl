#ifndef TPluginsFrameH
#define TPluginsFrameH
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <CheckLst.hpp>
#include <ExtCtrls.hpp>
#include <ActnList.hpp>
#include "dslPluginManager.h"
#include <System.Actions.hpp>
//---------------------------------------------------------------------------

class PACKAGE TPluginsFrame : public TFrame {
__published:	// IDE-managed Components
	TActionList *ActionList1;
	TGroupBox *GroupBox4;
	TGroupBox *GroupBox2;
	TCheckListBox *CheckListBox1;
	TLabel *PluginFolderLbl;
	TAction *Toolbars;
  	void __fastcall CheckListBox1Click(TObject *Sender);

    private:
    	void 					FillFileList(TStrings* list);
      	dsl::PluginManager*		Plugins;

    public:
      			__fastcall 		TPluginsFrame(TComponent* Owner);
    	void 					SetPlugins(dsl::PluginManager *plugins);
};

extern PACKAGE TPluginsFrame *PluginsFrame;
#endif
