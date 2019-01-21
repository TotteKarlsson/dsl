
#pragma hdrstop
#include "sqlite/sqlite3.h"
#include "dslSQLiteBuffer.h"
//---------------------------------------------------------------------------
//

namespace dsl
{

SQLiteBuffer::SQLiteBuffer()
{
    mpBuf = 0;
}


SQLiteBuffer::~SQLiteBuffer()
{
    clear();
}


void SQLiteBuffer::clear()
{
    if (mpBuf)
    {
        sqlite3_free(mpBuf);
        mpBuf = 0;
    }

}


const char* SQLiteBuffer::format(const char* szFormat, ...)
{
    clear();
    va_list va;
    va_start(va, szFormat);
    mpBuf = sqlite3_vmprintf(szFormat, va);
    va_end(va);
    return mpBuf;
}

}
