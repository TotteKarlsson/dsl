#include <vcl.h>
#pragma hdrstop
#include "TRemoteUpdateForm.h"
#include "dslUtils.h"
#include "dslVCLUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslURLLabel"
#pragma resource "*.dfm"
TRemoteUpdateForm *RemoteUpdateForm;

using namespace dsl;
//---------------------------------------------------------------------------
__fastcall TRemoteUpdateForm::TRemoteUpdateForm(const string& remoteDownLoadURL, TComponent* Owner)
:
TForm(Owner),
mRemoteDownloadURL(remoteDownLoadURL)
{
    //Start remote download of latest changelog
    mGetRemoteVersionDataThread.setURL(joinPath(remoteDownLoadURL,"CHANGELOG.txt",'/'));
    mGetRemoteVersionDataThread.assignCallBack(NotifyAboutUpdate);
    mGetRemoteVersionDataThread.start();
    mStatusTimer->Enabled = true;
    mNetStatus->Caption = "";
}

void __fastcall TRemoteUpdateForm::NotifyAboutUpdate(const string& data)
{
    StringList lines(data, '\n');
    //Check that this is indeed a CHANGELOG.
    //The Changelog first line contain firstr word release.
    //If not.. this is probably an error document.. discard..
    if(lines.size())
    {
        StringList firstLine(lines[0],' ');
        if(firstLine.size())
        {
            if(!compareNoCase(firstLine[0], "Release"))
            {
                Memo1->Lines->Add("There was a problem: Failed retrieving remote ChangeLog data");
                Memo1->SelStart = 0;//Memo1->GetTextLen();
                Memo1->Perform(EM_SCROLLCARET, 0, 0);
                return;
            }
        }
    }

    for(size_t i = 0; i < lines.size(); i++)
    {
        Memo1->Lines->Add(vclstr(lines[i]));
    }

    //Scroll to begining
    Memo1->SelStart = 0;//Memo1->GetTextLen();
    Memo1->Perform(EM_SCROLLCARET, 0, 0);
}

//---------------------------------------------------------------------------
void __fastcall TRemoteUpdateForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if(Key == VK_ESCAPE)
    {
        Close();
    }
}

void __fastcall TRemoteUpdateForm::mStatusTimerTimer(TObject *Sender)
{
    if(mGetRemoteVersionDataThread.isRunning())
    {
        mNetStatus->Caption = "";//"Trying to retrieve remote data...";
        return;
    }

    if(mGetRemoteVersionDataThread.isFinished())
    {
        //Check is succesfull.
        mNetStatus->Caption = "";
        mStatusTimer->Enabled = false;

        //If not successfull
        return;
    }
}

