#ifndef dslObserverH
#define dslObserverH
#include "dslObject.h"
#include "dslCommonExporter.h"
#include "dslSubjectEvents.h"
//---------------------------------------------------------------------------

namespace dsl
{

class Subject;

class DSL_COMMON Observer : public DSLObject
{
    //Allow access to the observedSubject
    friend class Subject;

    public:
        virtual                                 ~Observer();
        virtual void                            update(Subject* theChangedSubject, SubjectEvent se = Ping) = 0;
        virtual bool                            hasSubject();
        Subject*                                getSubject();
		void									observe(Subject* s);
  		void                                    stopObserving();
        string                                  mObserverTag;
        void                                    setInActive();
        void                                    setActive();
		bool                                    isActive();
	protected:
                                                Observer(Subject* s = nullptr);
        Subject*                                mSubject;

                                            	//Allow soft removal by a subject by setting this to false;
        bool                                    mIsActive;

};

}
#endif
