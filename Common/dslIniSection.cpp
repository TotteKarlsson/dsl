#pragma hdrstop
#include "dslUtils.h"
#include "dslStringUtils.h"
#include "dslFileUtils.h"
#include "dslLogger.h"
#include "dslIniSection.h"
//---------------------------------------------------------------------------
namespace dsl
{

IniSection::IniSection()
:
mIsDirty(true),
mName(gEmptyString),
mComment(gEmptyString)
{
}

IniSection::IniSection(const string& nameValueString, const char& sep)
:
mIsDirty(true),
mName(gEmptyString),
mComment(gEmptyString)
{
    vector<string> keys = splitString(nameValueString, sep);
    //Insert each key in the section
    for(unsigned int i = 0; i < keys.size(); i++)
    {
        IniKey *aKey = new IniKey(keys[i]);
        mKeys.push_back(aKey);
    }
}

IniSection::~IniSection()
{
    //detete all keys
    for(uint i = 0; i < mKeys.size(); i++)
    {
        IniKey *key = mKeys[i];
           delete key;
    }
    mKeys.clear();
}

//IniKey function
IniKey* IniSection::getFirst()
{
   	mKeyIter = mKeys.begin();
    if(mKeyIter != mKeys.end())
    {
        return (*mKeyIter);
    }
    return nullptr;
}

IniKey* IniSection::getNext()
{
    if(mKeyIter != mKeys.end())
    {
        mKeyIter++;
        if(mKeyIter != mKeys.end())
        {
            return (*mKeyIter);
        }
    }
    return nullptr;
}

IniKey* IniSection::getKey(const string& keyName, bool create)
{
    //Go trough the key list and return key with key name
    KeyItor k_pos;
    for (k_pos = mKeys.begin(); k_pos != mKeys.end(); k_pos++)
    {
        if ( compareNoCase( (*k_pos)->mKey, keyName ) )
        {
            return *k_pos;
        }
    }

    if(create)
    {
        createKey(keyName);
        return getKey(keyName, false);
    }
    return nullptr;
}

IniKey* IniSection::getKey(int i)
{
    if(i < mKeys.size() && i > -1)
    {
        return mKeys[i];
    }
    return nullptr;
}

IniKey* IniSection::operator[](int i)
{
    return getKey(i);
}

string IniSection::getNonKeysAsString()
{
    string tmp = "";
       NonKeyItor listPos;
    if(!mNonKeys.size())
    {
        return tmp;
    }
    for(listPos = mNonKeys.begin(); listPos != mNonKeys.end(); listPos++)
    {
        if ((*listPos).size())
        {
            tmp += (*listPos);
            tmp += "\n";
        }
    }
    return tmp;
}

string IniSection::asString(const char& delimiter) const
{
    string tmp = "";
    ConstKeyItor listPos;

    for(listPos = mKeys.begin(); listPos != mKeys.end(); listPos++)
    {
        if ((*listPos)->asString().size())
        {
            tmp += (*listPos)->asString();
            tmp += "\n";
        }
    }
    return tmp;
}

IniKey* IniSection::createKey(const string& mKey, const string& mValue, const string& mComment)
{
    IniKey* pKey = getKey(mKey);
    //Check if the key exists
    if(pKey)
    {
        pKey->mValue = mValue;
        pKey->mComment = mComment;
        return pKey;
    }

    //Create the key
    pKey = new IniKey;
    pKey->mKey = mKey;
    pKey->mValue = mValue;
    pKey->mComment = mComment;
    mIsDirty = true;
    mKeys.push_back(pKey);
    return pKey;
}

size_t IniSection::keyCount()
{
    return mKeys.size();
}

size_t IniSection::nonKeyCount()
{
    return mNonKeys.size();
}

void IniSection::clear()
{
    mKeys.clear();
    mNonKeys.clear();
}

}
