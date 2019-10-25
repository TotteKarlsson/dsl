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
    nrOfMessages = 0;
    BitBtn1->Caption = "Connect";
    mSocketClient.onConnected 		= boost::bind(&TClientSocketFrame::onConnected, this, _1);
    mSocketClient.onDisconnected 	= boost::bind(&TClientSocketFrame::onDisconnected, this, _1);
    mSocketClient.onReceiveData 	= boost::bind(&TClientSocketFrame::onReceiveData, this, _1);
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
    ConsoleMemo->Clear();
    ReceivedDataMemo->Clear();
    BitBtn1->Caption = "Disconnect";
    StatusBar1->Panels->Items[0]->Text = vclstr("Connected to: " + s->getRemoteHostName());
    nrOfMessages = 0;
//	mSocketClient.

}

void TClientSocketFrame::onDisconnected(Socket* s)
{
    BitBtn1->Caption = "Connect";
    if(SB)
        SB->Panels->Items[0]->Text = "Disconnected...";

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

string TClientSocketFrame::getLastMessage()
{
	return lastMessage;
}

////---------------------------------------------------------------------------
//void __fastcall TClientSocketFrame::ClientSocketError(TObject *Sender,
//      TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
//{
//  ReceivedDataMemo->Lines->Add("Error connecting to:" + Server + " on port number " + Sysutils::IntToStr(PortNrE->getValue()) );
//  ReceivedDataMemo->Lines->Add("The error code was: " + Sysutils::IntToStr(ErrorCode) );
//  //switch(ErrorCode)
////  {
////    case eeGeneral:         break;
////    case eeSend:            break;
////    case eeReceive:         break;
////    case eeConnect:         break;
////    case eeDisconnect:      break;
////    case eeAccept:          break;
////
////    default:    break;
////  }
//    mSocketClient.close();
//    ErrorCode = 0;        //Don't raise an exception
//    BitBtn1->Caption = "Connect";
//    if(SB)
//        SB->Panels->Items[0]->Text = "Disconnected...";
//}

////---------------------------------------------------------------------------
//void __fastcall TClientSocketFrame::mSocketClientRead(TObject *Sender, TCustomWinSocket *Socket)
//{
//    lastMessage = Socket->ReceiveText().c_str();
//    vector<string> strs;
//    strs = splitString(lastMessage, "\n");
//    for(unsigned int i=0; i < strs.size(); i++)
//    {
//        if(strs[i].size())
//            ReceivedDataMemo->Lines->Add(strs[i].c_str());
//    }
//}
//
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
    PortNr = PortNrE->getValue();
    if (Server.Length() < 1)
    {
        MessageDlg("Assign a valid server!", mtWarning, TMsgDlgButtons() << mbOK, 0);
        return;
    }

    mSocketClient.connect(PortNrE->getValue(), stdstr(Server));
}

//---------------------------------------------------------------------------
void __fastcall TClientSocketFrame::ConsoleMemoKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if (Key == VK_RETURN && !Shift.Contains(ssShift))
    {
        string msg;
        for(int i = 0; i < ConsoleMemo->Lines->Count; i++)
        {
            msg = msg + stdstr(ConsoleMemo->Lines->Strings[i]);
        }
        //Add newline
        msg += '\n';
        send(msg.c_str());
        ClearConsoleMemoAExecute(Sender);
      }
}

int TClientSocketFrame::send(const string& msg)
{
    bool res = mSocketClient.request(msg);
    ReceivedDataMemo->Lines->Add(vclstr("Response: " + dsl::toString(res)));
    return 0;
}

//void __fastcall TClientSocketFrame::mSocketClientConnecting(TObject *Sender, TCustomWinSocket *Socket)
//{
//    BitBtn1->Caption = "Connecting..";
//    if(SB)
//    {
//        SB->Panels->Items[0]->Text = "Connecting...";
//    }
//}

//---------------------------------------------------------------------------
//void __fastcall TClientSocketFrame::mSocketClientLookup(TObject *Sender, TCustomWinSocket *Socket)
//{
//    BitBtn1->Caption = "Connecting..";
//    if(SB)
//    {
//        SB->Panels->Items[0]->Text = "Connecting...";
//    }
//}

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
void __fastcall TClientSocketFrame::ClearReceivedMemoAExecute(TObject *Sender)
{
    ReceivedDataMemo->Clear();
}

//---------------------------------------------------------------------------
void __fastcall TClientSocketFrame::ClearConsoleMemoAExecute(TObject *Sender)
{
    ConsoleMemo->Clear();
}

//---------------------------------------------------------------------------
void __fastcall TClientSocketFrame::FrameExit(TObject *Sender)
{
    setStatusBar(nullptr);
}



