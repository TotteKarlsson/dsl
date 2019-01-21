#pragma hdrstop
#include "dslRange.h"
#include "dslStringList.h"
#include <sstream>
//---------------------------------------------------------------------------

namespace dsl
{
using namespace std;

string toString(const Range<double>& range)
{
	stringstream s;
    s<<"["<<range.getMin()<<":"<<range.getMax()<<"]";
	return s.str();
}

Range<double> getRange(const string& val)
{
	string tmp = stripCharacters("[]", val);
	StringList r(tmp, ':');
    if(r.count() == 2)
    {
    	return Range<double>(toDouble(r[0]), toDouble(r[1]));
    }
    else
    {
    	return Range<double>(0,0);
    }
}

}