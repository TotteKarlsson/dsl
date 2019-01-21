#pragma hdrstop
#include <string.h>
#include <cstring>
#include "sqlite/sqlite3.h"
#include "dslSQLite.h"
#include "dslSQLiteException.h"
#include "dslSQLiteQuery.h"
//---------------------------------------------------------------------------
//

namespace dsl
{

SQLiteQuery::SQLiteQuery(const SQLiteQuery& rQuery)
{
    mpVM = rQuery.mpVM;
    // Only one object can own the VM
    const_cast<SQLiteQuery&>(rQuery).mpVM = 0;
    mbEof = rQuery.mbEof;
    mnCols = rQuery.mnCols;
    mbOwnVM = rQuery.mbOwnVM;
}

SQLiteQuery::SQLiteQuery(sqlite3* pDB, sqlite3_stmt* pVM, bool bEof, bool bOwnVM/*=true*/)
{
    mpDB = pDB;
    mpVM = pVM;
    mbEof = bEof;
    mnCols = sqlite3_column_count(mpVM);
    mbOwnVM = bOwnVM;
}


SQLiteQuery::~SQLiteQuery()
{
    try
    {
        finalize();
    }
    catch (...)
    {
    }
}

SQLiteQuery& SQLiteQuery::operator=(const SQLiteQuery& rQuery)
{
    try
    {
        finalize();
    }
    catch (...)
    {
    }
    mpVM = rQuery.mpVM;

    // Only one object can own the VM
    const_cast<SQLiteQuery&>(rQuery).mpVM = 0;
    mbEof = rQuery.mbEof;
    mnCols = rQuery.mnCols;
    mbOwnVM = rQuery.mbOwnVM;
    return *this;
}

bool SQLiteQuery::Prepare(const string& sql)
{
    if (sqlite3_prepare_v2(mpDB , sql.c_str(), -1, &mpVM, nullptr) != SQLITE_OK)
    {
        return false;
    }
    return true;
}

bool SQLiteQuery::BindString(int index, char* &Text, int strLength)
{
    if (sqlite3_bind_text(mpVM, index, Text, strLength, SQLITE_TRANSIENT) != SQLITE_OK)
    {
        return false;
    }

    return true;
}

bool SQLiteQuery::BindValue(int index, char* &blob, int numBytes)
{
    if (sqlite3_bind_blob(mpVM, index, blob, numBytes, SQLITE_TRANSIENT) != SQLITE_OK)
    {
        return false;
    }

    return true;
}

int SQLiteQuery::Exec(const string& str)
{
	int rows = -1;
	if(str.size())
	{
		//checkDB();
		char* szError=0;

		int nRet = sqlite3_exec(mpDB, str.c_str(), 0, 0, &szError);

		if (nRet == SQLITE_OK)
		{
			return sqlite3_changes(mpDB);
		}
		else
		{
			throw SQLiteException(nRet, szError);
		}
	}

	if(sqlite3_step(mpVM) != SQLITE_DONE)
	{
		sqlite3_reset(mpVM);
	}
	return rows;
}

int SQLiteQuery::numFields()
{
	checkVM();
	return mnCols;
}

const char* SQLiteQuery::fieldValue(int nField)
{
	checkVM();

	if (nField < 0 || nField > mnCols-1)
	{
        throw SQLiteException(CPPSQLITE_ERROR,
                                "Invalid field index requested");
    }

    return (const char*)sqlite3_column_text(mpVM, nField);
}


const char* SQLiteQuery::fieldValue(const char* szField)
{
    int nField = fieldIndex(szField);
    return (const char*)sqlite3_column_text(mpVM, nField);
}


int SQLiteQuery::getIntField(int nField, int nNullValue/*=0*/)
{
    if (fieldDataType(nField) == SQLITE_NULL)
    {
        return nNullValue;
    }
    else
    {
        return sqlite3_column_int(mpVM, nField);
    }
}


int SQLiteQuery::getIntField(const char* szField, int nNullValue/*=0*/)
{
    int nField = fieldIndex(szField);
    return getIntField(nField, nNullValue);
}


sqlite_int64 SQLiteQuery::getInt64Field(int nField, sqlite_int64 nNullValue/*=0*/)
{
    if (fieldDataType(nField) == SQLITE_NULL)
    {
        return nNullValue;
    }
    else
    {
        return sqlite3_column_int64(mpVM, nField);
    }
}


sqlite_int64 SQLiteQuery::getInt64Field(const char* szField, sqlite_int64 nNullValue/*=0*/)
{
    int nField = fieldIndex(szField);
    return getInt64Field(nField, nNullValue);
}


double SQLiteQuery::getFloatField(int nField, double fNullValue/*=0.0*/)
{
    if (fieldDataType(nField) == SQLITE_NULL)
    {
        return fNullValue;
    }
    else
    {
        return sqlite3_column_double(mpVM, nField);
    }
}


double SQLiteQuery::getFloatField(const char* szField, double fNullValue/*=0.0*/)
{
    int nField = fieldIndex(szField);
    return getFloatField(nField, fNullValue);
}


const char* SQLiteQuery::getStringField(int nField, const char* szNullValue/*=""*/)
{
    if (fieldDataType(nField) == SQLITE_NULL)
    {
        return szNullValue;
    }
    else
    {
        return (const char*)sqlite3_column_text(mpVM, nField);
    }
}


const char* SQLiteQuery::getStringField(const char* szField, const char* szNullValue/*=""*/)
{
    int nField = fieldIndex(szField);
    return getStringField(nField, szNullValue);
}


const unsigned char* SQLiteQuery::getBlobField(int nField, int& nLen)
{
	checkVM();

    if (nField < 0 || nField > mnCols-1)
    {
        throw SQLiteException(CPPSQLITE_ERROR, "Invalid field index requested");
    }

    nLen = sqlite3_column_bytes(mpVM, nField);
    return (const unsigned char*)sqlite3_column_blob(mpVM, nField);
}


const unsigned char* SQLiteQuery::getBlobField(const char* szField, int& nLen)
{
    int nField = fieldIndex(szField);
    return getBlobField(nField, nLen);
}


bool SQLiteQuery::fieldIsNull(int nField)
{
    return (fieldDataType(nField) == SQLITE_NULL);
}


bool SQLiteQuery::fieldIsNull(const char* szField)
{
    int nField = fieldIndex(szField);
    return (fieldDataType(nField) == SQLITE_NULL);
}


int SQLiteQuery::fieldIndex(const char* szField)
{
    checkVM();

    if (szField)
    {
        for (int nField = 0; nField < mnCols; nField++)
        {
            const char* szTemp = sqlite3_column_name(mpVM, nField);

            if (strcmp(szField, szTemp) == 0)
            {
                return nField;
            }
        }
    }

    throw SQLiteException(CPPSQLITE_ERROR, "Invalid field name requested");
}


const char* SQLiteQuery::fieldName(int nCol)
{
    checkVM();

    if (nCol < 0 || nCol > mnCols-1)
    {
        throw SQLiteException(CPPSQLITE_ERROR, "Invalid field index requested");
    }

    return sqlite3_column_name(mpVM, nCol);
}

const char* SQLiteQuery::fieldDeclType(int nCol)
{
    checkVM();

    if (nCol < 0 || nCol > mnCols-1)
    {
        throw SQLiteException(CPPSQLITE_ERROR, "Invalid field index requested");
    }

    return sqlite3_column_decltype(mpVM, nCol);
}

int SQLiteQuery::fieldDataType(int nCol)
{
    checkVM();

    if (nCol < 0 || nCol > mnCols-1)
    {
        throw SQLiteException(CPPSQLITE_ERROR, "Invalid field index requested");
    }

    return sqlite3_column_type(mpVM, nCol);
}

bool SQLiteQuery::eof()
{
    checkVM();
    return mbEof;
}


void SQLiteQuery::nextRow()
{
    checkVM();

    int nRet = sqlite3_step(mpVM);

    if (nRet == SQLITE_DONE)
    {
        // no rows
        mbEof = true;
    }
    else if (nRet == SQLITE_ROW)
    {
        // more rows, nothing to do
    }
    else
    {
        nRet = sqlite3_finalize(mpVM);
        mpVM = 0;
        const char* szError = sqlite3_errmsg(mpDB);
        throw SQLiteException(nRet, szError);
    }
}

void SQLiteQuery::finalize()
{
    if (mpVM && mbOwnVM)
    {
        int nRet = sqlite3_finalize(mpVM);
        mpVM = 0;
        if (nRet != SQLITE_OK)
        {
            const char* szError = sqlite3_errmsg(mpDB);
            throw SQLiteException(nRet, szError);
        }
    }
}

void SQLiteQuery::checkVM()
{
    if (mpVM == 0)
    {
        throw SQLiteException(CPPSQLITE_ERROR, "Null Virtual Machine pointer");
    }
}

}
