#pragma hdrstop
#include "dslPlugin.h"
#include "dslProperty.h"
#include "dslBaseProperty.h"
#include "dslLogger.h"
#include "dslException.h"
#include "dslStringList.h"
#include <sstream>
#include <iomanip>
#include "dslUtils.h"

//---------------------------------------------------------------------------

namespace dsl
{

using namespace std;

Plugin::Plugin( const string& name, const string& category, const PluginManager* pm)
:
mMetaData(name, category),
mProperties(),
mPM(pm),
mTerminate(false),
mIsWorking(false),
mSubject(nullptr)
{}

Plugin::~Plugin()
{}

bool Plugin::addProperty(dsl::BaseProperty* p)
{
    mProperties.add(p);
    return true;
}

const PluginManager* Plugin::getPluginManager() const
{
    return mPM;
}

PluginMetaData Plugin::getPluginMetaData()
{
    return mMetaData;
}

bool Plugin::assignMetaData(const PluginMetaData& mData)
{
    mMetaData = mData;
    return true;
}

void Plugin::terminate(bool block)
{
    if(!mIsWorking)
    {
        Log(lWarning) << "Tried to terminate a non working plugin..";
        return;
    }

    mTerminate = true;
    if(block)
    {
        //Wait until the thread is terminated
        while(mIsWorking)
        {
            sleep(100);
        }
    }
}

bool Plugin::isBeingTerminated() const
{
    return mTerminate;
}

bool Plugin::wasTerminated() const
{
    if(mTerminate)
    {
        return (mIsWorking == false) ? true : false;
    }
    return false;
}

bool Plugin::resetPlugin()
{
    //Do whats needed in descendants
    return true;
}

bool Plugin::isWorking() const
{
    return mIsWorking;
}

void Plugin::setLibraryName(const string& libName)
{
    mMetaData.setLibraryName(libName);
}

void Plugin::setPropertyByString(const string& nameOf, const string& value)
{
    BaseProperty* bp = mProperties.getProperty(nameOf);


    if(bp && !bp->assignValueFromString(value))
    {
        stringstream msg;
        msg<<"Failed setting property value; No property with name: "<<nameOf;
        throw(DSLException(msg.str()));
    }
}

void Plugin::setPropertyValueFromVoid(const string& nameOf, const void* value)
{
    BaseProperty* property = mProperties.getProperty(nameOf);
    if(property)
    {
        string type = property->getTypeName();
        if(type == "bool")
        {
            const bool* theData = (bool*) value;
            Property<bool>* prop = dynamic_cast< Property<bool>* >(property);
            prop->setValue(*theData);
            return;
        }

        if(type == "int")
        {
            const int* theData = (int*) value;
            Property<int>* prop = dynamic_cast< Property<int>* >(property);
            prop->setValue(*theData);
            return;
        }

        if(type == "double")
        {
            const double* theData = (double*) value;
            Property<double>* prop = dynamic_cast< Property<double>* >(property);
            prop->setValue(*theData);
            return;
        }

        if(type == "std::string" || type == "string")
        {
            const string* theData = (string*) value;
            Property<string>* prop = dynamic_cast< Property<string>* >(property);
            prop->setValue(*theData);
            return;
        }

        if(type == "properties")
        {
            const Properties* theData = (Properties*) value;
            Property<Properties>* props = dynamic_cast< Property<Properties>* >(property);
            props->setValue(*theData);
            return;
        }

//        if(type == "point")
//        {
//            const Point* theData = (Point*) value;
//            Property<Point>* props = dynamic_cast< Property<Point>* >(property);
//            props->setValue(*theData);
//            return;
//        }

        stringstream msg;
        msg<<"Conversion of property of type: \""<<type<<" is not implemented";
        throw(DSLException(msg.str()));
    }

    stringstream msg;
    msg<<"Failed setting property value; No property with name: "<<nameOf;
    throw(DSLException(msg.str()));
}

string Plugin::getName()
{
    return mMetaData.getPluginName();
}

string Plugin::getLibraryName()
{
    return mMetaData.getLibraryName();
}

string Plugin::getAuthor()
{
    return mMetaData.getAuthor();
}

string Plugin::getCategory()
{
    return mMetaData.getCategory();
}

string Plugin::getDescription()
{
    return mMetaData.getDescription();
}

string Plugin::getHint()
{
    return mMetaData.getHint();
}

string Plugin::getVersion()
{
    return mMetaData.getVersion();
}

string Plugin::getCopyright()
{
    return mMetaData.getCopyright();
}

//Overload in descendants and add info there.
string Plugin::getStatus()
{
    stringstream msg;
    msg<<"The following is a status message for Plugin: "<<mMetaData.getPluginName()<<"\n";
    return msg.str();
}

//Obs. subclasses may over ride this function and add more info
string Plugin::getInfo()
{
    stringstream msg;
    msg<<setfill('.');
    msg<<setw(30)<<left<<"Name" << getName() <<"\n";
    msg<<setw(30)<<left<<"Author"<<getAuthor()<<"\n";
    msg<<setw(30)<<left<<"Category"<<getCategory()<<"\n";
    msg<<setw(30)<<left<<"Description"<<getDescription()<<"\n";
    msg<<setw(30)<<left<<"Hint"<<getHint()<<"\n";
    msg<<setw(30)<<left<<"Version"<<getVersion()<<"\n";
    msg<<setw(30)<<left<<"Copyright"<<getCopyright()<<"\n";
    return msg.str();
}

string Plugin::getExtendedInfo()
{
    stringstream msg;
    msg<<getInfo();
    msg<<"\nPlugin Properties Info\n";
    Properties* props = getProperties();
    msg<<(*props);
    return msg.str();
}

StringList Plugin::getPropertyNames()
{
    return mProperties.getNames();
}

Properties* Plugin::getProperties()
{
    return &mProperties;
}

BaseProperty* Plugin::getProperty(const string& propName)
{
    return mProperties.getProperty(propName);
}

string Plugin::getPropertyValueAsString(const string& propName)
{
    BaseProperty* prop =  mProperties.getProperty(propName);
    if(prop)
    {
        return prop->getValueAsString();
    }
    else
    {
        stringstream str;
        str<<"No property with name: "<<propName;
        throw(DSLException(str.str()));
    }
}

int Plugin::getPropertyValueAsInteger(const string& propName)
{
    BaseProperty* bp =  mProperties.getProperty(propName);
    if(bp)
    {
	    Property<int>* p = dynamic_cast< Property<int>* >(bp);
        if(p)
        {
            return p->getValue();
        }
        else
        {
            stringstream str;
	        str<<"this property does not hold an integer: "<<propName;
    	    throw(DSLException(str.str()));
        }
    }
    else
    {
        stringstream str;
        str<<"No property with name: "<<propName;
        throw(DSLException(str.str()));
    }
}

void* Plugin::getPropertyValueHandle(const string& propName)
{
    BaseProperty* prop =  mProperties.getProperty(propName);
    if(prop)
    {
        return prop->getValueHandle();
    }
    else
    {
        stringstream str;
        str<<"No property with name: "<<propName;
        throw(DSLException(str.str()));
    }
}

}

