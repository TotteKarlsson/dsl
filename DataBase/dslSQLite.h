#ifndef dslSQLiteH
#define dslSQLiteH
#include "dslObject.h"
#include "DataBaseExporter.h"

namespace dsl
{
//Thhe SQLite class is a wrapper aroung a sqlite database
class SQLiteTable;
class SQLiteQuery;
class SQLiteStatement;

class DSL_DB SQLite : DSLObject
{
    public:
                                                        SQLite(const string& name = gEmptyString, bool autoOpen = false);
        virtual                                         ~SQLite();
        sqlite3*                                        getHandle();
        bool                                            open(const string& szFile, bool autoCreate = false);
        bool                                            close();
        bool                                            tableExists(const string& szTable);

        int                                             execDML(const char* szSQL);
        SQLiteQuery                                     execQuery(const char* szSQL);
        int                                             execScalar(const char* szSQL, int nNullValue=0);
        string                                          execString(const string& szSQL, const string& nNullValue = gEmptyString);
        SQLiteTable                                     getTable(const string& szSQL);
        SQLiteStatement                                 compileStatement(const char* szSQL);
        sqlite_int64                                    lastRowId();
        void                                            interrupt();
        void                                            setBusyTimeout(int nMillisecs);

        static const char*                              version();
        static const char*                              libraryVersion();
        static int                                      libraryVersionNumber();
        bool                                            isAutoCommitOn();
        bool                                            isOpen();

    private:
        int                                             mnBusyTimeoutMs;
        string                                          mDBName;
        string                                          mLastError;
        sqlite3*                                        mDB;

                                                        //Don't copy db's
                                                        SQLite(const SQLite& db);
        SQLite&                                         operator=(const SQLite& db);

        sqlite3_stmt*                                   compile(const char* szSQL);
        void                                            checkDB();
};

}
#endif
