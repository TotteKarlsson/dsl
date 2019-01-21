//---------------------------------------------------------------------------

#ifndef TThreadHealthFrameH
#define TThreadHealthFrameH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ExtCtrls.hpp>
class mtkThread;
//---------------------------------------------------------------------------
class TThreadHealth : public TFrame
{
__published:    // IDE-managed Components
    TLabel *Label1;
    TLabel *Label2;
    TActionList *ActionList1;
    TButton *Button1;
    TAction *ToggleStartStopA;
    TTimer *Timer1;
    TAction *AbortThreadA;
    TLabel *mThreadNameLbl;
    TLabel *mThreadIDLbl;
    void __fastcall ToggleStartStopAExecute(TObject *Sender);
    void __fastcall Timer1Timer(TObject *Sender);

private:    // User declarations
    mtkThread*  mTheThread;

public:        // User declarations
    __fastcall TThreadHealth(TComponent* Owner);
    void       SetThread(mtkThread* aThread);
    void       StartMonitor();
    void       StopMonitor();
};
//---------------------------------------------------------------------------
extern PACKAGE TThreadHealth *ThreadHealth;
//---------------------------------------------------------------------------
#endif
