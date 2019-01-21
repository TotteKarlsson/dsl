//---------------------------------------------------------------------------

#ifndef dslManagePluginsFormH
#define dslManagePluginsFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "dslPluginsFrame.h"
#include <ActnList.hpp>
#include <ExtCtrls.hpp>
#include <vector>
using std::vector;
//---------------------------------------------------------------------------
class mtkPluginManager;
class PACKAGE TmanagePluginsForm : public TForm
{
__published:    // IDE-managed Components
  TPanel *Panel1;
  TComboBox *pluginsCB;
  TActionList *ActionList1;
  TAction *FillPluginsCB;
  void __fastcall FillPluginsCBExecute(TObject *Sender);
  void __fastcall pluginsCBChange(TObject *Sender);
  void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:    // User declarations
  vector<mtkPluginManager *> *plugins;
public:        // User declarations
  __fastcall TmanagePluginsForm(vector<mtkPluginManager *>* pl, TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TmanagePluginsForm *managePluginsForm;
//---------------------------------------------------------------------------
#endif
