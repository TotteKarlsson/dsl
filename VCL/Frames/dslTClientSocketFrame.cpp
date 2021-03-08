#pragma hdrstop
#include <string>
#include <vector>
#include "dslTClientSocketFrame.h"
#include "dslUtils.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"
#include <boost/bind.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTIntegerEdit"
#pragma link "dslTSTDStringEdit"
#pragma resource "*.dfm"

using namespace std;
using namespace dsl;

TClientSocketFrame *ClientSocketFrame;

//---------------------------------------------------------------------------
__fastcall TClientSocketFrame::TClientSocketFrame(TComponent* Owner)
    :
    TFrame(Owner),
    SB(nullptr),
    mSocketClient()
{
    BitBtn1->Caption = "Connect";
    mSocketClient.onConnected 		= boost::bind(&TClientSocketFrame::onConnected, this, _1);
    mSocketClient.onDisconnected 	= boost::bind(&TClientSocketFrame::onDisconnected, this, _1);
    mSocketClient.onReceiveData 	= boost::bind(&TClientSocketFrame::onReceiveData, this, _1);
    mSocketClient.onSendData 		= boost::bind(&TClientSocketFrame::onSentData, this, _1);
}

//---------------------------------------------------------------------------
void TClientSocketFrame::setStatusBar(TStatusBar* sb)
{
    StatusBar1->Visible = false;
    SB = sb;
}

void TClientSocketFrame::onConnected(Socket* s)
{
    Log(lInfo) << "Socket with ID: " << s->getSocketID() <<" was connected";
    SentDataMemo->Clear();
    ReceivedDataMemo->Clear();
    BitBtn1->Caption = "Disconnect";
    StatusBar1->Panels->Items[0]->Text = vclstr("Connected to: " + s->getRemoteHostName());
}

void TClientSocketFrame::onDisconnected(Socket* s)
{
    BitBtn1->Caption = "Connect";
    if(SB)
    {
    	SB->Panels->Items[0]->Text = "Disconnected...";
    }
}

void TClientSocketFrame::onReceiveData(dsl::Socket* s)
{
    if(!s)
    {
        return;
    }

    //Get received data
	string receivedData = s->getReceivedBufferContent();
    ReceivedDataMemo->Lines->Append(vclstr(receivedData));
}

void TClientSocketFrame::onSentData(dsl::Socket* s)
{
    if(!s)
    {
        return;
    }

    //Get sent data
	string data = s->getLastSentData();
    SentDataMemo->Lines->Append(vclstr(data));
}

//---------------------------------------------------------------------------
void __fastcall TClientSocketFrame::ToggleConnectionExecute(TObject *Sender)
{
     mSocketClient.isConnected() ? DisconnectExecute(Sender) : ConnectExecute(Sender);
}

//---------------------------------------------------------------------------
void __fastcall TClientSocketFrame::DisconnectExecute(TObject *Sender)
{
  mSocketClient.disConnect();
  BitBtn1->Caption = "Connect";
  if(SB)
  {
      SB->Panels->Items[0]->Text = "Disconnected...";
  }
}

//---------------------------------------------------------------------------
void __fastcall TClientSocketFrame::ConnectExecute(TObject *Sender)
{
    if (mSocketClient.isConnected())
    {
        return;
    }

    Server = ServerCB->Text;

    if(Server.Length() < 1)
    {
        Log(lError) << "Please assign a valid server..";
        return;
    }

    mSocketClient.connect(PortNrE->getValue(), stdstr(Server));
}

//---------------------------------------------------------------------------
int TClientSocketFrame::send(const string& msg)
{
    bool res = mSocketClient.request(msg);
    return 0;
}

//---------------------------------------------------------------------------
void __fastcall TClientSocketFrame::ReconnectTimerTimer(TObject *Sender)
{
    //Try to reconnect to server
    ConnectExecute(Sender);
}

//---------------------------------------------------------------------------
void __fastcall TClientSocketFrame::ToggleConnectionUpdate(TObject *Sender)
{
    //Code when the connection status changes
    if(mSocketClient.isConnected())
    {
        ReconnectTimer->Enabled = false;    //turn off the reconnect timer
    }
    else
    {
        AutoReconnectCB->Enabled = true;
        ReconnectTimer->Enabled = AutoReconnectCB->Checked;
    }
}

//---------------------------------------------------------------------------
void __fastcall TClientSocketFrame::ClearMemo(TObject *Sender)
{

    TMemo* memo = dynamic_cast<TMemo*>(MemosPopup->PopupComponent);
	if(memo)
    {
        memo->Clear();
    }
}

//---------------------------------------------------------------------------
void __fastcall TClientSocketFrame::FrameExit(TObject *Sender)
{
    setStatusBar(nullptr);
}

//---------------------------------------------------------------------------
void __fastcall TClientSocketFrame::SendDataBtnClick(TObject *Sender)
{
	send(SendDataE->getValue());
}

//---------------------------------------------------------------------------
void __fastcall TClientSocketFrame::SendData(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
    if (Key == VK_RETURN)
    {
        send(SendDataE->getValue());
    }
}



