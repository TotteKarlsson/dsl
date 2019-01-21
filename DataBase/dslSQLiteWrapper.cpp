#pragma hdrstop
#include <sstream>
#include "dslException.h"
#include "dslConstants.h"
#include "dslUtils.h"
#include "dslSQLiteTable.h"
#include "dslSQLiteWrapper.h"
//---------------------------------------------------------------------------
using namespace std;
using namespace dsl;
namespace dsl
{

SQLiteWrapper::SQLiteWrapper(const string& dbFile)
:
mDBFile(dbFile)
{
}

SQLiteWrapper::~SQLiteWrapper()
{}


//DB stuff
bool SQLiteWrapper::open(const string& dbFileName)
{
    if(fileExists(dbFileName))
    {
        return mDB.open(dbFileName);
    }
    return false;
}

bool SQLiteWrapper::close()
{
    return mDB.close();
}

bool SQLiteWrapper::isOpen()
{
    return mDB.isOpen();
}

string SQLiteWrapper::getInfo()
{
    stringstream info;
    info << "\n==== Implement this in descendants ===\n";
    return info.str();
}


}