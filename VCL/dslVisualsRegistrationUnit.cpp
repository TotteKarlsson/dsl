#pragma hdrstop
#include "dslComponentsPackageDefs.h"
#include "dslTAboutFrame.h"
#include "dslConstants.h"
#include "dslTLogMemoFrame.h"
#include "dslTServerSocketFrame.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------
static inline void ValidCtrCheck(TAboutFrame *)
{
    new TAboutFrame(nullptr);
}

namespace Dsltaboutframe
{
    void __fastcall PACKAGE Register()
    {
         TComponentClass classes[1] = {__classid(TAboutFrame)};
         RegisterComponents(gDuneFrames, classes, 0);
    }
}

//---------------------------------------------------------------------------
static inline void ValidCtrCheck(TLogMemoFrame *)
{
    new TLogMemoFrame(nullptr);
}

namespace Dsltlogmemoframe
{
    void __fastcall PACKAGE Register()
    {
         TComponentClass classes[1] = {__classid(TLogMemoFrame)};
         RegisterComponents(gDuneFrames, classes, 0);
    }
}

//---------------------------------------------------------------------------
static inline void ValidCtrCheck(TServerSocketFrame *)
{
    new TServerSocketFrame(nullptr);
}

namespace Dsltserversocketframe
{
    void __fastcall PACKAGE Register()
    {
        TComponentClass classes[1] = {__classid(TServerSocketFrame)};
        RegisterComponents("Dune Components", classes, 0);
    }
}


