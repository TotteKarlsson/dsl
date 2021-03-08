#ifndef dslProjectsH
#define dslProjectsH
#include "dslObject.h"
#include "dslSharedPointer.h"
#include <list>
#include "dslSubject.h"
//---------------------------------------------------------------------------

//Container for Projects
namespace dsl
{
class Project;
using std::list;

//Simple container holding projects
//User is responsible to dispose of the projects
class DSL_COMMON Projects : public DSLObject
{
    public:
                                			    Projects();
                                			    ~Projects();
        void                                    clear();
        bool                                    hasProject(const string& pName);

        void                    			    append(Project* p);
        bool                    			    remove(Project* p);
        Project*                                selectFirst();
        Project*                                selectLast();
		Project* 							    getProject(int i);
        void                                    notifyObservers(SubjectEvent se);

        bool                                    selectProject(Project* p);
        Project*					            getRootProject(Project* p);

        Project*                                getCurrent();
        Project*                                getFirst();
        Project*                                getNext();
        Project*                                getPrevious();
        Project*                                getLast();
        size_t                                  count();

    protected:
        list<Project* >         	      		mProjects;
        list<Project* >::iterator     			mCurrentProjectIter;
};

}

#endif
