#ifndef TCaptionedIntPaintedPanelH
#define TCaptionedIntPaintedPanelH
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include "DuneComponents.h"
#include "TPaintedPanel.h"
#include "dslIntLabel.h"
//---------------------------------------------------------------------------
class PACKAGE TCaptionedIntPaintedPanel : public TPaintedPanel
{
private:
    TLabel*                         FCaption;
    TColor                          mCaptionColor;
    TColor                          mValueColor;
    mtkIntLabel*                    FIntLabel;
    String                          FValueCaption;
    int                             FCaptionTop;
    int                             FValueLeft;
    int                             FValueTop;
    TNotifyEvent                    FOnValueClick;
    bool                            FIsEnabled;
    bool                            FCaptionVisible;
    void            __fastcall         ValueClicked(TObject *Sender);

protected:
    public:
                        __fastcall     TCaptionedIntPaintedPanel(TComponent* Owner);
                        __fastcall  ~TCaptionedIntPaintedPanel();
    void                __fastcall  Enable(bool doWhat);
    void                __fastcall  SetReference(int& val);
    String              __fastcall  GetLabelCaption();
    void                __fastcall  SetLabelCaption(String aString);
    bool                __fastcall  GetCaptionVisible();
    void                __fastcall  SetCaptionVisible(bool visible);
    String              __fastcall  GetValueCaption();
    void                __fastcall  SetValueCaption(String aString);
    TFont*              __fastcall  GetCaptionFont();
    void                __fastcall  SetCaptionFont(TFont* aFont);
    TFont*              __fastcall  GetValueFont();
    void                __fastcall  SetValueFont(TFont* aFont);
    void                __fastcall  UpdateFromValue(){FIntLabel->UpdateFromValue();}
    int                 __fastcall  GetValue();
    void                __fastcall  SetValue(int number);
    void                __fastcall  SetValueLabelLeft(int left);
    void                __fastcall  SetValueLabelTop(int top);
    void                  __fastcall  SetValueReference(int& val){if(FIntLabel) FIntLabel->SetReference(val);}

__published:
    __property String               Caption             = {read=GetLabelCaption,    write=SetLabelCaption};
    __property bool                 CaptionVisible      = {read=GetCaptionVisible,  write=SetCaptionVisible};
    __property TFont*               CaptionFont         = {read=GetCaptionFont,     write=SetCaptionFont};
    __property String               ValueCaption        = {read=GetValueCaption,    write=SetValueCaption};
    __property int                  ValueTop            = {read=FValueTop,          write=SetValueLabelTop,    default=27};
    __property int                  ValueLeft           = {read=FValueLeft,         write=SetValueLabelLeft,   default=7};
    __property TNotifyEvent         OnValueClick        = {read=FOnValueClick,      write=FOnValueClick};
    __property TFont*               ValueFont           = {read=GetValueFont,       write=SetValueFont};
};
#endif
