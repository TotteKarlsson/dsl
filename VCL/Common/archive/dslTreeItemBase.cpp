#pragma hdrstop
#include "dslTreeItemBase.h"
#include "dslVCLUtils.h"

#pragma package(smart_init)
using namespace dsl;
//---------------------------------------------------------------------------
dslTreeItemBase::dslTreeItemBase(const string& lbl, const bool& isRoot)
:
mID(0),
mDeleted(false),
mLabel(lbl),
mIsRoot(isRoot)
{

}


unsigned int    dslTreeItemBase::GetID(){return mID;}
dslTreeItemBase::~dslTreeItemBase(){}
string            dslTreeItemBase::GetLabel(){return mLabel;}
void            dslTreeItemBase::SoftDelete(bool what){mDeleted = what;}
bool            dslTreeItemBase::SoftDelete(){return mDeleted;}
int                dslTreeItemBase::GetIconIndex(){return mIconIndex;}
int                dslTreeItemBase::GetIconSelectedIndex(){return mIconSelectedIndex;}
