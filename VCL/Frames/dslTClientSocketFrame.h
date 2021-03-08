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
    TActionList *SocketFrameActionList1;
    TAction *ToggleConnection;
    TAction *Disconnect;
    TAction *Connect;
    TToolBar *ToolBar1;
    TComboBox *ServerCB;
    TBitBtn *BitBtn1;
	TMemo *ReceivedDataMemo;
	TMemo *SentDataMemo;
    TSplitter *Splitter1;
    TTimer *ReconnectTimer;
    TCheckBox *AutoReconnectCB;
	TPopupMenu *MemosPopup;
	TAction *ClearSentDataMemoA;
    TMenuItem *Clear1;
	TGroupBox *GroupBox1;
	TGroupBox *GroupBox2;
	TGroupBox *GroupBox3;
	TSTDStringEdit *SendDataE;
	TButton *SendDataBtn;
	TIntegerEdit *PortNrE;
    void __fastcall ToggleConnectionExecute(TObject *Sender);
    void __fastcall DisconnectExecute(TObject *Sender);
    void __fastcall ConnectExecute(TObject *Sender);
    void __fastcall ReconnectTimerTimer(TObject *Sender);
    void __fastcall ToggleConnectionUpdate(TObject *Sender);
    void __fastcall ClearMemo(TObject *Sender);
    void __fastcall FrameExit(TObject *Sender);
	void __fastcall SendDataBtnClick(TObject *Sender);
	void __fastcall SendData(TObject *Sender, WORD &Key, TShiftState Shift);


private:
        SocketClient                mSocketClient;
        void                        onConnected(dsl::Socket* s);
        void                        onDisconnected(dsl::Socket* s);
        void                        onReceiveData(dsl::Socket* s);
        void                        onSentData(dsl::Socket* s);

public:
        String                      Server;
        TStatusBar*                 SB;

                        __fastcall  TClientSocketFrame(TComponent* Owner);

        int                         send(const string& msg);
        void                        setStatusBar(TStatusBar* sb);

};

extern PACKAGE TClientSocketFrame *ClientSocketFrame;
#endif
