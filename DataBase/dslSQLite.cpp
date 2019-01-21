#pragma hdrstop
#include <string.h>
#include "sqlite/sqlite3.h"
#include "dslSQLite.h"
#include "dslSQLiteException.h"
#include "dslSQLiteTable.h"
#include "dslSQLiteQuery.h"
#include "dslSQLiteStatement.h"
#include "dslSQLiteBuffer.h"
#include "dslLogger.h"
#include "dslFileUtils.h"
//---------------------------------------------------------------------------
namespace dsl
{

const char*     SQLite::version()                { return SQLITE_VERSION; }
const char*     SQLite::libraryVersion()         { return sqlite3_libversion(); }
int             SQLite::libraryVersionNumber()   { return sqlite3_libversion_number(); }

SQLite::SQLite(const string& db, bool autoOpen)
:
mDB(nullptr)
{
    if(autoOpen && db.size())
    {
        open(db);
    }
}

SQLite::~SQLite()
{
    try
    {
        close();
    }
    catch (...)
    {
        //throw("Bad..");
    }
}

sqlite3* SQLite::getHandle()
{
    return mDB;
}

bool SQLite::isOpen()
{
    return mDB ? true : false;
}

void SQLite::checkDB()
{
    if (!mDB)
    {
        throw SQLiteException(CPPSQLITE_ERROR, (char*) "Database is not open", DONT_DELETE_MSG);
    }
}

void SQLite::interrupt()
{
    sqlite3_interrupt(mDB);
}

bool SQLite::open(const string& db, bool autoCreate)
{
    if(!db.size())
    {
        Log(lDebug) << "Empty database name passed to open database call";
        return false;
    }

    mDBName = db;

    if(isOpen())
    {
        close();
    }

    if(autoCreate == false && !fileExists(db))
    {
        Log(lError) << "Database: "<<db<<" don't exist.";
        return false;
    }
    int openRes = sqlite3_open(db.c_str(), &mDB);
    if(openRes != SQLITE_OK)
    {
        //Set error
        mLastError = sqlite3_errmsg(mDB);
        sqlite3_close(mDB);
        mDB = nullptr;
        return false;
    }
    return true;
}

bool SQLite::close()
{
    if(!mDB)
    {
        return true;
    }

    int result = sqlite3_close(mDB);
    if(result != SQLITE_OK)
    {
        //Set error
        mLastError = sqlite3_errmsg(mDB);
    }
    else
    {
        mDB = nullptr;
    }
    Log(lDebug) << "The database: "<<mDBName<<" was closed";
    return true;
}

SQLiteTable SQLite::getTable(const string& szSQL)
{
    checkDB();

    char* szError=0;
    char** paszResults=0;
    int nRet;
    int nRows(0);
    int nCols(0);

    nRet = sqlite3_get_table(mDB, szSQL.c_str(), &paszResults, &nRows, &nCols, &szError);

    if (nRet == SQLITE_OK)
    {
        return SQLiteTable(paszResults, nRows, nCols);
    }
    else
    {
        throw SQLiteException(nRet, szError);
    }
}

////CppSQLite3Exception::CppSQLite3Exception(const int nErrCode,
////                                    char* szErrMess,
////                                    bool bDeleteMsg/*=true*/) :
////                                    mnErrCode(nErrCode)
////{
////    mpszErrMess = sqlite3_mprintf("%s[%d]: %s",
////                                errorCodeAsString(nErrCode),
////                                nErrCode,
////                                szErrMess ? szErrMess : "");
////
////    if (bDeleteMsg && szErrMess)
////    {
////        sqlite3_free(szErrMess);
////    }
////}
////
////
////CppSQLite3Exception::CppSQLite3Exception(const CppSQLite3Exception&  e) :
////                                    mnErrCode(e.mnErrCode)
////{
////    mpszErrMess = 0;
////    if (e.mpszErrMess)
////    {
////        mpszErrMess = sqlite3_mprintf("%s", e.mpszErrMess);
////    }
////}
////
////
////const char* CppSQLite3Exception::errorCodeAsString(int nErrCode)
////{
////    switch (nErrCode)
////    {
////        case SQLITE_OK          : return "SQLITE_OK";
////        case SQLITE_ERROR       : return "SQLITE_ERROR";
////        case SQLITE_INTERNAL    : return "SQLITE_INTERNAL";
////        case SQLITE_PERM        : return "SQLITE_PERM";
////        case SQLITE_ABORT       : return "SQLITE_ABORT";
////        case SQLITE_BUSY        : return "SQLITE_BUSY";
////        case SQLITE_LOCKED      : return "SQLITE_LOCKED";
////        case SQLITE_NOMEM       : return "SQLITE_NOMEM";
////        case SQLITE_READONLY    : return "SQLITE_READONLY";
////        case SQLITE_INTERRUPT   : return "SQLITE_INTERRUPT";
////        case SQLITE_IOERR       : return "SQLITE_IOERR";
////        case SQLITE_CORRUPT     : return "SQLITE_CORRUPT";
////        case SQLITE_NOTFOUND    : return "SQLITE_NOTFOUND";
////        case SQLITE_FULL        : return "SQLITE_FULL";
////        case SQLITE_CANTOPEN    : return "SQLITE_CANTOPEN";
////        case SQLITE_PROTOCOL    : return "SQLITE_PROTOCOL";
////        case SQLITE_EMPTY       : return "SQLITE_EMPTY";
////        case SQLITE_SCHEMA      : return "SQLITE_SCHEMA";
////        case SQLITE_TOOBIG      : return "SQLITE_TOOBIG";
////        case SQLITE_CONSTRAINT  : return "SQLITE_CONSTRAINT";
////        case SQLITE_MISMATCH    : return "SQLITE_MISMATCH";
////        case SQLITE_MISUSE      : return "SQLITE_MISUSE";
////        case SQLITE_NOLFS       : return "SQLITE_NOLFS";
////        case SQLITE_AUTH        : return "SQLITE_AUTH";
////        case SQLITE_FORMAT      : return "SQLITE_FORMAT";
////        case SQLITE_RANGE       : return "SQLITE_RANGE";
////        case SQLITE_ROW         : return "SQLITE_ROW";
////        case SQLITE_DONE        : return "SQLITE_DONE";
////        case CPPSQLITE_ERROR    : return "CPPSQLITE_ERROR";
////        default: return "UNKNOWN_ERROR";
////    }
////}
////
////
////CppSQLite3Exception::~CppSQLite3Exception()
////{
////    if (mpszErrMess)
////    {
////        sqlite3_free(mpszErrMess);
////        mpszErrMess = 0;
////    }
////}
////
////
SQLiteTable::SQLiteTable()
{
    mpaszResults = 0;
    mnRows = 0;
    mnCols = 0;
    mnCurrentRow = 0;
}
////
////
////CppSQLite3Table::CppSQLite3Table(const CppSQLite3Table& rTable)
////{
////    mpaszResults = rTable.mpaszResults;
////    // Only one object can own the results
////    const_cast<CppSQLite3Table&>(rTable).mpaszResults = 0;
////    mnRows = rTable.mnRows;
////    mnCols = rTable.mnCols;
////    mnCurrentRow = rTable.mnCurrentRow;
////}
////
////
////CppSQLite3Table::CppSQLite3Table(char** paszResults, int nRows, int nCols)
////{
////    mpaszResults = paszResults;
////    mnRows = nRows;
////    mnCols = nCols;
////    mnCurrentRow = 0;
////}
////
////
////CppSQLite3Table::~CppSQLite3Table()
////{
////    try
////    {
////        finalize();
////    }
////    catch (...)
////    {
////    }
////}
////
////
////CppSQLite3Table& CppSQLite3Table::operator=(const CppSQLite3Table& rTable)
////{
////    try
////    {
////        finalize();
////    }
////    catch (...)
////    {
////    }
////    mpaszResults = rTable.mpaszResults;
////    // Only one object can own the results
////    const_cast<CppSQLite3Table&>(rTable).mpaszResults = 0;
////    mnRows = rTable.mnRows;
////    mnCols = rTable.mnCols;
////    mnCurrentRow = rTable.mnCurrentRow;
////    return *this;
////}
////
////
////void CppSQLite3Table::finalize()
////{
////    if (mpaszResults)
////    {
////        sqlite3_free_table(mpaszResults);
////        mpaszResults = 0;
////    }
////}
////
////
////int CppSQLite3Table::numFields()
////{
////    checkResults();
////    return mnCols;
////}
////
////
////int CppSQLite3Table::numRows()
////{
////    checkResults();
////    return mnRows;
////}
////
////
////const char* CppSQLite3Table::fieldValue(int nField)
////{
////    checkResults();
////
////    if (nField < 0 || nField > mnCols-1)
////    {
////        throw CppSQLite3Exception(CPPSQLITE_ERROR,
////                                "Invalid field index requested",
////                                DONT_DELETE_MSG);
////    }
////
////    int nIndex = (mnCurrentRow*mnCols) + mnCols + nField;
////    return mpaszResults[nIndex];
////}
////
////
////const char* CppSQLite3Table::fieldValue(const char* szField)
////{
////    checkResults();
////
////    if (szField)
////    {
////        for (int nField = 0; nField < mnCols; nField++)
////        {
////            if (strcmp(szField, mpaszResults[nField]) == 0)
////            {
////                int nIndex = (mnCurrentRow*mnCols) + mnCols + nField;
////                return mpaszResults[nIndex];
////            }
////        }
////    }
////
////    throw CppSQLite3Exception(CPPSQLITE_ERROR,
////                            "Invalid field name requested",
////                            DONT_DELETE_MSG);
////}
////
////
////int CppSQLite3Table::getIntField(int nField, int nNullValue/*=0*/)
////{
////    if (fieldIsNull(nField))
////    {
////        return nNullValue;
////    }
////    else
////    {
////        return atoi(fieldValue(nField));
////    }
////}
////
////
////int CppSQLite3Table::getIntField(const char* szField, int nNullValue/*=0*/)
////{
////    if (fieldIsNull(szField))
////    {
////        return nNullValue;
////    }
////    else
////    {
////        return atoi(fieldValue(szField));
////    }
////}
////
////
////double CppSQLite3Table::getFloatField(int nField, double fNullValue/*=0.0*/)
////{
////    if (fieldIsNull(nField))
////    {
////        return fNullValue;
////    }
////    else
////    {
////        return atof(fieldValue(nField));
////    }
////}
////
////
////double CppSQLite3Table::getFloatField(const char* szField, double fNullValue/*=0.0*/)
////{
////    if (fieldIsNull(szField))
////    {
////        return fNullValue;
////    }
////    else
////    {
////        return atof(fieldValue(szField));
////    }
////}
////
////
////const char* CppSQLite3Table::getStringField(int nField, const char* szNullValue/*=""*/)
////{
////    if (fieldIsNull(nField))
////    {
////        return szNullValue;
////    }
////    else
////    {
////        return fieldValue(nField);
////    }
////}
////
////
////const char* CppSQLite3Table::getStringField(const char* szField, const char* szNullValue/*=""*/)
////{
////    if (fieldIsNull(szField))
////    {
////        return szNullValue;
////    }
////    else
////    {
////        return fieldValue(szField);
////    }
////}
////
////
////bool CppSQLite3Table::fieldIsNull(int nField)
////{
////    checkResults();
////    return (fieldValue(nField) == 0);
////}
////
////
////bool CppSQLite3Table::fieldIsNull(const char* szField)
////{
////    checkResults();
////    return (fieldValue(szField) == 0);
////}
////
////
////const char* CppSQLite3Table::fieldName(int nCol)
////{
////    checkResults();
////
////    if (nCol < 0 || nCol > mnCols-1)
////    {
////        throw CppSQLite3Exception(CPPSQLITE_ERROR,
////                                "Invalid field index requested",
////                                DONT_DELETE_MSG);
////    }
////
////    return mpaszResults[nCol];
////}
////
////
////void CppSQLite3Table::setRow(int nRow)
////{
////    checkResults();
////
////    if (nRow < 0 || nRow > mnRows-1)
////    {
////        throw CppSQLite3Exception(CPPSQLITE_ERROR,
////                                "Invalid row index requested",
////                                DONT_DELETE_MSG);
////    }
////
////    mnCurrentRow = nRow;
////}
////
////
////void CppSQLite3Table::checkResults()
////{
////    if (mpaszResults == 0)
////    {
////        throw CppSQLite3Exception(CPPSQLITE_ERROR,
////                                "Null Results pointer",
////                                DONT_DELETE_MSG);
////    }
////}
////
////
////////////////////////////////////////////////////////////////////////////////////
////
////CppSQLite3Statement::CppSQLite3Statement()
////{
////    mpDB = 0;
////    mpVM = 0;
////}
////
////
////CppSQLite3Statement::CppSQLite3Statement(const CppSQLite3Statement& rStatement)
////{
////    mpDB = rStatement.mpDB;
////    mpVM = rStatement.mpVM;
////    // Only one object can own VM
////    const_cast<CppSQLite3Statement&>(rStatement).mpVM = 0;
////}
////
////
////CppSQLite3Statement::CppSQLite3Statement(sqlite3* pDB, sqlite3_stmt* pVM)
////{
////    mpDB = pDB;
////    mpVM = pVM;
////}
////
////
////CppSQLite3Statement::~CppSQLite3Statement()
////{
////    try
////    {
////        finalize();
////    }
////    catch (...)
////    {
////    }
////}
////
////
////CppSQLite3Statement& CppSQLite3Statement::operator=(const CppSQLite3Statement& rStatement)
////{
////    mpDB = rStatement.mpDB;
////    mpVM = rStatement.mpVM;
////    // Only one object can own VM
////    const_cast<CppSQLite3Statement&>(rStatement).mpVM = 0;
////    return *this;
////}
int SQLiteStatement::execDML()
{
    checkDB();
    checkVM();

    const char* szError=0;

    int nRet = sqlite3_step(mpVM);

    if (nRet == SQLITE_DONE)
    {
        int nRowsChanged = sqlite3_changes(mpDB);

        nRet = sqlite3_reset(mpVM);

        if (nRet != SQLITE_OK)
        {
            szError = sqlite3_errmsg(mpDB);
            throw SQLiteException(nRet, (char*)szError, DONT_DELETE_MSG);
        }

        return nRowsChanged;
    }
    else
    {
        nRet = sqlite3_reset(mpVM);
        szError = sqlite3_errmsg(mpDB);
        throw SQLiteException(nRet, (char*)szError, DONT_DELETE_MSG);
    }
}


////
////
////////////////////////////////////////////////////////////////////////////////////
////
////CppSQLite3DB::CppSQLite3DB()
////{
////    mpDB = 0;
////    mnBusyTimeoutMs = 60000; // 60 seconds
////}
////
////
////CppSQLite3DB::CppSQLite3DB(const CppSQLite3DB& db)
////{
////    mpDB = db.mpDB;
////    mnBusyTimeoutMs = 60000; // 60 seconds
////}
////
////
////CppSQLite3DB::~CppSQLite3DB()
////{
////    try
////    {
////        close();
////    }
////    catch (...)
////    {
////    }
////}
////
////
////CppSQLite3DB& CppSQLite3DB::operator=(const CppSQLite3DB& db)
////{
////    mpDB = db.mpDB;
////    mnBusyTimeoutMs = 60000; // 60 seconds
////    return *this;
////}
////
////
////void CppSQLite3DB::open(const char* szFile)
////{
////    int nRet = sqlite3_open(szFile, &mpDB);
////
////    if (nRet != SQLITE_OK)
////    {
////        const char* szError = sqlite3_errmsg(mpDB);
////        throw CppSQLite3Exception(nRet, (char*)szError, DONT_DELETE_MSG);
////    }
////
////    setBusyTimeout(mnBusyTimeoutMs);
////}
////
////
////void CppSQLite3DB::close()
////{
////    if (mpDB)
////    {
////        if (sqlite3_close(mpDB) == SQLITE_OK)
////        {
////            mpDB = 0;
////        }
////        else
////        {
////            throw CppSQLite3Exception(CPPSQLITE_ERROR,
////                                    "Unable to close database",
////                                    DONT_DELETE_MSG);
////        }
////    }
////}
////
////
////CppSQLite3Statement CppSQLite3DB::compileStatement(const char* szSQL)
////{
////    checkDB();
////
////    sqlite3_stmt* pVM = compile(szSQL);
////    return CppSQLite3Statement(mpDB, pVM);
////}
////
////
bool SQLite::tableExists(const string& szTable)
{
    char szSQL[256];
    sprintf(szSQL,
            "select count(*) from sqlite_master where type='table' and name='%s'",
            szTable.c_str());
    int nRet = execScalar(szSQL);
    return (nRet > 0);
}

int SQLite::execDML(const char* szSQL)
{
    checkDB();
    char* szError=0;

    int nRet = sqlite3_exec(mDB, szSQL, 0, 0, &szError);

    if (nRet == SQLITE_OK)
    {
        return sqlite3_changes(mDB);
    }
    else
    {
        throw SQLiteException(nRet, szError);
    }
}

SQLiteQuery SQLite::execQuery(const char* szSQL)
{
    checkDB();

    sqlite3_stmt* pVM = compile(szSQL);

    int nRet = sqlite3_step(pVM);

    if (nRet == SQLITE_DONE)
    {
        // no rows
        return SQLiteQuery(mDB, pVM, true/*eof*/);
    }
    else if (nRet == SQLITE_ROW)
    {
        // at least 1 row
        return SQLiteQuery(mDB, pVM, false/*eof*/);
    }
    else
    {
        nRet = sqlite3_finalize(pVM);
        const char* szError= sqlite3_errmsg(mDB);
        throw SQLiteException(nRet, (char*)szError, DONT_DELETE_MSG);
    }
}

int SQLite::execScalar(const char* szSQL, int nNullValue/*=0*/)
{
    //SQLite
    SQLiteQuery q = execQuery(szSQL);

    if (q.eof() || q.numFields() < 1)
    {
        throw SQLiteException(CPPSQLITE_ERROR, "Invalid scalar query");
    }

    return q.getIntField(0, nNullValue);
}

string SQLite::execString(const string& szSQL, const string& nNullValue)
{
    //SQLite
    SQLiteQuery q = execQuery(szSQL.c_str());

    if (q.eof() || q.numFields() < 1)
    {
        throw SQLiteException(CPPSQLITE_ERROR, "Invalid scalar query");
    }

    return q.getStringField(0, nNullValue.c_str());
}


////
////
////sqlite_int64 CppSQLite3DB::lastRowId()
////{
////    return sqlite3_last_insert_rowid(mpDB);
////}
////
////
////void CppSQLite3DB::setBusyTimeout(int nMillisecs)
////{
////    mnBusyTimeoutMs = nMillisecs;
////    sqlite3_busy_timeout(mpDB, mnBusyTimeoutMs);
////}
////
////
////void CppSQLite3DB::checkDB()
////{
////    if (!mpDB)
////    {
////        throw CppSQLite3Exception(CPPSQLITE_ERROR,
////                                "Database not open",
////                                DONT_DELETE_MSG);
////    }
////}
////
////

sqlite3_stmt* SQLite::compile(const char* szSQL)
{
    checkDB();

    const char* szTail=0;
    sqlite3_stmt* pVM;

    int nRet = sqlite3_prepare_v2(mDB, szSQL, -1, &pVM, &szTail);

    if (nRet != SQLITE_OK)
    {
        const char* szError = sqlite3_errmsg(mDB);
        stringstream msg;
        msg<<"In SQL: "<<szSQL<<". DBError: "<<szError;

        throw SQLiteException(nRet, msg.str().c_str() );
    }

    return pVM;
}

bool SQLite::isAutoCommitOn()
{
    checkDB();
    return sqlite3_get_autocommit(mDB) ? true : false;
}

////////////////////////////////////////////////////////////////////////////////////
////// SQLite encode.c reproduced here, containing implementation notes and source
////// for sqlite3_encode_binary() and sqlite3_decode_binary()
////////////////////////////////////////////////////////////////////////////////////
////
/////*
////** 2002 April 25
////**
////** The author disclaims copyright to this source code.  In place of
////** a legal notice, here is a blessing:
////**
////**    May you do good and not evil.
////**    May you find forgiveness for yourself and forgive others.
////**    May you share freely, never taking more than you give.
////**
////*************************************************************************
////** This file contains helper routines used to translate binary data into
////** a null-terminated string (suitable for use in SQLite) and back again.
////** These are convenience routines for use by people who want to store binary
////** data in an SQLite database.  The code in this file is not used by any other
////** part of the SQLite library.
////**
////** $Id: encode.c,v 1.10 2004/01/14 21:59:23 drh Exp $
////*/
////
/////*
////

int sqlite3_encode_binary(const unsigned char *in, int n, unsigned char *out)
{
  int i, j, e, m;
  int cnt[256];
  if( n<=0 ){
    out[0] = 'x';
    out[1] = 0;
    return 1;
  }
  memset(cnt, 0, sizeof(cnt));
  for(i=n-1; i>=0; i--){ cnt[in[i]]++; }
  m = n;
  for(i=1; i<256; i++){
    int sum;
    if( i=='\'' ) continue;
    sum = cnt[i] + cnt[(i+1)&0xff] + cnt[(i+'\'')&0xff];
    if( sum<m ){
      m = sum;
      e = i;
      if( m==0 ) break;
    }
  }
  out[0] = e;
  j = 1;
  for(i=0; i<n; i++){
    int c = (in[i] - e)&0xff;
    if( c==0 ){
      out[j++] = 1;
      out[j++] = 1;
    }else if( c==1 ){
      out[j++] = 1;
      out[j++] = 2;
    }else if( c=='\'' ){
      out[j++] = 1;
      out[j++] = 3;
    }else{
      out[j++] = c;
    }
  }
  out[j] = 0;
  return j;
}

/*
** Decode the string "in" into binary data and write it into "out".
** This routine reverses the encoding created by sqlite3_encode_binary().
** The output will always be a few bytes less than the input.  The number
** of bytes of output is returned.  If the input is not a well-formed
** encoding, -1 is returned.
**
** The "in" and "out" parameters may point to the same buffer in order
** to decode a string in place.
*/
int sqlite3_decode_binary(const unsigned char *in, unsigned char *out)
{
    int e = *(in++);
    int i = 0;
    int c;
    while( (c = *(in++)) != 0 )
    {
        if(c == 1)
        {
            c = *(in++);
            if(c == 1)
            {
                c = 0;
            }
            else if(c == 2)
            {
                c = 1;
            }
            else if(c == 3)
            {
                c = '\'';
            }
            else
            {
                return -1;
            }
        }
        out[i++] = (c + e)&0xff;
    }
    return i;
}

} //Namespace
