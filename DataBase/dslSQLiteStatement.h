#ifndef dslSQLiteStatementH
#define dslSQLiteStatementH
#include "DataBaseExporter.h"
#include "dslSQLiteQuery.h"
//---------------------------------------------------------------------------

struct sqlite3;
struct sqlite3_stmt;
namespace dsl
{
class DSL_DB SQLiteStatement
{
    public:
        SQLiteStatement();
        SQLiteStatement(const SQLiteStatement& rStatement);
        SQLiteStatement(sqlite3* pDB, sqlite3_stmt* pVM);
        virtual ~SQLiteStatement();
        SQLiteStatement& operator=(const SQLiteStatement& rStatement);
        int execDML();
        SQLiteQuery execQuery();
        void bind(int nParam, const char* szValue);
        void bind(int nParam, const int nValue);
        void bind(int nParam, const double dwValue);
        void bind(int nParam, const unsigned char* blobValue, int nLen);
        void bindNull(int nParam);
        int  bindParameterIndex(const char* szParam);
        void bind(const char* szParam, const char* szValue);
        void bind(const char* szParam, const int nValue);
        void bind(const char* szParam, const double dwValue);
        void bind(const char* szParam, const unsigned char* blobValue, int nLen);
        void bindNull(const char* szParam);
        void reset();
        void finalize();

    private:
        void checkDB();
        void checkVM();
        sqlite3* mpDB;
        sqlite3_stmt* mpVM;
};
}

#endif

////class CppSQLite3Statement
////{
////public:
////
////    CppSQLite3Statement();
////
////    CppSQLite3Statement(const CppSQLite3Statement& rStatement);
////
////    CppSQLite3Statement(sqlite3* pDB, sqlite3_stmt* pVM);
////
////    virtual ~CppSQLite3Statement();
////
////    CppSQLite3Statement& operator=(const CppSQLite3Statement& rStatement);
////
////    int execDML();
////
////    CppSQLite3Query execQuery();
////
////    void bind(int nParam, const char* szValue);
////    void bind(int nParam, const int nValue);
////    void bind(int nParam, const double dwValue);
////    void bind(int nParam, const unsigned char* blobValue, int nLen);
////    void bindNull(int nParam);
////
////    int bindParameterIndex(const char* szParam);
////    void bind(const char* szParam, const char* szValue);
////    void bind(const char* szParam, const int nValue);
////    void bind(const char* szParam, const double dwValue);
////    void bind(const char* szParam, const unsigned char* blobValue, int nLen);
////    void bindNull(const char* szParam);
////
////    void reset();
////
////    void finalize();
////
////private:
////
////    void checkDB();
////    void checkVM();
////
////    sqlite3* mpDB;
////    sqlite3_stmt* mpVM;
////};
