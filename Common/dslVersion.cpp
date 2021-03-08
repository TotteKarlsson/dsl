#pragma hdrstop
#include "dslVersion.h"
#include "dslStringList.h"
#include "dslUtils.h"
#include <sstream>
//---------------------------------------------------------------------------

namespace dsl
{
using namespace std;

Version::Version(const string& version)
{
    parse(version);
}

bool Version::parse(const string& input)
{
    StringList vers(input,'.');
    if(vers.size() < 2)
    {
        return false;
    }

    mMajor = toInt(vers[0]);
    mMinor = toInt(vers[1]);
    if(vers.size() > 2)
    {
        mPatch = toInt(vers[2]);
    }
    else
    {
        mPatch = 0;
    }

    if(vers.size() > 3)
    {
        mBuild = toInt(vers[3]);
    }
    else
    {
        mBuild = 0;
    }
    return true;
}

string Version::asString(const string& format) const
{
    stringstream st;
    if(format == "all")
    {
        st << getMajor() << "." << getMinor() << "." << getPatch() << "." << getBuild();
    }
    else if(format == "major.minor.patch")
    {
        st << getMajor() << "." << getMinor() << "." << getPatch();
    }
    else if(format == "major.minor")
    {
        st << getMajor() << "." << getMinor();
    }
    else
    {
        st << getMajor() << "." << getMinor() << "." << getPatch() << "." << getBuild();
    }
    return st.str();
}

int Version::getMajor() const
{
    return mMajor;
}

int Version::getMinor() const
{
    return mMinor;
}

int Version::getPatch() const
{
    return mPatch;
}

int Version::getBuild() const
{
    return mBuild;
}

bool operator < (const Version& l, const Version& r)
{
    double left = toDouble(l);
    double right = toDouble(r);

    return left < right;
}

bool operator > (const Version& l, const Version& r)
{
    double left = toDouble(l);
    double right = toDouble(r);

    return left > right;
}

bool operator == (const Version& l, const Version& r)
{
    double left = toDouble(l);
    double right = toDouble(r);

    return left == right;
}

ostream& operator << (ostream& st, const Version& ver)
{
    st<<ver.asString();
    return st;
}

//Idea from https://gist.github.com/kjk/458186
double toDouble(const Version& ver)
{
    double val;
    val = ver.getMajor();
    val += ver.getMinor() /100.0;
    val += ver.getPatch() /10000.0;
    val += ver.getBuild() /100000.0;
    return val;
}

}
