#pragma hdrstop
#include "dslNumberBuilder.h"
//---------------------------------------------------------------------------
namespace dsl
{
void NumberBuilder::Init(const string& val)
{
    if(val.size())
    {
        mTheString = val;
        mIsFresh = false;
    }
    else
    {
        mTheString = "0.0";
        mIsFresh = true;
    }
 }
void NumberBuilder::AddChar(char* aChar)
{
    if(mIsFresh && aChar != ".")
    {
        mTheString="";
    }
    if(mTheString.size() >= 14)
    {
        mTheString[mTheString.size()] = aChar[0];
    }
    else
    {
        mTheString += aChar;
    }
    mIsFresh = false;
}
void NumberBuilder::RemoveLastChar()
{
    if(mTheString.size() == 1)
    {
        Init("");
        mIsFresh = true;
    }
    else
    {
        mTheString.erase(mTheString.end()-1);
    }
}
void NumberBuilder::SwitchSign()
{
    if(mTheString[0] != '-')
    {
        mTheString = "-" + mTheString;
    }
    else
    {
        //mTheString[1] = ' ';
        mTheString = mTheString.erase(0,1);
    }
}
            NumberBuilder::NumberBuilder(const string& str) : mTheString(str), mIsFresh(true){}
string         NumberBuilder::GetString()        {return mTheString;}
char           NumberBuilder::GetLastChar()    {return mTheString.at(mTheString.size() -1);}
bool        NumberBuilder::HasDot()        {return mTheString.find('.') == string::npos ? false : true;}
void         NumberBuilder::Clear()            {mTheString = "";}
bool         NumberBuilder::IsFresh()        {return mIsFresh;}
}
