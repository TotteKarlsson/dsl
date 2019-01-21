#pragma hdrstop
#include "dslStringBuilder.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------


namespace dsl
{

StringBuilder::StringBuilder(const char& del)
 :
mDelimiter(del),
mIsBuilding(false),
mTheString(""),
mHasString(false),
mNrOfDels(0)
{}

void StringBuilder::reset()
{
    mIsBuilding = false;
    mHasString = false;
    mNrOfDels = 0;
    mTheString.clear();
}

void StringBuilder::setDelimiter(const char& rDel)
{
    mDelimiter = (rDel);
}

bool StringBuilder::build(const char& ch)
{
    //If we are looking for end of lines, we are "always" building
    if(ch == mDelimiter && mTheString.size() > 0)
    {
        mHasString = true;
        mIsBuilding = false;
        return true;
    }
    else if(ch == mDelimiter)
    {
        return false;
    }

    //Insert the character, discard irrelevant ones
    if(!(ch == '\r'))
    {
    	mTheString += ch;
    }
    return true;
}

string StringBuilder::getString()
{
    return mTheString;
}

}
