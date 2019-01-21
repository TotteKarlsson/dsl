
#pragma hdrstop
#include "TPaintedPanel.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------
__fastcall TPaintedPanel::TPaintedPanel(TComponent* Owner)
    : TPanel(Owner)
{
    FPicture = new TPicture;
    FPicture->OnChange = &PictureChanged;
}
//---------------------------------------------------------------------------

__fastcall TPaintedPanel::~TPaintedPanel()
{
    delete FPicture;
}

void __fastcall    TPaintedPanel::ShowEnabled(bool what)
{
       this->Enabled = what;

    if(what)
    {
        //MOdify graphic to look "disabled.."

    }
    else
    {

    }
}

void __fastcall TPaintedPanel::Paint()
{
    if(FPicture->Graphic && !FPicture->Graphic->Empty)
    {
        if(FSizeToPicture)
        {
            this->Width     = FPicture->Width;
            this->Height    = FPicture->Height;
            Canvas->Draw(0, 0, FPicture->Graphic);
        }
        else if (FStretchGraphic)
        {
            //Stretch the graphic to fill the panel
            TRect aRect(0, 0, this->Width, this->Height);
            Canvas->StretchDraw(aRect, FPicture->Graphic);
        }
        else if(FCenterGraphic)
        {
            //Center the graphic on the panel
            int horCenter = this->Left +  this->Width/2;
            int vertCenter = this->Top +  this->Height/2;

            int picLeft = horCenter  - FPicture->Width/2;
            int picTop =  vertCenter - FPicture->Height/2;
            Canvas->Draw(picLeft, picTop, FPicture->Graphic);
        }
        else
        {
            Canvas->Draw(0, 0, FPicture->Graphic);
        }
    }
    else
    {
        TPanel::Paint();
    }
}

void __fastcall TPaintedPanel::PictureChanged(TObject *Sender)
{
    Invalidate();
}

void __fastcall TPaintedPanel::SetPicture(TPicture* Value)
{
    FPicture->Assign(Value);
}

////////////////////////////////////////////////////////////////////////
namespace Tpaintedpanel
{
    void __fastcall PACKAGE Register()
    {
        TComponentClass classes[1] = {__classid(TPaintedPanel)};
        RegisterComponents(dslComponents::gDuneEditPanels, classes, 0);
    }
}
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//
static inline void ValidCtrCheck(TPaintedPanel *)
{
    new TPaintedPanel(nullptr);
}

