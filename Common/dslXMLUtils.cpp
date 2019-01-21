#pragma hdrstop
#include "dslXMLUtils.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------

namespace dsl
{

using namespace tinyxml2;

vector<double> getDoubleAttributes(const XMLElement* elem, const StringList& lbls)
{
    //TODO: do some error checking.
    vector<double> res;
    for(unsigned int i = 0; i < lbls.count(); i++)
    {
        res.push_back(elem->DoubleAttribute(lbls[i].c_str()));
    }

    return res;
}

vector<double> getRecordOfDoubles(const XMLElement* element, const string& name, const StringList& lbls)
{
    vector<double> res;

    const XMLElement* elem = element->FirstChildElement(name.c_str());
    if(elem)
    {
        for(unsigned int i = 0; i < lbls.count(); i++)
        {
            res.push_back(elem->DoubleAttribute(lbls[i].c_str()));
        }
    }
    return res;
}

vector<double> getListOfDoublesAttribute(const XMLElement* element, const string& name)
{
    vector<double> res;

    string dbls = string(element->Attribute(name.c_str()));
    if(dbls.size())
    {
        dbls = trimChars(dbls, "()");
        StringList coords(dbls, ',');
        for(unsigned int i = 0; i < coords.count(); i++)
        {
            res.push_back(toDouble(coords[i]));
        }
    }
    return res;
}

}
