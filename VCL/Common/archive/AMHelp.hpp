// CodeGear C++Builder
// Copyright (c) 1995, 2007 by CodeGear
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Amhelp.pas' rev: 11.00

#ifndef AmhelpHPP
#define AmhelpHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member functions
#pragma pack(push,8)
#include <System.hpp>	// Pascal unit
#include <Sysinit.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <Actnlist.hpp>	// Pascal unit
#include <Actnman.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Amhelp
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TAMHelp;
class PASCALIMPLEMENTATION TAMHelp : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
private:
	Actnlist::TCustomAction* FAction;
	Actnman::TCustomActionManager* FActionManager;
	AnsiString FCaption;
	Actnman::TActionProc FCompareProc;
	Actnman::TActionClientItem* FFoundClient;
	void __fastcall CompareCaption(Actnman::TActionClient* AClient);
	void __fastcall CompareAction(Actnman::TActionClient* AClient);
	Actnman::TActionClientItem* __fastcall FindItem(void);
	
protected:
	void __fastcall FindClient(Actnman::TActionClient* AClient);
	virtual void __fastcall Notification(Classes::TComponent* AComponent, Classes::TOperation Operation);
	
public:
	Actnman::TActionClientItem* __fastcall AddAction(Actnlist::TCustomAction* AnAction, Actnman::TActionClient* AClient, bool After = true);
	Actnman::TActionClientItem* __fastcall AddCategory(AnsiString ACategory, Actnman::TActionClient* AClient, bool After = true);
	Actnman::TActionClientItem* __fastcall AddSeparator(Actnman::TActionClientItem* AnItem, bool After = true);
	void __fastcall DeleteActionItems(Actnlist::TCustomAction* * Actions, const int Actions_Size);
	void __fastcall DeleteItem(AnsiString Caption);
	Actnman::TActionClientItem* __fastcall FindItemByCaption(AnsiString ACaption);
	Actnman::TActionClientItem* __fastcall FindItemByAction(Actnlist::TCustomAction* Action);
	
__published:
	__property Actnman::TCustomActionManager* ActionManager = {read=FActionManager, write=FActionManager};
public:
	#pragma option push -w-inl
	/* TComponent.Create */ inline __fastcall virtual TAMHelp(Classes::TComponent* AOwner) : Classes::TComponent(AOwner) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TComponent.Destroy */ inline __fastcall virtual ~TAMHelp(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE void __fastcall Register(void);

}	/* namespace Amhelp */
using namespace Amhelp;
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Amhelp
