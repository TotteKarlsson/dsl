#ifndef dslSQLiteQueryH
#define dslSQLiteQueryH
#include <string>
#include "dslObject.h"
#include "DataBaseExporter.h"
#include "dslConstants.h"
//---------------------------------------------------------------------------

namespace dsl
{
class DSL_DB SQLiteQuery : public DSLObject
{
    public:
                                            SQLiteQuery(sqlite3* pDB = nullptr, sqlite3_stmt* pVM = nullptr, bool bEof = false, bool bOwnVM=true);
                                            SQLiteQuery(const SQLiteQuery& rQuery);
        virtual                            ~SQLiteQuery();
        int                                 numFields();
        SQLiteQuery&                        operator=(const SQLiteQuery& rQuery);
        bool                                Prepare(const string& sql);
        bool                                BindString(int index, char* &Text, int strLength);
        bool                                BindValue(int sql, char* &blob, int numBytes);
        int                                 Exec(const string& str = gEmptyString);
        int                                 fieldIndex(const char* szField);
        const char*                         fieldName(int nCol);
        const char*                         fieldDeclType(int nCol);
        int                                 fieldDataType(int nCol);
        const char*                         fieldValue(int nField);
        const char*                         fieldValue(const char* szField);
        int                                 getIntField(int nField, int nNullValue=0);
        int                                 getIntField(const char* szField, int nNullValue=0);
        sqlite_int64                        getInt64Field(int nField, sqlite_int64 nNullValue=0);
        sqlite_int64                        getInt64Field(const char* szField, sqlite_int64 nNullValue=0);
        double                              getFloatField(int nField, double fNullValue=0.0);
        double                              getFloatField(const char* szField, double fNullValue=0.0);
        const char*                         getStringField(int nField, const char* szNullValue="");
        const char*                         getStringField(const char* szField, const char* szNullValue="");
        const unsigned char*                getBlobField(int nField, int& nLen);
        const unsigned char*                getBlobField(const char* szField, int& nLen);
        bool                                fieldIsNull(int nField);
        bool                                fieldIsNull(const char* szField);
        bool                                eof();
        void                                nextRow();
        void                                finalize();

    protected:
        void                                checkVM();
        sqlite3                            *mpDB;
        sqlite3_stmt                       *mpVM;

        bool                                mbEof;
        int                                 mnCols;
        bool                                mbOwnVM;
};

}
#endif

////class CppSQLite3Query
////{
////public:
////
////    CppSQLite3Query();
////
////    CppSQLite3Query(const CppSQLite3Query& rQuery);
////
////    CppSQLite3Query(sqlite3* pDB,
////                sqlite3_stmt* pVM,
////                bool bEof,
////                bool bOwnVM=true);
////
////    CppSQLite3Query& operator=(const CppSQLite3Query& rQuery);
////
////    virtual ~CppSQLite3Query();
////
////    int numFields();
////
////    int fieldIndex(const char* szField);
////    const char* fieldName(int nCol);
////
////    const char* fieldDeclType(int nCol);
////    int fieldDataType(int nCol);
////
////    const char* fieldValue(int nField);
////    const char* fieldValue(const char* szField);
////
////    int getIntField(int nField, int nNullValue=0);
////    int getIntField(const char* szField, int nNullValue=0);
////
////    sqlite_int64 getInt64Field(int nField, sqlite_int64 nNullValue=0);
////    sqlite_int64 getInt64Field(const char* szField, sqlite_int64 nNullValue=0);
////
////    double getFloatField(int nField, double fNullValue=0.0);
////    double getFloatField(const char* szField, double fNullValue=0.0);
////
////    const char* getStringField(int nField, const char* szNullValue="");
////    const char* getStringField(const char* szField, const char* szNullValue="");
////
////    const unsigned char* getBlobField(int nField, int& nLen);
////    const unsigned char* getBlobField(const char* szField, int& nLen);
////
////    bool fieldIsNull(int nField);
////    bool fieldIsNull(const char* szField);
////
////    bool eof();
////
////    void nextRow();
////
////    void finalize();
////
////private:
////
////    void checkVM();
////
////    sqlite3* mpDB;
////    sqlite3_stmt* mpVM;
////    bool mbEof;
////    int mnCols;
////    bool mbOwnVM;
////};

