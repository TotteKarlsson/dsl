#ifndef TPaintedPanelH
#define TPaintedPanelH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include "dslPackageDefs.h"
//---------------------------------------------------------------------------

class PACKAGE TPaintedPanel : public TPanel
{
    private:
        bool                            FSizeToPicture;
        bool                            FStretchGraphic;
        bool                            FCenterGraphic;
        TPicture*                       FPicture;
        void                __fastcall     PictureChanged(TObject *Sender);
        void                __fastcall     SetPicture(TPicture* Value);

    protected:

    public:
        __property Canvas;
                            __fastcall     TPaintedPanel(TComponent* Owner);
                               __fastcall     ~TPaintedPanel();
           void                   __fastcall     Paint();
        virtual void        __fastcall    ShowEnabled(bool what);

    __published:
        __property TPicture*            Picture         = {read=FPicture,             write=SetPicture};
        __property bool                 SizeToPicture   = {read=FSizeToPicture,     write=FSizeToPicture,       default=false};
        __property bool                 StretchGraphic  = {read=FStretchGraphic,    write=FStretchGraphic,      default=false};
        __property bool                 CenterGraphic   = {read=FCenterGraphic,     write=FCenterGraphic,       default=false};
};
#endif
