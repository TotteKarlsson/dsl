#pragma hdrstop
#include "dslTServerSocketFrame.h"
#include <sstream>
#include "dslUtils.h"
#include "dslTMemoSocketServer.h"
#include "dslSocketServer.h"
#include "dslVCLUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTIntegerEdit"
#pragma resource "*.dfm"

using std::stringstream;
using namespace dsl;
TServerSocketFrame *ServerSocketFrame;

//---------------------------------------------------------------------------
__fastcall TServerSocketFrame::TServerSocketFrame(TComponent* Owner)
    :
    TFrame(Owner),
    mServer(dsl_shared_ptr<TMemoSocketServer>(new TMemoSocketServer("MemoSocket.ini", "GENERAL")))
{

    mAppFolder = GetCurrentDir().c_str();
    BitBtn1->Caption = "Start server";
    StatusBar1->Panels->Items[0]->Text = "Not serving..";
}

//---------------------------------------------------------------------------
__fastcall TServerSocketFrame::~TServerSocketFrame()
{}

//---------------------------------------------------------------------------
void __fastcall TServerSocketFrame::Memo1Change(TObject *Sender)
{
	string msg = stdstr(writeMemo->Lines->Strings[ writeMemo->Lines->Count -1 ]);
    mServer->broadcast(msg);
}

//---------------------------------------------------------------------------
void __fastcall TServerSocketFrame::ToggleListeningExecute(TObject *Sender)
{
    mServer->isRunning() ?  StopListeningExecute(Sender) : StartListeningExecute(Sender);
}

//---------------------------------------------------------------------------
void __fastcall TServerSocketFrame::StartListeningExecute(TObject *Sender)
{
    if (mServer->isRunning())
    {
        MessageDlg("Already listening", mtWarning, TMsgDlgButtons() << mbOK, 0);
        return;
    }

    int portNr = PortNrE->getValue();
    if(!mServer->init(portNr))
    {
        MessageDlg("Failed to start server", mtWarning, TMsgDlgButtons() << mbOK, 0);
    }
    else
    {
        mServer->SetMemo(logMemo);
        BitBtn1->Caption = "Stop server";
    }
}
//---------------------------------------------------------------------------
void __fastcall TServerSocketFrame::StopListeningExecute(TObject *Sender)
{
    mServer->shutDown();
    BitBtn1->Caption = "Start server";
}

bool __fastcall TServerSocketFrame::SendIPCMessage(const string& msg)
{
    mServer->broadcast(msg.c_str());
    return true;
}

void __fastcall TServerSocketFrame::writeMemoKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (Key == VK_RETURN)
    {
    	string msg = stdstr(writeMemo->Lines->Strings[ writeMemo->Lines->Count -1 ]);
	    SendIPCMessage(msg);
    }
}

void __fastcall TServerSocketFrame::SocketFrameActionList1Update(TBasicAction *Action, bool &Handled)
{
    int nrOfClients = mServer->getNumberOfClients();
    StatusBar1->Panels->Items[1]->Text = "Nr of clients: " + Sysutils::IntToStr(nrOfClients);
    if(mServer->isRunning())
    {
        StatusBar1->Panels->Items[0]->Text = "Listening on port " + Sysutils::IntToStr(mServer->servingPort());
    }
    else
    {
        StatusBar1->Panels->Items[0]->Text = "Not serving..";
    }
}

void __fastcall TServerSocketFrame::ClearLogMemoAExecute(TObject *Sender)
{
    logMemo->Clear();
}

