#pragma hdrstop
#include "dslPropertiesContainer.h"
//---------------------------------------------------------------------------

namespace dsl
{

PropertiesContainer::PropertiesContainer()
{}

PropertiesContainer::~PropertiesContainer()
{}

void PropertiesContainer::append(shared_ptr<Properties> ps)
{
    mSections.push_back(ps);
}

bool PropertiesContainer::enableEdits()
{
    for (mSectionIterator = mSections.begin(); mSectionIterator != mSections.end(); ++mSectionIterator)
    {
	    if((*mSectionIterator))
        {
        	(*mSectionIterator)->enableEdits();
        }
    }
    return true;
}

bool PropertiesContainer::disableEdits()
{
    for (mSectionIterator = mSections.begin(); mSectionIterator != mSections.end(); ++mSectionIterator)
    {
	    if((*mSectionIterator))
        {
        	(*mSectionIterator)->disableEdits();
        }
    }
    return true;
}

bool PropertiesContainer::discardEdits()
{
    for (mSectionIterator = mSections.begin(); mSectionIterator != mSections.end(); ++mSectionIterator)
    {
	    if((*mSectionIterator))
        {
        	(*mSectionIterator)->discardEdits();
        }
    }
    return true;
}

int PropertiesContainer::applyEdits()
{
    for (mSectionIterator = mSections.begin(); mSectionIterator != mSections.end(); ++mSectionIterator)
    {
	    if((*mSectionIterator))
        {
        	(*mSectionIterator)->applyEdits();
        }
    }

    return -1;
}

shared_ptr<Properties> PropertiesContainer::getSection(const string& s)
{
    for (mSectionIterator = mSections.begin(); mSectionIterator != mSections.end(); ++mSectionIterator)
    {
	    if((*mSectionIterator)->getSectionName() == s)
        {
            return (*mSectionIterator);
        }
    }
    return shared_ptr<Properties>();
}

}