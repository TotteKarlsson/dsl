#ifndef dslSQLiteTableH
#define dslSQLiteTableH
#include <string>
#include <vector>
#include "dslObject.h"
#include "DataBaseExporter.h"
//---------------------------------------------------------------------------

using std::string;
using std::vector;
namespace dsl
{

class DSL_DB SQLiteTable : DSLObject
{
    public:
                                            SQLiteTable();
                                            SQLiteTable(const SQLiteTable& rTable);
                                            SQLiteTable(char** paszResults, int nRows, int nCols);
        virtual                            ~SQLiteTable();
        SQLiteTable&                        operator=(const SQLiteTable& rTable);
        int                                 numFields() const;
        int                                 nrRows() const;
        int                                 nrCols() const;
        string                              asString(const char& del = ' ') const;

        void                                setRow(int nRow) const;
        const char*                         fieldName(int nCol) const;
        const char*                         fieldValue(int nField) const;
        const char*                         fieldValue(const char* szField) const;

        int                                 getIntField(int nField, int nNullValue=0);
        int                                 getIntField(const char* szField, int nNullValue=0);
        sqlite_int64                        getInt64Field(int nField, sqlite_int64 nNullValue=0);
        sqlite_int64                        getInt64Field(const char* szField, sqlite_int64 nNullValue=0);

        double                              getFloatField(int nField, double fNullValue=0.0);
        double                              getFloatField(const char* szField, double fNullValue=0.0);

        const char*                         getStringField(int nField, const char* szNullValue="") const;
        const char*                         getStringField(const char* szField, const char* szNullValue="") const;

        const unsigned char*                getBlobField(int nField, int& nLen);
        const unsigned char*                getBlobField(const char* szField, int& nLen);

        bool                                fieldIsNull(int nField) const;
        bool                                fieldIsNull(const char* szField) const;
        void                                finalize();

     protected:
        int                                 mnCols;
        int                                 mnRows;
        mutable int                         mnCurrentRow;
        char**                              mpaszResults;
        void                                checkResults() const;
        string                              mName;
        vector<string>                      mColumnHeaders;
};
}
#endif

