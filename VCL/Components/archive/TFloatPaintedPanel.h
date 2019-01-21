#ifndef TFloatPaintedPanelH
#define TFloatPaintedPanelH
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include "TPaintedPanel.h"
#include "dslFloatLabel.h"

//---------------------------------------------------------------------------
class PACKAGE TFloatPaintedPanel : public TPaintedPanel
{
private:
    mtkFloatLabel*                  FLabel;
    String                          FValueCaption;
    TAlign                          FValueLabelAlign;
    TAlignment                      FValueLabelAlignment;
    TTextLayout                     FValueLabelLayout;
    int                             FNrOfDecimals;
    int                             FValueLeft;
    int                             FValueTop;
    TNotifyEvent                    FOnValueClick;
    TColor                          mValueColor;

    void                __fastcall     ValueClicked(TObject *Sender);

protected:
    public:
                        __fastcall     TFloatPaintedPanel(TComponent* Owner);
                        __fastcall ~TFloatPaintedPanel();
    void                __fastcall     Enable(bool doWhat);
    void                __fastcall     SetReference(double& val){if(FLabel) FLabel->SetReference(val);}
    void                __fastcall  UpdateFromValue(){FLabel->UpdateFromValue();}
    String              __fastcall  GetValueCaption();
    void                __fastcall  SetValueCaption(String aString);
    int                 __fastcall  GetNrOfDecimals(){return FLabel ? FLabel->NrOfDecimals : 2;}
    void                __fastcall  SetNrOfDecimals(int decimals){if(FLabel){ FLabel->SetNrOfDecimals(decimals);}}

    TFont*              __fastcall  GetValueFont(){return FLabel ? FLabel->Font : nullptr;}
    void                __fastcall  SetValueFont(TFont* aFont){FLabel->Font = aFont ? aFont : nullptr;}
    double              __fastcall     GetValue();
    void                __fastcall     SetValue(double number);
    void                __fastcall     SetValueLabelLeft(int left);
    void                __fastcall     SetValueLabelTop(int    top);
    void                  __fastcall     SetValueReference(double& val){if(FLabel) FLabel->SetReference(val);}
    void                  __fastcall     SetValueLabelAlign(TAlign align){FValueLabelAlign = align; FLabel->Align = align;}
    void                  __fastcall     SetValueLabelAlignment(TAlignment align){FValueLabelAlignment = align; FLabel->Alignment = align;}
    void                  __fastcall     SetValueLabelLayout(TTextLayout layout){FValueLabelLayout = layout; FLabel->Layout = layout;}

__published:
    __property String       ValueCaption        = {read=GetValueCaption,        write=SetValueCaption};
    __property int          ValueNrOfDecimals   = {read=GetNrOfDecimals,        write=SetNrOfDecimals,          default=2};
    __property TAlign       ValueLabelAlign     = {read=FValueLabelAlign,       write=SetValueLabelAlign,       default=alNone};
    __property TAlignment   ValueLabelAlignment = {read=FValueLabelAlignment,   write=SetValueLabelAlignment,   default=taCenter};
    __property TTextLayout  ValueLabelLayout    = {read=FValueLabelLayout,      write=SetValueLabelLayout,      default=tlCenter};
    __property int          ValueTop            = {read=FValueTop,              write=SetValueLabelTop,            default=27};
    __property int          ValueLeft           = {read=FValueLeft,             write=SetValueLabelLeft,           default=7};
    __property TNotifyEvent OnValueClick        = {read=FOnValueClick,          write=FOnValueClick};
    __property TFont*       ValueFont           = {read=GetValueFont,           write=SetValueFont};
};
#endif
