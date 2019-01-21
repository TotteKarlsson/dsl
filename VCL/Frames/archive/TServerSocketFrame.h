#ifndef TServerSocketFrameH
#define TServerSocketFrameH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ActnList.hpp>
#include <System.Win.ScktComp.hpp>
#include <StdActns.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <Menus.hpp>
#include "dslIntEdit.h"
#include <System.Actions.hpp>
#include <string>
#include "dslIntEdit.h"

using namespace std;
class TMemoSocketServer;
//---------------------------------------------------------------------------
class PACKAGE TServerSocketFrame : public TFrame
{
__published:    // IDE-managed Components
    TPanel *Panel2;
    TStatusBar *StatusBar1;
    TPopupMenu *SocketFramePopupMenu1;
    TActionList *SocketFrameActionList1;
    TAction *ToggleListening;
    TToolBar *ToolBar1;
    TBitBtn *BitBtn1;
    TPanel *Panel1;
    TMemo *logMemo;
    TMemo *writeMemo;
    TSplitter *Splitter1;
    TAction     *StartListening;
    TAction     *StopListening;
    TAction     *ClearLogMemoA;
    TMenuItem     *Clear1;
    TToolButton *ToolButton1;
    mtkIntEdit     *PortNrE;
    void __fastcall writeMemoKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall Memo1Change(TObject *Sender);
    void __fastcall ToggleListeningExecute(TObject *Sender);
    void __fastcall StartListeningExecute(TObject *Sender);
    void __fastcall StopListeningExecute(TObject *Sender);
    void __fastcall SocketFrameActionList1Update(TBasicAction *Action, bool &Handled);
    void __fastcall ClearLogMemoAExecute(TObject *Sender);

    private:
        String                            mAppFolder;
        TMemoSocketServer*                mServer;

    public:
                                __fastcall  TServerSocketFrame(TComponent* Owner);
                                __fastcall ~TServerSocketFrame();
        bool                    __fastcall  SendIPCMessage(const string& msg);
};
//---------------------------------------------------------------------------
extern PACKAGE TServerSocketFrame *ServerSocketFrame;
//---------------------------------------------------------------------------
#endif
