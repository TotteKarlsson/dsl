#ifndef dslSubjectH
#define dslSubjectH
#include "dslObject.h"
#include "dslConstants.h"
#include "dslSharedPointer.h"
#include "dslSubjectEvents.h"
#include <list>
#include "dslSharedPointer.h"
//---------------------------------------------------------------------------

namespace dsl
{

using std::list;
class Observer;

typedef  list< dsl_shared_ptr<Observer> >   ObserverList;
typedef dsl_shared_ptr<Observer>            spObserver;

//Might rename this class to Observable
class DSL_COMMON Subject : public DSLObject
{
    public:
                                                Subject(const string& tag = gNoneString);
        virtual                                 ~Subject();
        virtual string                  		getTypeName() const;
        bool                                    hasObserver(Observer* obs);
        bool                                    hasObservers();

        virtual void                            notifyObservers(SubjectEvent se);

        virtual bool                            attachObserver(Observer* obs);
        virtual bool                            detachObserver(Observer* obs);
        virtual void                            detachAllObservers();

        virtual void                            setTag(const string& tag);
        string                                  getTag();
        const list<Observer*>&                  getObservers();
        virtual void                            setSuspendedUpdates();
        virtual void                            enableUpdates();
        virtual string                          asString(const char& delimiter) const;
        virtual void                            select();
        virtual void                            unSelect();
        bool                                    isSelected();

    protected:
        bool                                    mIsSelected;
        string                                  mTag;
        list<Observer*>                         mObservers;
        bool                                    mSuspendObserverUpdates;
};

}
#endif
