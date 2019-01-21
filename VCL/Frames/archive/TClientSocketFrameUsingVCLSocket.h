#ifndef TClientSocketFrameUsingVCLSocketH
#define TClientSocketFrameUsingVCLSocketH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include <ExtCtrls.hpp>
#include <ActnList.hpp>
#include <ScktComp.hpp>
#include <StdActns.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <Menus.hpp>
#include "dslIntEdit.h"
#include <System.Actions.hpp>
#include "TIntegerLabeledEdit.h"
#include <string>

using std::string;
//---------------------------------------------------------------------------
class PACKAGE TClientSocketFrame : public TFrame
{
__published:    // IDE-managed Components
    TPanel *Panel2;
    TClientSocket *ClientSocket;
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
    TPanel *Panel1;
    TMemo *RecMsgMemo;
    TMemo *ConsoleMemo;
    TSplitter *Splitter1;
    TTimer *ReconnectTimer;
    TCheckBox *AutoReconnectCB;
    TPopupMenu *ConsolePopup;
    TAction *ClearConsoleMemoA;
    TMenuItem *Clear1;
    TIntegerLabeledEdit *PortNrE;
    void __fastcall ClientSocketConnect(TObject *Sender, TCustomWinSocket *Socket);
    void __fastcall ClientSocketDisconnect(TObject *Sender, TCustomWinSocket *Socket);
    void __fastcall ClientSocketError(TObject *Sender, TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode);
    void __fastcall ClientSocketRead(TObject *Sender, TCustomWinSocket *Socket);
    void __fastcall ToggleConnectionExecute(TObject *Sender);
    void __fastcall DisconnectExecute(TObject *Sender);
    void __fastcall ConnectExecute(TObject *Sender);
    void __fastcall ConsoleMemoKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall ClientSocketConnecting(TObject *Sender, TCustomWinSocket *Socket);
    void __fastcall ClientSocketLookup(TObject *Sender,    TCustomWinSocket *Socket);
    void __fastcall ReconnectTimerTimer(TObject *Sender);
    void __fastcall ToggleConnectionUpdate(TObject *Sender);
    void __fastcall ClearReceivedMemoAExecute(TObject *Sender);
    void __fastcall ClearConsoleMemoAExecute(TObject *Sender);
    void __fastcall FrameExit(TObject *Sender);

private:
        int                         nrOfMessages;
        string                      lastMessage;

public:
        String                      Server;
        TStatusBar*                 SB;
        long                        PortNr;
                        __fastcall  TClientSocketFrame(TComponent* Owner);
        string          __fastcall  GetLastMessage(){return lastMessage;}
        int             __fastcall  Send(const string& msg);
        void            __fastcall  SetStatusBar(TStatusBar* sb);
};
//---------------------------------------------------------------------------
extern PACKAGE TClientSocketFrame *ClientSocketFrame;
//---------------------------------------------------------------------------
#endif
