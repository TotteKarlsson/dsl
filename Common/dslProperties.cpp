#pragma hdrstop
#include <sstream>
#include <iomanip>
#include "dslProperties.h"
#include "dslLogger.h"
#include "dslStringList.h"
//---------------------------------------------------------------------------

namespace dsl
{
using namespace std;

string toString(const Properties& props)
{
    return gEmptyString;
}

string getFormattedParStr(const string& str, const Properties& props)
{
    return gEmptyString;
}

Properties::Properties(const string& regSubSection)
:
mSectionName(regSubSection)
{}

Properties::~Properties()
{
    mProperties.clear();
}

string Properties::asString(const char&) const
{
    return "Not implemented yet";
}

void Properties::add(BaseProperty* o)
{
    mProperties.push_back(o);
}

string Properties::getSectionName() const
{
    return mSectionName;
}

void Properties::enableEdits()
{
    for(unsigned int i = 0; i < count(); i++)
    {
    	mProperties[i]->setEditMode(true);
    }
}

void Properties::applyEdits()
{
    for(unsigned int i = 0; i < count(); i++)
    {
        if(mProperties[i]->isModified())
        {
            mProperties[i]->applyEdit();
        }
    }
}

void Properties::disableEdits()
{
    for(unsigned int i = 0; i < count(); i++)
    {
    	mProperties[i]->setEditMode(false);
    }
}

bool Properties::isModified() const
{
    for(unsigned int i = 0; i < count(); i++)
    {
        if(mProperties[i]->isModified())
        {
            return true;
        }
    }
    return false;
}

void Properties::discardEdits()
{
    for(unsigned int i = 0; i < count(); i++)
    {
        mProperties[i]->discardEdit();
    }
}

BaseProperty* Properties::operator [](const string& label)
{
    //Search trough parameters for label
    for(unsigned int i = 0; i < count(); i++)
    {
        if(mProperties[i]->getLabel() == label)
        {
            return mProperties[i];
        }
    }
    return nullptr;
}

BaseProperty* Properties::getProperty(const string& label)
{
    //find parameter usign its label
    for(unsigned int i = 0; i < count(); i++)
    {
        if(mProperties[i]->getLabel() == label)
        {
            return mProperties[i];
        }
    }
    Log(lError) << "Failed getting property with name: " << label;
    return nullptr;
}

string Properties::getListing() const
{
    stringstream paras_list;
    for(unsigned int i = 0; i < count(); i++)
    {
        paras_list << setw(30)<<mProperties[i]->getLabel()<<"="<<mProperties[i]->getValueAsString()<<endl;
    }
    return paras_list.str();
}

StringList Properties::getNames() const
{
    StringList list;
    for(unsigned int i = 0; i < count(); i++)
    {
        list.append(mProperties[i]->getLabel());
    }
    return list;
}

bool Properties::read()
{
    return false;
}

bool Properties::write()
{
    return false;
}

unsigned int Properties::count() const
{
	return (unsigned int) mProperties.size();
}

//BaseProperty* Properties::operator [](int index)
//{
//	return mProperties[index];
//}

void Properties::setSectionName(const string& sec)
{
    mSectionName = sec;
}

BaseProperty* Properties::getProperty(int index)
{
	return mProperties[index];
}

void Properties::setupProperties()
{}

template <>
string Properties::getPropertyValue<string>(const string& propName)
{
    BaseProperty* bp = this->getProperty(propName);
    if(!bp)
    {
        stringstream str;
        str << "The property: "<<propName<<" could not be found!";
        throw(DSLException(str.str()));
    }

    if(bp->getPropertyType() != otStdString)
    {
        stringstream str;
        str<<"Property \""<<propName<<"\" is of type: "<<dsl::toString(bp->getPropertyType())<<". Tried to use property type: "<<dsl::toString(otInt);
        throw(DSLException(str.str()));
    }

    string* valueHandle = (string*) bp->getValueHandle();
    return *valueHandle;
}

template <>
bool Properties::setPropertyValue<string>(const string& propName, const string& newValue)
{
    BaseProperty* bp = this->getProperty(propName);
    if(!bp)
    {
        stringstream str;
        str << "The property: "<<propName<<" could not be found!";
        throw(DSLException(str.str()));
    }

    if(bp->getPropertyType() != otStdString)
    {
        stringstream str;
        str<<"Property \""<<propName<<"\" is of type: "<<dsl::toString(bp->getPropertyType())<<". Tried to use property type: "<<dsl::toString(otInt);
        throw(DSLException(str.str()));
    }

    string* valueHandle = (string*) bp->getValueHandle();
    *valueHandle = newValue;
    return true;
}

template <>
int Properties::getPropertyValue<int>(const string& propName)
{
    BaseProperty* bp = this->getProperty(propName);
    if(!bp)
    {
        stringstream str;
        str << "The property: "<<propName<<" could not be found!";
        throw(DSLException(str.str()));
    }

    if(bp->getPropertyType() != otInt)
    {
        stringstream str;
        str<<"Property \""<<propName<<"\" is of type: "<<dsl::toString(bp->getPropertyType())<<". Tried to use property of type: "<<dsl::toString(otInt);
        throw(DSLException(str.str()));
    }

    int* valueHandle = (int*) bp->getValueHandle();
    return *valueHandle;
}

template <>
bool Properties::getPropertyValue<bool>(const string& propName)
{
    BaseProperty* bp = this->getProperty(propName);
    if(!bp)
    {
        stringstream str;
        str << "The property: "<<propName<<" could not be found!";
        throw(DSLException(str.str()));
    }

    if(bp->getPropertyType() != otBool)
    {
        stringstream str;
        str<<"Property \""<<propName<<"\" is of type: "<<dsl::toString(bp->getPropertyType())<<". Tried to use property of type: "<<dsl::toString(otInt);
        throw(DSLException(str.str()));
    }

    bool* valueHandle = (bool*) bp->getValueHandle();
    return *valueHandle;
}

template <>
bool Properties::setPropertyValue<bool>(const string& propName, const bool& newValue)
{
    BaseProperty* bp = this->getProperty(propName);
    if(!bp)
    {
        stringstream str;
        str << "The property: "<<propName<<" could not be found!";
        throw(DSLException(str.str()));
    }

    if(bp->getPropertyType() != otBool)
    {
        stringstream str;
        str<<"Property \""<<propName<<"\" is of type: "<<dsl::toString(bp->getPropertyType())<<". Tried to use property type: "<<dsl::toString(otInt);
        throw(DSLException(str.str()));
    }

    bool* valueHandle = (bool*) bp->getValueHandle();
    *valueHandle = newValue;
    return true;
}



ostream&  operator<<(ostream& stream, const Properties& p)
{
	return stream;
}
}

