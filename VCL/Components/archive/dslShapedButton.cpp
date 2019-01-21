
#pragma hdrstop
#include "dslShapedButton.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//
static inline void ValidCtrCheck(TShapedButton *)
{
    new TShapedButton(nullptr);
}
//---------------------------------------------------------------------------
__fastcall TShapedButton::TShapedButton(TComponent* Owner)
    : TSpeedButton(Owner)
{
    mShape         = new TShape(nullptr);
    mShape->Shape  = stEllipse;
    mShape->Width  = 200;
    mShape->Height = 200;
}

//---------------------------------------------------------------------------
__fastcall TShapedButton::~TShapedButton()
{
    delete mShape;
}

namespace Mtkshapedbutton
{
    void __fastcall PACKAGE Register()
    {
         TComponentClass classes[1] = {__classid(TShapedButton)};
        RegisterComponents(dslComponents::gDuneComponents, classes, 0);
    }
}
//---------------------------------------------------------------------------
