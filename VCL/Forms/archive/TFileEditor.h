//---------------------------------------------------------------------------
#ifndef TFileEditorH
#define TFileEditorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ActnList.hpp>
#include <Dialogs.hpp>
#include <StdActns.hpp>
#include <System.Actions.hpp>
#include <vector>
#include "dslStringList.h"
//---------------------------------------------------------------------------
using std::string;
using std::vector;
using dsl::StringList;

//Make this to a mtkChild
class PACKAGE TFileEditor : public TForm
{
__published:    // IDE-managed Components
    TPanel *Panel1;
    TGroupBox *GroupBox1;
    TLabel *Label1;
    TMemo *Memo1;
    TActionList *ActionList1;
    TAction *SaveFileAction1;
    TButton *SaveBtn;
    TAction *ReloadFileAction;
    TButton *ReloadButton;
    TButton *SaveAsBtn;
    TSaveDialog *SaveDialog1;
    TAction *SaveAsAction;
    TEditCopy *EditCopy1;
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall SaveFileAction1Execute(TObject *Sender);
    void __fastcall ReloadFileActionExecute(TObject *Sender);
    void __fastcall SaveAsActionExecute(TObject *Sender);
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);


private:

public:
                    __fastcall TFileEditor(const StringList& strs,      TApplication* Owner);
//                    __fastcall TFileEditor(TStrings* strs,                TApplication* Owner);
//                    __fastcall TFileEditor(const string& fileN, bool createNew = false, TApplication* Owner = nullptr);
    bool            __fastcall Read(const string& file);
    bool            __fastcall Write(const string& file);
    void            __fastcall UpdateWindow();
};
//---------------------------------------------------------------------------
extern PACKAGE TFileEditor *FileEditor;
//---------------------------------------------------------------------------
#endif
