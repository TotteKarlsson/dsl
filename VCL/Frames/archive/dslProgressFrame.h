//---------------------------------------------------------------------------


#ifndef dslProgressFrameH
#define dslProgressFrameH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//#include "dslFloatLabel.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class PACKAGE TProgressFrame : public TFrame
{
__published:    // IDE-managed Components
    TPanel *Panel1;
    TProgressBar *ProgressBar1;
    TPanel *Panel2;
    TLabel *progressLbl;
private:    // User declarations
public:        // User declarations
    __fastcall TProgressFrame(TComponent* Owner);
    void __fastcall StepBy(const int&);
    int __fastcall Max();
    void  __fastcall SetPos(int pos);
    void __fastcall  SetPos(const String& pos);
    void __fastcall SetBarColor(int color);    
};
//---------------------------------------------------------------------------
//extern PACKAGE TProgressFrame *ProgressFrame;
//---------------------------------------------------------------------------
#endif
