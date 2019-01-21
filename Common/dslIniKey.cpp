#pragma hdrstop
#include "dslIniKey.h"
//---------------------------------------------------------------------------

namespace dsl
{

IniKey::IniKey(const string& key)
{
    setupKey(key);
}

IniKey::~IniKey()
{}

void IniKey::reKey(const string& key)
{
    setupKey(key);
}

ostream& operator<<(ostream& stream, const IniKey& aKey)
{
    stream << aKey.asString();
    return stream;
}

string IniKey::asString(const char& delimiter) const
{
    string tmp = mKey;
    tmp += " = ";
    tmp += mValue;
    return tmp;
}

int IniKey::asBool() const
{
    return toBool(mValue);
}

int IniKey::asInt() const
{
    return toInt(mValue);
}

double IniKey::asFloat() const
{
    return toDouble(mValue);
}

void IniKey::setupKey(const string& key)
{
    vector<string> recs = splitString(key, "=");
    if(recs.size() == 2)
    {

        mKey = recs[0];
        mValue = recs[1];
        mComment     = gEmptyString;
    }
    else    //We could throw
    {
        mKey         = gEmptyString;
        mValue       = gEmptyString;
        mComment     = gEmptyString;
    }
}

}
