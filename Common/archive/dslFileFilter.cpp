#pragma hdrstop
#include "dslFileFilter.h"
#include <algorithm>
#include <sstream>
//---------------------------------------------------------------------------
namespace dsl
{

using namespace std;

FileFilter::FileFilter(int filter)
{
    addFilter(filter);
}

bool FileFilter::addFilters(const StringList& filters)
{
    for(unsigned int i = 0; i < filters.size(); i++)
    {
        Path f(filters[i]);
        if(f.isFile())
        {
            mFilters.append(filters[i]);
        }
        else
        {
            string ext = f.getExtension();
            if(ext.size())
            {
                mFilters.append(ext);
            }
        }
    }
    return true;
}

bool FileFilter::addFilter(unsigned int filter)
{
    //Check integer for 'bits'
    if( (filter) & ffCPPHeaders )
    {
        if(!mFilters.contains("h"))
        {
            mFilters.append("h");
        }
    }

    if( filter & ffCPPSource )
    {
        if(!mFilters.contains("cpp"))
        {
            mFilters.append("cpp");
        }
    }

    if( filter & ffCPPUnits )
    {
        if(!mFilters.contains("h"))
        {
            mFilters.append("h");
        }
        if(!mFilters.contains("cpp"))
        {
            mFilters.append("cpp");
        }
    }

    if( filter & ffCMakeFiles)
    {
        if(!mFilters.contains("CMakeList.txt"))
        {
            mFilters.append("CMakeList.txt");
        }
    }
    return true;
}

size_t FileFilter::size() const
{
    return mFilters.count();
}

string FileFilter::operator[](int index) const
{
    return mFilters[index];
}

string FileFilter::toString() const
{
    stringstream ss;
    ss <<mFilters.asString('\n');
    return ss.str();
}

bool FileFilter::containExtension(const string& ext) const
{
    return mFilters.find(ext) == -1 ? false : true;
}

ostream& operator<<(ostream& os, const FileFilter& ff)
{
    os<<ff.toString();
    return os;
}

}