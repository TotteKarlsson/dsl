#include <iomanip>
#include "dslException.h"
#include "dslLogger.h"
#include "dslSQLite.h"
#include "dslSQLiteTable.h"
#include "dslUtils.h"

using namespace dsl;
int main()
{
try
{
    LogOutput::mLogToConsole = true;
    gLogger.setLogLevel(lDebug4);
    SQLite db;
    string dbName("p:/moleculix/Misc/DataBase/moleculix.db");
    db.open(dbName);


    if(!db.isOpen() || !db.tableExists("compounds"))
    {
        throw(DSLException("Failed to open data base"));
    }
    //SQLiteQuery q = db.execQuery("select * from SBMLTests order by 1;");
    SQLiteTable t = db.getTable("select CompoundID, short_name, long_name, note from compounds;");

    if(t.numFields() == 0)
    {
        throw(DSLException("The table is empty.."));
    }

//    t.setRow(0);
//    stringstream msg;
//    for(int i = 0; i < t.numFields() ; i++)
//    {
//        msg<<left<<setw(25)<<t.fieldName(i);
//    }
//
//    Log(lInfo)<<msg.str();
//    msg.str("");
//
//    //Fill out cells
//    for (int row = 0; row < t.nrRows(); row++)
//    {
//        t.setRow(row);
//        for (int field = 0; field < t.numFields(); field++)
//        {
//            if (!t.fieldIsNull(field))
//            {
//                msg << left<<setw(25)<<t.fieldValue(field);
//            }
//        }
//        Log(lInfo)<<msg.str();
//        msg.str("");
//    }

    //Or simpler
    Log(lInfo) << t.asString();
}
catch(const DSLException& ex)
{
    Log(lError)<<ex.what();
}
      return 0;
}

#if defined(CG_IDE)

#if defined(DSL_STATIC)
    #pragma comment(lib, "dslCommon-static.lib")
    #pragma comment(lib, "dslDataBase-static.lib")
#else
    #pragma comment(lib, "dslCommon.lib")
    #pragma comment(lib, "dslDataBase.lib")
#endif


#pragma comment(lib, "SQLite-static.lib")
#pragma comment(lib, "poco_foundation-static.lib")


#endif



