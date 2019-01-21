#pragma hdrstop
#include "dslPluginMetaData.h"
#include <sstream>
#include "dslLogger.h"
//---------------------------------------------------------------------------

using namespace std;
namespace dsl
{

PluginMetaData::PluginMetaData(const string& name, const string& category)
:
mData()
{
    mData["PluginName"]    	= name;
    mData["Category"] 		= category;
    mData["LibraryName"]  	= "The LibraryName";
    mData["Author"] 		= "The Author";
    mData["Description"] 	= "The Description";
    mData["Hint"] 			= "The Hint";
    mData["Version"] 	 	= "0.0";
    mData["Copyright"] 	 	= "The Copyright";
}

//PluginMetaData::~PluginMetaData()
//{
//    Log(lDebug) << "Destroying a pluginMetaData object";
//}

string PluginMetaData::getAll()
{
    stringstream st;
	map<string, string>::iterator it;

    for ( it = mData.begin(); it != mData.end(); it++ )
    {
        st << it->first  << " = " << it->second << std::endl;
    }
    return st.str();
}

void PluginMetaData::setAuthor(const string& v)
{
    mData["Author"] = v;
}

string PluginMetaData::getAuthor()
{
    return mData["Author"];
}

void PluginMetaData::setDescription(const string& v)
{
    mData["Description"] = v;
}

string PluginMetaData::getDescription()
{
    return mData["Description"];
}

void PluginMetaData::setPluginName(const string& v)
{
    mData["PluginName"] = v;
}

string PluginMetaData::getPluginName()
{
    return mData["PluginName"];
}

void PluginMetaData::setLibraryName(const string& v)
{
    mData["LibraryName"] = v;
}

string PluginMetaData::getLibraryName()
{
    return mData["LibraryName"];
}

void PluginMetaData::setHint(const string& val)
{
    mData["Hint"] = val;
}

string PluginMetaData::getHint()
{
    return mData["Hint"];
}

void PluginMetaData::setVersion(const string& val)
{
    mData["Version"] = val;
}

string PluginMetaData::getVersion()
{
    return mData["Version"];
}

void PluginMetaData::setCategory(const string& val)
{
    mData["Category"] = val;
}

string PluginMetaData::getCategory()
{
    return mData["Category"];
}

void PluginMetaData::setCopyright(const string& val)
{
    mData["Copyright"] = val;
}

string PluginMetaData::getCopyright()
{
    return mData["Copyright"];
}

bool PluginMetaData::add(const string& lbl, const string& info)
{
    mData[lbl] = info;
    return true;
}




}
