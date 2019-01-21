#ifndef TCaptionedFloatPaintedPanelH
#define TCaptionedFloatPaintedPanelH
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include "DuneComponents.h"
#include "TPaintedPanel.h"
#include "dslFloatLabel.h"
//---------------------------------------------------------------------------
class PACKAGE TCaptionedFloatPaintedPanel : public TPaintedPanel
{
private:
    TLabel*                         FCaption;
    TColor                          mCaptionColor;
    TColor                          mValueColor;
    mtkFloatLabel*                  FFloatLabel;
    String                          FValueCaption;
    int                             FNrOfDecimals;
    int                             FValueLeft;
    int                             FValueTop;
    TNotifyEvent                    FOnValueClick;
    void            __fastcall         ValueClicked(TObject *Sender);

protected:
    public:
            __fastcall                 TCaptionedFloatPaintedPanel(TComponent* Owner);
            __fastcall                ~TCaptionedFloatPaintedPanel();
    void    __fastcall                 Enable(bool doWhat);
    void     __fastcall             SetReference(double& val)
        {
            if(FFloatLabel)
                FFloatLabel->SetReference(val);
        }
    void     __fastcall             UpdateFromValue(){FFloatLabel->UpdateFromValue();}
    String   __fastcall             GetLabelCaption();
    void     __fastcall             SetLabelCaption(String aString);
    String   __fastcall             GetValueCaption();
    void     __fastcall             SetValueCaption(String aString);
    int      __fastcall             GetNrOfDecimals(){return FFloatLabel ? FFloatLabel->NrOfDecimals : 2;}
    void     __fastcall             SetNrOfDecimals(int decimals)
    {
        if(FFloatLabel)
        {
            FFloatLabel->SetNrOfDecimals(decimals);
        }
    }

    TFont*  __fastcall              GetCaptionFont(){return FCaption ? FCaption->Font : nullptr;}
    void    __fastcall              SetCaptionFont(TFont* aFont)
                                                            {
                                                                FCaption->Font = aFont ? aFont : nullptr;
                                                            }

    TFont*  __fastcall              GetValueFont(){return FFloatLabel ? FFloatLabel->Font : nullptr;}
    void    __fastcall              SetValueFont(TFont* aFont)
                                                {
                                                    FFloatLabel->Font = aFont ? aFont : nullptr;
                                                }

    double              __fastcall     GetValue();
    void                __fastcall     SetValue(double number);
    void                __fastcall     SetValueLabelLeft(int left);
    void                __fastcall     SetValueLabelTop(int    top);
    void                  __fastcall     SetValueReference(double& val){if(FFloatLabel) FFloatLabel->SetReference(val);}

__published:
    __property String               Caption             = {read=GetLabelCaption,    write=SetLabelCaption};
    __property TFont*               CaptionFont         = {read=GetCaptionFont,     write=SetCaptionFont};
    __property String               ValueCaption        = {read=GetValueCaption,    write=SetValueCaption};
    __property int                  ValueNrOfDecimals   = {read=GetNrOfDecimals,    write=SetNrOfDecimals,      default=2};
    __property int                  ValueTop            = {read=FValueTop,          write=SetValueLabelTop,    default=27};
    __property int                  ValueLeft           = {read=FValueLeft,         write=SetValueLabelLeft,   default=7};
    __property TNotifyEvent         OnValueClick        = {read=FOnValueClick,      write=FOnValueClick};
    __property TFont*               ValueFont           = {read=GetValueFont,       write=SetValueFont};

};
#endif
