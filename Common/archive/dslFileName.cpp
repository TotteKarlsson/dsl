#pragma hdrstop
#include "dslStringUtils.h"
#include "dslFileName.h"
//---------------------------------------------------------------------------
namespace dsl
{

using std::ostream;

FileName::FileName(const string& name, const string& path)
{
    setNameAndPath(path, name);
}

FileName::~FileName()
{}

FileName::FileName(const FileName& fN)
{
    mPath = fN.getPath();
    mName = fN.getFileName();
    makeFileString();
}

FileName& FileName::operator=(const FileName& fN)
{
    mPath = fN.getPath();
    mName = fN.getFileName();
    makeFileString();
    return *this;
}

FileName& FileName::operator=(const string& fN)
{
    mPathAndName = fN;
    mPath = getFilePath(fN);
    mName = getFileNameNoPath(fN);
    return *this;
}

bool FileName::operator!=(const char* fN)
{
    return (mName != fN) ? false : true;
}

string FileName::getFileName() const {return mName;}
string FileName::getPath() const {return mPath;}
const string FileName::getPathAndFileName() const {return mPathAndName;}
uint FileName::size(){return mName.size();}

FileName::operator string() {return mPathAndName;}
string FileName::get()
{
    makeFileString();
    return mPathAndName;
}

string FileName::getFileNameNoExtension() const
{
    //remove extension
    return dsl::getFileNameNoExtension(getFileName());
}

void FileName::setFileName(const string& name)
{
    mName = name;
    makeFileString();
}

bool FileName::setPath(const string& path)
{
    mPath = path;
    makeFileString();
    return true;
}

void FileName::setNameAndPath(const string& path, const string& name)
{
    mPath = path;
    mName = name;
    makeFileString();
}

void FileName::setFileNameAndPath(const string& file)
{
    if(!file.size())
    {
        mPathAndName = "";
        mName = "";
        mPath = "";
    }
    else
    {
        mName = getFileNameNoPath(file);
        mPath = getFilePath(file);
        makeFileString();
    }
}

void FileName::makeFileString()
{
    mPathAndName = "";
    if(mPath.size())
    {
        if(mPath[mPath.size()-1] == '\\')
        {
            mPathAndName = mPath + mName;
        }
        else //Add slashes to path
        {
            //exit(-1);
            mPath = mPath + "\\";
            mPathAndName = mPath + mName;
        }
    }
    else // No path
    {
        if(mName.size())
        {
            mPathAndName += mName;
        }
    }
}

ostream& operator <<(ostream& os, FileName& obj)
{
    os<<obj.get();
    return os;
}

}
