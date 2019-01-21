//---------------------------------------------------------------------------

#ifndef dslProcessStatusFrameH
#define dslProcessStatusFrameH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <string>
using std::string;
//---------------------------------------------------------------------------
class TProcessStatusFrame : public TFrame
{
__published:    // IDE-managed Components
    TTimer *mStatusTimer;
    TSpeedButton *SpeedButton1;
    TActionList *ActionList1;
    TAction *StartStopA;
    TGroupBox *ProcessGB;
    TImageList *ImageList1;
    void __fastcall StartStopAExecute(TObject *Sender);
    void __fastcall mStatusTimerTimer(TObject *Sender);

private:    // User declarations
    string                      mExeName;    //To start executable
    string                      mExePath;
    unsigned int                mShutDownMessageID;
    bool    __fastcall          IsRunning();


public:        // User declarations
            __fastcall  TProcessStatusFrame(TComponent* Owner);
    bool    __fastcall  SetExecutable(const string& name);
    void    __fastcall  SetShutDownMessageID(const unsigned int& id){mShutDownMessageID = id;}
    bool    __fastcall  Start();
    bool    __fastcall  Stop();
    string  __fastcall  GetApplicationPathAndName(){return mExePath + mExeName;}

};
//---------------------------------------------------------------------------
extern PACKAGE TProcessStatusFrame *ProcessStatusFrame;
//---------------------------------------------------------------------------
#endif
