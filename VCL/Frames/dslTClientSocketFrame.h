#ifndef dslTClientSocketFrameH
#define dslTClientSocketFrameH
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
#include <System.Actions.hpp>
#include "dslTIntegerEdit.h"
#include "dslTSTDStringEdit.h"
#include <string>
#include "dslSocketClient.h"

using std::string;
using dsl::SocketClient;

//---------------------------------------------------------------------------
class PACKAGE TClientSocketFrame : public TFrame
{
__published:    // IDE-managed Components
    TPanel *Panel2;
    TStatusBar *StatusBar1;
    TPopupMenu *SocketFramePopupMenu1;
    TMenuItem *Connect1;
    TActionList *SocketFrameActionList1;
    TAction *ToggleConnection;
    TAction *ClearReceivedMemoA;
    TAction *Disconnect;
    TAction *Connect;
    TToolBar *ToolBar1;
    TComboBox *ServerCB;
    TBitBtn *BitBtn1;
	TMemo *ReceivedDataMemo;
    TMemo *ConsoleMemo;
    TSplitter *Splitter1;
    TTimer *ReconnectTimer;
    TCheckBox *AutoReconnectCB;
    TPopupMenu *ConsolePopup;
    TAction *ClearConsoleMemoA;
    TMenuItem *Clear1;
	TGroupBox *GroupBox1;
	TGroupBox *GroupBox2;
	TGroupBox *GroupBox3;
	TSTDStringEdit *STDStringEdit1;
	TButton *Button1;
	TIntegerEdit *PortNrE;
    void __fastcall ToggleConnectionExecute(TObject *Sender);
    void __fastcall DisconnectExecute(TObject *Sender);
    void __fastcall ConnectExecute(TObject *Sender);
    void __fastcall ConsoleMemoKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall ReconnectTimerTimer(TObject *Sender);
    void __fastcall ToggleConnectionUpdate(TObject *Sender);
    void __fastcall ClearReceivedMemoAExecute(TObject *Sender);
    void __fastcall ClearConsoleMemoAExecute(TObject *Sender);
    void __fastcall FrameExit(TObject *Sender);

private:
        int                         nrOfMessages;
        string                      lastMessage;
        SocketClient                mSocketClient;
        void                        onConnected(dsl::Socket* s);
        void                        onDisconnected(dsl::Socket* s);
        void                        onReceiveData(dsl::Socket* s);

public:
        String                      Server;
        TStatusBar*                 SB;
        long                        PortNr;
                        __fastcall  TClientSocketFrame(TComponent* Owner);
        string                      getLastMessage();
        int                         send(const string& msg);
        void                        setStatusBar(TStatusBar* sb);
};

extern PACKAGE TClientSocketFrame *ClientSocketFrame;
#endif
