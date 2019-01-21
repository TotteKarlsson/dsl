#pragma hdrstop
#include <iomanip>
#include <iostream>
//#include <cstring>
#include "sqlite/sqlite3.h"
#include "dslSQLiteTable.h"
#include "dslSQLiteException.h"
#include <map>
#include "dslStreamCenteredOutput.h"
//---------------------------------------------------------------------------
//
using namespace std;


namespace dsl
{

SQLiteTable::SQLiteTable(const SQLiteTable& rTable)
{
    mpaszResults = rTable.mpaszResults;
    // Only one object can own the results
    const_cast<SQLiteTable&>(rTable).mpaszResults = 0;
    mnRows = rTable.mnRows;
    mnCols = rTable.mnCols;
    mnCurrentRow = rTable.mnCurrentRow;
}

SQLiteTable::SQLiteTable(char** paszResults, int nRows, int nCols)
{
    mpaszResults = paszResults;
    mnRows = nRows;
    mnCols = nCols;
    mnCurrentRow = 0;
}

SQLiteTable::~SQLiteTable()
{
    try
    {
        finalize();
    }
    catch (...)
    {
    }
}

SQLiteTable& SQLiteTable::operator=(const SQLiteTable& rTable)
{
    try
    {
        finalize();
    }
    catch (...)
    {
    }
    mpaszResults = rTable.mpaszResults;
    // Only one object can own the results
    const_cast<SQLiteTable&>(rTable).mpaszResults = 0;
    mnRows = rTable.mnRows;
    mnCols = rTable.mnCols;
    mnCurrentRow = rTable.mnCurrentRow;
    return *this;
}

void SQLiteTable::finalize()
{
    if (mpaszResults)
    {
        sqlite3_free_table(mpaszResults);
        mpaszResults = 0;
    }
}

int SQLiteTable::numFields() const
{
    checkResults();
    return mnCols;
}

int SQLiteTable::nrCols() const
{
    checkResults();
    return mnCols;
}

int SQLiteTable::nrRows() const
{
    checkResults();
    return mnRows;
}

string SQLiteTable::asString(const char& del) const
{
    checkResults();
    stringstream tbl;

    //Precalculate width of columns
    map<int, int> colWidths;

    for(int c = 0; c < nrCols(); c++)
    {
        int maxColWidth = 0;
        for(int r = 0; r < nrRows(); r++)
        {
            setRow(r);
            string colVal = string(getStringField(c));
            if(colVal.size() >= maxColWidth)
            {
                colWidths[c] = colVal.size();
                maxColWidth  = colVal.size();
            }
        }
    }


    //Header
    for(int c = 0; c < nrCols(); c++)
    {
        if(string(fieldName(c)).size() > colWidths[c])
        {
            colWidths[c] = string(fieldName(c)).size() + 1;
        }

        if(c == 0)
        {
            tbl<<" "<< setw(colWidths[c])<<centered(string(fieldName(c)));
        }
        else
        {
            tbl<<" | " << setw(colWidths[c])<<centered(string(fieldName(c)))<<"";
        }

        if(c == nrCols() - 1)
        {
            tbl<<"\n";
        }
    }

    tbl<<setfill('-');
    for(int c = 0; c < nrCols(); c++)
    {

        tbl<<"-" << setw(colWidths[c])<<left<<centered("-")<<"-";
        if(c != nrCols() -1)
        {
            tbl<<"-";
        }
    }

    tbl<<"\n";

    tbl<<setfill(' ');
    //Values
    for(int r = 0; r < nrRows(); r++)
    {
        setRow(r);
        for(int c = 0; c < nrCols(); c++)
        {
            if(c == 0)
            {
                tbl<<" "<< setw(colWidths[c])<<left<<centered(string(getStringField(c)))<<" ";
            }
            else
            {
                tbl<<"| " << setw(colWidths[c])<<left<<centered(string(getStringField(c)))<<" ";
            }
            if(c == nrCols() - 1)
            {
                tbl<<"\n";
            }
        }
    }
    return tbl.str();
}

const char* SQLiteTable::fieldValue(int nField) const
{
    checkResults();

    if (nField < 0 || nField > mnCols-1)
    {
        throw SQLiteException(CPPSQLITE_ERROR, "Invalid field index requested");
    }

    int nIndex = (mnCurrentRow*mnCols) + mnCols + nField;
    return mpaszResults[nIndex];
}

const char* SQLiteTable::fieldValue(const char* szField) const
{
    checkResults();

    if (szField)
    {
        for (int nField = 0; nField < mnCols; nField++)
        {
            if (strcmp(szField, mpaszResults[nField]) == 0)
            {
                int nIndex = (mnCurrentRow*mnCols) + mnCols + nField;
                return mpaszResults[nIndex];
            }
        }
    }

    throw SQLiteException(CPPSQLITE_ERROR, "Invalid field name requested");
}

int SQLiteTable::getIntField(int nField, int nNullValue/*=0*/)
{
    if (fieldIsNull(nField))
    {
        return nNullValue;
    }
    else
    {
        return atoi(fieldValue(nField));
    }
}

int SQLiteTable::getIntField(const char* szField, int nNullValue/*=0*/)
{
    if (fieldIsNull(szField))
    {
        return nNullValue;
    }
    else
    {
        return atoi(fieldValue(szField));
    }
}

double SQLiteTable::getFloatField(int nField, double fNullValue/*=0.0*/)
{
    if (fieldIsNull(nField))
    {
        return fNullValue;
    }
    else
    {
        return atof(fieldValue(nField));
    }
}

double SQLiteTable::getFloatField(const char* szField, double fNullValue/*=0.0*/)
{
    if (fieldIsNull(szField))
    {
        return fNullValue;
    }
    else
    {
        return atof(fieldValue(szField));
    }
}

const char* SQLiteTable::getStringField(int nField, const char* szNullValue/*=""*/) const
{
    if (fieldIsNull(nField))
    {
        return szNullValue;
    }
    else
    {
        return fieldValue(nField);
    }
}

const char* SQLiteTable::getStringField(const char* szField, const char* szNullValue/*=""*/) const
{
    if (fieldIsNull(szField))
    {
        return szNullValue;
    }
    else
    {
        return fieldValue(szField);
    }
}

bool SQLiteTable::fieldIsNull(int nField) const
{
    checkResults();
    return (fieldValue(nField) == 0);
}

bool SQLiteTable::fieldIsNull(const char* szField) const
{
    checkResults();
    return (fieldValue(szField) == 0);
}

const char* SQLiteTable::fieldName(int nCol) const
{
    checkResults();

    if (nCol < 0 || nCol > mnCols-1)
    {
        throw SQLiteException(CPPSQLITE_ERROR, "Invalid field index requested");
    }

    return mpaszResults[nCol];
}

void SQLiteTable::setRow(int nRow) const
{
    checkResults();

    if (nRow < 0 || nRow > mnRows-1)
    {
        throw SQLiteException(CPPSQLITE_ERROR, "Invalid row index requested");
    }

    mnCurrentRow = nRow;
}

void SQLiteTable::checkResults() const
{
    if (mpaszResults == 0)
    {
        throw SQLiteException(CPPSQLITE_ERROR, "Null Results pointer");
    }
}

}
