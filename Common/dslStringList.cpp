#pragma hdrstop
#include "dslStringList.h"
#include "dslUtils.h"
#include "dslStringUtils.h"
#include "dslException.h"
#include <cctype>
#include <algorithm>
#include <iostream>
#include <sstream>
//---------------------------------------------------------------------------
using namespace std;

namespace dsl
{
    typedef unsigned int uint;
StringList::StringList(const vector<int>& ints)
:
mStrings(),
mDelimiter(',')
{
	for(uint i = 0; i < ints.size(); i++)
    {
    	mStrings.push_back(toString(ints[i]));
    }
}

StringList::StringList(const vector<string>& strings)
:
mStrings(strings),
mDelimiter(',')
{}

StringList::StringList(const string& str, const char delimiter)
{
    mDelimiter = delimiter;
    if(str.size())
    {
        mStrings = split(str, delimiter);
    }
}

StringList::StringList(const StringList& cp)
{
    mStrings = cp.mStrings;
    mDelimiter = cp.mDelimiter;
}

StringList::~StringList()
{}


void StringList::strip(const StringList& chars)
{
    for(int i = 0; i < chars.count(); i++)
    {
        for(uint j = 0; j < count(); j++)
        {
        	mStrings[j]  = dsl::stripCharacters(chars[i], mStrings[j]);
        }
    }
}

void StringList::outerStrip(const StringList& chars)
{
    if(count())
    {
        for(int i = 0; i < chars.count(); i++)
    	{
        	mStrings[0] = dsl::stripCharacters(chars[i], mStrings[0]);
			mStrings[count() - 1] = dsl::stripCharacters(chars[i], mStrings[count() - 1]);
        }
    }
}

bool is_not_digit(char c)
{
    return !std::isdigit(c);
}

bool numeric_string_compare(const string& str1, const string& str2)
{
    // handle empty strings...
    string::const_iterator it1 = str1.begin(), it2 = str2.begin();

    if (std::isdigit(str1[0]) && std::isdigit(str2[0]))
    {
        int n1, n2;
        std::stringstream ss(str1);
        ss >> n1;
        ss.clear();

        ss.str(str2);
        ss >> n2;

        if (n1 != n2)
        {
        	return n1 < n2;
        }

        it1 = std::find_if(str1.begin(), str1.end(), is_not_digit);
        it2 = std::find_if(str2.begin(), str2.end(), is_not_digit);
    }

    return std::lexicographical_compare(it1, str1.end(), it2, str2.end());
}

void StringList::sort()
{
	::sort(mStrings.begin(), mStrings.end(), numeric_string_compare);
}

bool StringList::reverse()
{
	std::reverse(mStrings.begin(), mStrings.end());
    return true;
}
string StringList::popBack()
{
	string s = mStrings.back();
    mStrings.pop_back();
    return s;
}

string StringList::popFront()
{
	if(!mStrings.size())
    {
    	return "";
    }

	string s = mStrings.front();
    mStrings.erase(mStrings.begin());
    return s;
}

char StringList::getDelimiter() const
{
    return mDelimiter;
}

StringList StringList::operator-(const StringList& rhs)
{
    StringList newList;
    for(uint i = 0; i < count(); i++)
    {
        string item = mStrings[i] + "-" + rhs[i];
        newList.append(item);
    }

    return newList;
}

StringList& StringList::operator=(const StringList& rhs)
{
    mStrings = rhs.mStrings;
    mDelimiter = rhs.mDelimiter;
    return *this;
}

StringList& StringList::operator=(const vector<string>& rhs)
{
    mStrings = rhs;
    return *this;
}

//Converison operator
StringList::operator const vector<string>&() const
{
    return mStrings;
}

bool StringList::operator!=(const StringList& rhs)
{
    if(mStrings.size() != rhs.count())
    {
        return true;
    }
    for(int i = 0; i < mStrings.size(); i++)
    {
        if(mStrings[i] != rhs[i])
        {
            return true;
        }
    }

    return false;
}

//Converison operator
const vector<string>& StringList::getContainer()
{
	return mStrings;
}

void StringList::reSize(int size)
{
    mStrings.resize(size);
}

void StringList::truncate(int linesAfter)
{
    reSize(linesAfter);
}

vector<string>::iterator StringList::begin()
{
    return mStrings.begin();
}

vector<string>::iterator StringList::end()
{
    return mStrings.end();
}

string StringList::at(int index)
{
	if ((uint)index > count() - 1)
	{
		stringstream msg;
		msg << "index (" << index << ") out of bounds in StringList with count " << count();

		throw(DSLException(msg.str()));
	}
	return mStrings[index];
}

string& StringList::operator[](int index)
{
    if((uint) index > count() -1 )
    {
        stringstream msg;
        msg<<"index ("<<index<<") out of bounds in StringList with count "<<count();

        throw(DSLException(msg.str()));
    }
    return mStrings[index];
}

const string& StringList::operator[](int index) const
{
    if((uint) index > count() -1 )
    {
        stringstream msg;
        msg<<"index ("<<index<<") out of bounds in StringList with count "<<count();

        throw(DSLException(msg.str()));
    }

    return mStrings[index];
}

size_t StringList::size() const
{
    return mStrings.size();
}

size_t StringList::count() const
{
    return mStrings.size();
}

string StringList::asString(const char& delimiter) const
{
    stringstream names;
    for(uint i = 0; i < mStrings.size(); i++)
    {
        names << mStrings[i];
        if(i < mStrings.size() - (uint) 1)
        {
            if(delimiter != '\0')
            {
                names << delimiter;
            }
            else
            {
                names << mDelimiter;
            }
        }
    }
    return names.str();
}

void StringList::preFix(const string& fix)
{
     for(mLI = mStrings.begin(); mLI != mStrings.end(); mLI++)
    {
        (*mLI) = fix + (*mLI) ;
    }
}

void StringList::postFix(const string& fix)
{
    for(mLI = mStrings.begin(); mLI != mStrings.end(); mLI++)
    {
        (*mLI) = (*mLI) + fix;
    }
}

void StringList::insertAt(int index, const string& item)
{
    if(count() == 0)
    {
        mStrings.push_back(item);
        return;
    }

    mLI = mStrings.begin() + index;
    if(mLI != mStrings.end())
    {
        mStrings.insert(mLI, item);
    }
}

void StringList::appendList(const StringList& list)
{
    for(uint i = 0; i < list.count(); i++)
    {
        mStrings.push_back(list[i]);
    }
}

void StringList::append(int item)
{
    mStrings.push_back(dsl::toString(item));
}

void StringList::append(const string& item)
{
    mStrings.push_back(item);
}

int StringList::find(const string& item) const
{
    return dsl::indexOf(mStrings, item);
}

int StringList::indexOf(const string& item)
{
    return dsl::indexOf(mStrings, item);
}

string StringList::getFirstLineStartingWith(const string& item, bool ignoreWhiteSpace) const
{
	for(int i = 0; i < mStrings.size(); i++)
    {
        string line(mStrings[i]);
        if(ignoreWhiteSpace)
	    {
            line = trimWS(line);
        }

    	if(dsl::startsWith(item, line))
        {
        	return mStrings[i];
        }
    }
	return "";
}

string StringList::getLineContaining(const string& subStr)
{
	for(int i = 0; i < mStrings.size(); i++)
    {
    	if(dsl::contains(subStr, mStrings[i]))
        {
        	return mStrings[i];
        }
    }
	return "";
}

void StringList::removeAt(int index)
{
    mLI = mStrings.begin() + index;
    mStrings.erase(mLI);
}


bool StringList::hasString(const string& item, bool caseSensitive) const
{
    for(int i = 0; i < count(); i++)
    {
        bool equal(false);
        //Only coimpare string with equal size
        if(item.size() == mStrings[i].size())
        {
            CASE_SENSITIVITY cs = caseSensitive ? csCaseSensitive : csCaseInsensitive;
            if(compareStrings(item, mStrings[i], cs))
            {
                return true;
            }
        }
    }
    return false;
}


bool StringList::contains(const string& item) const
{
    return std::find(mStrings.begin(), mStrings.end(), item) != mStrings.end() ? true : false;
}

bool StringList::dontContain(const string& item) const
{
    return !contains(item);
}

bool isRHSLonger(string const& lhs, string const& rhs)
{
    return lhs.size() < rhs.size();
}

string StringList::getLongest()
{
	mLI = std::max_element(mStrings.begin(), mStrings.end(), isRHSLonger);
    return *mLI;
}

string StringList::getShortest()
{
    mLI = std::min_element(mStrings.begin(), mStrings.end(), isRHSLonger);
    return *mLI;
}

void StringList::clear()
{
    mStrings.clear();
}

void StringList::empty()
{
    mStrings.clear();
}

ostream& operator<<(ostream& stream, const StringList& list)
{
    stream<<"{";
    for(uint i = 0; i < list.count(); i++)
    {
        stream<<"\""<<list[i]<<"\"";
        if(i < list.count() - (uint) 1)
        {
            stream<<",";
        }

    }
    stream<<"}";
    return stream;
}


//std::string toString(const vector<string>& sl)
//{
//	StringList s(sl);
//	return s.asString();
//}

std::string toString(const StringList& sl)
{
    return sl.asString();
}

}

