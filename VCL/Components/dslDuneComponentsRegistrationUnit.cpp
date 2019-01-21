#pragma hdrstop
#include "dslComponentsPackageDefs.h"
#include "dslTFloatLabeledEdit.h"
#include "dslTIntegerEdit.h"
#include "dslTIntegerLabeledEdit.h"
#include "dslTFloatEdit.h"
#include "dslTFloatLabel.h"
#include "dslTIniFileC.h"
#include "dslTPropertyCheckBox.h"
#include "dslTURLLabel.h"
#include "dslTSTDStringEdit.h"
#include "dslTSTDStringLabeledEdit.h"
#include "dslTIntLabel.h"
#include "dslTPluginManager.h"
#include "dslTLogFileReader.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

using namespace dsl;

//namespace Dsltfloatlabelededit
//{
//      void __fastcall PACKAGE Register()
//      {
//      	ShowMessage("test");
//        TComponentClass classes[1] = {__classid(TFloatLabeledEdit)};
//        RegisterComponents(DuneComponents, classes, 0);
//      }
//}


//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
static inline void ValidCtrCheck(TPluginManager *)
{
    new TPluginManager(nullptr);
}

namespace Dsltpluginmanager
{
    void __fastcall PACKAGE Register()
    {
         TComponentClass classes[1] = {__classid(TPluginManager)};
         RegisterComponents(gDuneComponents, classes, 0);
    }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
static inline void ValidCtrCheck(TLogFileReader *)
{
	new TLogFileReader(NULL);
}

namespace Dsltlogfilereader
{
	void __fastcall PACKAGE Register()
	{
		TComponentClass classes[1] = {__classid(TLogFileReader)};
		RegisterComponents(gDuneComponents, classes, 0);
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
static inline void ValidCtrCheck(TIntLabel *)
{
  new TIntLabel(nullptr);
}

namespace Dsltintlabel
{
    void __fastcall PACKAGE Register()
    {
        TComponentClass classes[1] = {__classid(TIntLabel)};
        RegisterComponents(gDuneComponents, classes, 0);
    }
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
static inline void ValidCtrCheck(TFloatLabel *)
{
  new TFloatLabel(nullptr);
}

namespace Dsltfloatlabel
{
    void __fastcall PACKAGE Register()
    {
        TComponentClass classes[1] = {__classid(TFloatLabel)};
        RegisterComponents(gDuneComponents, classes, 0);
    }
}

////---------------------------------------------------------------------------
static inline void ValidCtrCheck(TFloatEdit *)
{
  new TFloatEdit(nullptr);
}

namespace Dsltfloatedit
{
      void __fastcall PACKAGE Register()
      {
        TComponentClass classes[1] = {__classid(TFloatEdit)};
        RegisterComponents(gDuneComponents, classes, 0);
      }
}
//
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
static inline void ValidCtrCheck(TIniFileC *)
{
    new TIniFileC(nullptr);
}

namespace Dsltinifilec
{
    void __fastcall PACKAGE Register()
    {
        TComponentClass classes[1] = {__classid(TIniFileC)};
        RegisterComponents(gDuneComponents, classes, 0);
    }
}


//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
static inline void ValidCtrCheck(TPropertyCheckBox *)
{
    new TPropertyCheckBox(nullptr);
}

namespace Dsltpropertycheckbox
{
    void __fastcall PACKAGE Register()
    {
        TComponentClass classes[1] = {__classid(TPropertyCheckBox)};
        RegisterComponents(gDuneComponents, classes, 0);
    }
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
static inline void ValidCtrCheck(TFloatLabeledEdit *)
{
  new TFloatLabeledEdit(nullptr);
}

namespace Dsltfloatlabelededit
{
      void __fastcall PACKAGE Register()
      {
//      	ShowMessage("test");
        TComponentClass classes[1] = {__classid(TFloatLabeledEdit)};
        RegisterComponents(gDuneComponents, classes, 0);
      }
}

////---------------------------------------------------------------------------
static inline void ValidCtrCheck(TIntegerLabeledEdit *)
{
    new TIntegerLabeledEdit(nullptr);
}

namespace Dsltintegerlabelededit
{
    void __fastcall PACKAGE Register()
    {
        TComponentClass classes[1] = {__classid(TIntegerLabeledEdit)};
        RegisterComponents(gDuneComponents, classes, 0);
    }
}
////---------------------------------------------------------------------------
////---------------------------------------------------------------------------
static inline void ValidCtrCheck(TIntegerEdit *)
{
    new TIntegerEdit(nullptr);
}

namespace Dsltintegeredit
{
    void __fastcall PACKAGE Register()
    {
        TComponentClass classes[1] = {__classid(TIntegerEdit)};
        RegisterComponents(gDuneComponents, classes, 0);
    }
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
static inline void ValidCtrCheck(TURLLabel *)
{
  new TURLLabel(nullptr);
}

namespace Dslturllabel
{
    void __fastcall PACKAGE Register()
    {
        TComponentClass classes[1] = {__classid(TURLLabel)};
        RegisterComponents(gDuneComponents, classes, 0);
    }
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
static inline void ValidCtrCheck(TSTDStringLabeledEdit *)
{
  new TSTDStringLabeledEdit(nullptr);
}

namespace Dsltstdstringlabelededit
{
    void __fastcall PACKAGE Register()
    {
        TComponentClass classes[1] = {__classid(TSTDStringLabeledEdit)};
        RegisterComponents(gDuneComponents, classes, 0);
    }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
static inline void ValidCtrCheck(TSTDStringEdit *)
{
  new TSTDStringEdit(NULL);
}

namespace Dsltstdstringedit
{
    void __fastcall PACKAGE Register()
    {
        TComponentClass classes[1] = {__classid(TSTDStringEdit)};
        RegisterComponents(gDuneComponents, classes, 0);
    }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

