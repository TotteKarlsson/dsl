#pragma hdrstop
#include "dslSubject.h"
#include "dslObserver.h"
#include <sstream>
#include <algorithm>
//---------------------------------------------------------------------------

namespace dsl
{


using namespace std;

Subject::Subject(const string& tag)
:
mTag(tag),
mSuspendObserverUpdates(false),
mIsSelected(false)
{}

Subject::~Subject()
{
//    //Detach all observers
//    list<Observer*>::iterator iter = mObservers.begin();
//    for( iter = mObservers.begin(); iter != mObservers.end(); ++iter)
//    {
//        detachObserver((*iter));
//    }
}

string Subject::getTypeName() const
{
    return "subject";
}

void Subject::setTag(const string& tag)
{
    mTag = tag;
}

string Subject::getTag()
{
    return mTag;
}

const list<Observer*>& Subject::getObservers()
{
    return mObservers;
}

void Subject::select()
{
    mIsSelected = true;
    notifyObservers(SubjectEvent::UpdateSelectedProperties);
}

void Subject::unSelect()
{
    mIsSelected = false;
    notifyObservers(SubjectEvent::UpdateSelectedProperties);
}

bool Subject::isSelected()
{
    return mIsSelected;
}

string Subject::asString(const char& delimiter) const
{
    stringstream ss;
    ss<<"Subject ("<<mTag<<") has "<<mObservers.size()<<" observers"<<endl;
    return ss.str();
}

void Subject::setSuspendedUpdates()
{
    mSuspendObserverUpdates = true;
}

void Subject::enableUpdates()
{
    mSuspendObserverUpdates = false;
}

bool Subject::hasObservers()
{
    return mObservers.size() > 0 ? true : false;
}

bool Subject::hasObserver(Observer* obs)
{
    return std::find(mObservers.begin(), mObservers.end(), obs) != mObservers.end() ? true : false;
}

bool Subject::attachObserver(Observer* o)
{
    //Check that the observer is not already in the list...
    if(!hasObserver(o))
    {
        mObservers.push_back(o);
        return true;
    }
    return false;
}

bool Subject::detachObserver(Observer* o)
{
    if(hasObserver(o))
    {
        mObservers.remove(o);
        return true;
    }
    return false;
}

void Subject::detachAllObservers()
{
    mObservers.clear();
}

void Subject::notifyObservers(SubjectEvent event)
{
    if(mSuspendObserverUpdates)
    {
        return;
    }

    list<Observer*>::iterator iter = mObservers.begin();
    while(iter != mObservers.end())
    {
        Observer* obs = (*iter);
        if(obs != nullptr)
        {
            if(obs->isActive())
            {
            	obs->update(this, event);
            }
        }
        ++iter;
    }

    //Remove inactive observers..
	iter = mObservers.begin();
    while(iter != mObservers.end())
    {
        Observer* obs = (*iter);
        if(obs != nullptr)
        {
            if(!obs->isActive())
            {
                iter = mObservers.erase(iter);
            }
        }
        ++iter;
    }

}

}
