#pragma hdrstop
#include "dslLogFile.h"
//---------------------------------------------------------------------------
namespace dsl
{

LogFile::LogFile(const string& name)
:
mFILEHandle(fopen(name.c_str(), "w")),
mFileName(name)
{
    if (!mFILEHandle)
    {
        throw std::runtime_error("File Open failure");
    }
    else
    {
        fclose(mFILEHandle);
		mFILEHandle = fopen(name.c_str(), "a");
    }
}

LogFile::~LogFile()
{
    fclose(mFILEHandle);
}

string LogFile::getFileName()
{
    return mFileName;
}

}
