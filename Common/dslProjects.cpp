#pragma hdrstop
#include "dslProjects.h"
#include "dslProject.h"
#include "dslStringList.h"
#include <sstream>
#include "dslException.h"
//---------------------------------------------------------------------------

namespace dsl
{

using namespace std;

Projects::Projects()
{
	mCurrentProjectIter = mProjects.begin();
}

Projects::~Projects()
{}

void Projects::clear()
{
	mProjects.clear();
}

Project* Projects::getRootProject(Project* p)
{
    //Find project root for project
    return p->getProjectRoot();
}

void Projects::notifyObservers(SubjectEvent se)
{
    for(mCurrentProjectIter = mProjects.begin(); mCurrentProjectIter != mProjects.end(); ++mCurrentProjectIter)
    {
        (*mCurrentProjectIter)->notifyObservers(se);
    }
}

bool Projects::hasProject(const string& pName)
{
    Project* p = getFirst();
    while(p)
    {
        if(p->getProjectName() == pName)
        {
            return true;
        }
        p = getNext();
    }
    return false;
}

//Inefficient
Project* Projects::getProject(int i)
{
    int ix = 0;
    Project* p = getFirst();
    while(ix < count())
    {
        if(ix == i)
        {
            return p;
        }
        p = getNext();
        ix++;
    }
    return nullptr;
}

void Projects::append(Project* p)
{
    mProjects.push_back(p);
    selectLast();
}

bool Projects::remove(Project* p)
{
    mProjects.remove(p);
    return true;
}

bool Projects::selectProject(Project* p)
{
	mCurrentProjectIter = std::find(mProjects.begin(), mProjects.end(), p);
    return (mCurrentProjectIter != mProjects.end()) ? true : false;
}

Project* Projects::getCurrent()
{
    return *mCurrentProjectIter;
}

Project* Projects::selectFirst()
{
    return getFirst();
}

Project* Projects::selectLast()
{
    return getLast();
}

Project* Projects::getFirst()
{
    if(mProjects.size() == 0)
    {
        return nullptr;
    }

	mCurrentProjectIter = mProjects.begin();
    return *(mCurrentProjectIter);
}

Project* Projects::getNext()
{
    if(mCurrentProjectIter != mProjects.end())
    {
        mCurrentProjectIter++;
        if(mCurrentProjectIter != mProjects.end())
        {
            return (*mCurrentProjectIter);
        }
    }
    return nullptr;
}

Project* Projects::getPrevious()
{
    if(mCurrentProjectIter != mProjects.begin())
    {
        mCurrentProjectIter--;
        return (*mCurrentProjectIter);
    }
    return nullptr;
}

Project* Projects::getLast()
{
    if(count() > 0)
    {
		mCurrentProjectIter = mProjects.end();
        --mCurrentProjectIter;
        return (*mCurrentProjectIter);
    }
    return nullptr;
}

int Projects::count()
{
    return mProjects.size();
}

}//Namnespace
