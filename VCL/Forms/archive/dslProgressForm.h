//---------------------------------------------------------------------------
#ifndef dslProgressFormH
#define dslProgressFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class PACKAGE TProgressF : public TForm
{
__published:    // IDE-managed Components
    TLabel *Label1;
    TLabel *FileNameLabel;
    TPanel *Panel1;
    TProgressBar *ProgressBar1;
private:    // User declarations
public:        // User declarations
            __fastcall TProgressF(TComponent* Owner);
      void     __fastcall SetFileNameLabel(const String& str);
    void     __fastcall StepBy(const int&);
    int     __fastcall GetMax();
};
//---------------------------------------------------------------------------
extern PACKAGE TProgressF *ProgressF;
//---------------------------------------------------------------------------
#endif
