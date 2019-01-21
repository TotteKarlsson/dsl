#pragma hdrstop
#include "dslBaseProperty.h"
//---------------------------------------------------------------------------

namespace dsl
{

BaseProperty::BaseProperty()
:
mKey("<none>"),
mWasRead(false),
mIsModified(false),
mIsInEditMode(false)
{}

BaseProperty::BaseProperty(const string& lbl)
:
mKey(lbl),
mWasRead(false),
mIsModified(false),
mIsInEditMode(false)
{}

BaseProperty::~BaseProperty()
{}

const char* BaseProperty::c_str() const
{
    return "Implement c_str() in derived property!";
}

bool BaseProperty::doReadFromINI()
{
    return mDoReadFromINI;
}

bool BaseProperty::wasRead()
{
    return mWasRead;
}

bool BaseProperty::wasWritten()
{
    return mWasWritten;
}

void BaseProperty::setModified()
{
    mIsModified = true;
}

bool BaseProperty::isModified()
{
    return mIsModified;
}

bool BaseProperty::isInEditMode()
{
    return mIsInEditMode;
}

bool BaseProperty::setEditMode(bool val)
{
	mIsInEditMode = val;
}

void BaseProperty::discardEdit()
{
    mIsModified = false;
}

}
