#ifndef TIntPaintedPanelH
#define TIntPaintedPanelH
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include "TPaintedPanel.h"
#include "dslIntLabel.h"
#include "DuneComponents.h"
//---------------------------------------------------------------------------
class PACKAGE TIntPaintedPanel : public TPaintedPanel
{
private:
    mtkIntLabel                   *FLabel;
    String                      FValueCaption;
    TAlign                      FValueLabelAlign;
    TAlignment                  FValueLabelAlignment;
    TTextLayout                 FValueLabelLayout;
    int                         FValueLeft;
    int                         FValueTop;
    TNotifyEvent                FOnValueClick;

    //Events..
    void            __fastcall     ValueClicked(TObject *Sender);

protected:
    public:
                        __fastcall TIntPaintedPanel(TComponent* Owner);
                        __fastcall ~TIntPaintedPanel();
    void                __fastcall Enable(bool doWhat);
    void                __fastcall SetReference(int& val);
    String              __fastcall GetValueCaption();
    void                __fastcall SetValueCaption(String aString);
    TFont*              __fastcall GetValueFont();
    void                __fastcall SetValueFont(TFont* aFont);
    void                __fastcall UpdateFromValue(){FLabel->UpdateFromValue();}
    int                 __fastcall GetValue();
    void                __fastcall SetValue(int number);
    void                __fastcall SetValueLabelLeft(int left);
    void                __fastcall SetValueLabelTop(int top);
    void                  __fastcall SetValueReference(int& val)                {if(FLabel) FLabel->SetReference(val);}
    void                  __fastcall SetValueLabelAlign(TAlign align)            {FValueLabelAlign = align;         FLabel->Align = align;}
    void                  __fastcall SetValueLabelAlignment(TAlignment align)    {FValueLabelAlignment = align;     FLabel->Alignment = align;}
    void                  __fastcall SetValueLabelLayout(TTextLayout layout)    {FValueLabelLayout = layout;     FLabel->Layout = layout;}

__published:
    __property String       ValueCaption        = {read=GetValueCaption,        write=SetValueCaption};
    __property TAlign       ValueLabelAlign     = {read=FValueLabelAlign,       write=SetValueLabelAlign,               default=alClient};
    __property TAlignment   ValueLabelAlignment = {read=FValueLabelAlignment,   write=SetValueLabelAlignment,            default=taCenter};
    __property TTextLayout  ValueLabelLayout    = {read=FValueLabelLayout,      write=SetValueLabelLayout,                default=tlCenter};
    __property int          ValueTop            = {read=FValueTop,              write=SetValueLabelTop,                 default=0};
    __property int          ValueLeft           = {read=FValueLeft,             write=SetValueLabelLeft,                default=0};
    __property TFont*       ValueFont           = {read=GetValueFont,           write=SetValueFont};
    __property TNotifyEvent OnValueClick        = {read=FOnValueClick,          write=FOnValueClick};
};
#endif
