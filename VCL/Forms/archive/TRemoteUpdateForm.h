#ifndef TRemoteUpdateFormH
#define TRemoteUpdateFormH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include "dslTURLLabel.h"
#include "dslGetRemoteTextFileDataThread.h"
#include "dslTURLLabel.h"
#include <string>
//---------------------------------------------------------------------------
using std::string;

class PACKAGE TRemoteUpdateForm : public TForm
{
__published:	// IDE-managed Components
    TMemo *Memo1;
    TPanel *Panel2;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *currentVersionLbl;
    TLabel *remoteVersionLbl;
    TURLLabel *remoteDownloadURL;
    TGroupBox *GroupBox1;
    TPanel *Panel1;
    TButton *Button1;
    TLabel *mNetStatus;
    TTimer *mStatusTimer;
    void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall mStatusTimerTimer(TObject *Sender);

private:
    dsl::GetRemoteTextFileDataThread    mGetRemoteVersionDataThread;
    string                              mRemoteDownloadURL;
    void                __fastcall      NotifyAboutUpdate(const string& data);

public:
                        __fastcall      TRemoteUpdateForm(const string& remoteDownLoadURL, TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TRemoteUpdateForm *RemoteUpdateForm;
//---------------------------------------------------------------------------
#endif
