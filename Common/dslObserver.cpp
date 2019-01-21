#pragma hdrstop
#include "dslObserver.h"
#include "dslSubject.h"
//---------------------------------------------------------------------------
namespace dsl
{

Observer::Observer(Subject* s)
:
mSubject(s),
mIsActive(true)
{}

bool Observer::hasSubject()
{
    return mSubject == nullptr ? false : true;
}

Observer::~Observer()
{
    //Subject better be arount here..!
	if(mSubject && mIsActive)
	{
		mSubject->detachObserver(this);
	}
}

void Observer::setInActive()
{
    mIsActive = false;
}

void Observer::setActive()
{
    mIsActive = true;
}

bool Observer::isActive()
{
    return mIsActive;
}

void Observer::observe(Subject* s)
{
	if(s)
	{
		mSubject = s;
		mSubject->attachObserver(this);
	}
}

void Observer::stopObserving()
{
	if(mSubject)
	{
		mSubject->detachObserver(this);
        mSubject = nullptr;
	}
}

Subject* Observer::getSubject()
{
	return mSubject;
}

}
