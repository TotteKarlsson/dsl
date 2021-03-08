#pragma hdrstop
#include "dslLogFile.h"
#include <sstream>
//---------------------------------------------------------------------------
namespace dsl
{

using namespace std;

LogFile::LogFile(const string& name)
:
mFILEHandle(fopen(name.c_str(), "w")),
mFileName(name)
{
    if (!mFILEHandle)
    {
        stringstream msg;
        msg << "Failed to open logfile: " <<name;
        throw std::runtime_error(msg.str());
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
