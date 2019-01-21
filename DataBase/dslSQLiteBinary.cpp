#pragma hdrstop
#include <cstdlib>
#include "sqlite/sqlite3.h"
#include "dslSQLiteException.h"
#include "dslSQLiteBinary.h"
//---------------------------------------------------------------------------
//
using namespace std;
namespace dsl
{

SQLiteBinary::SQLiteBinary() :
                        mpBuf(0),
                        mnBinaryLen(0),
                        mnBufferLen(0),
                        mnEncodedLen(0),
                        mbEncoded(false)
{
}


SQLiteBinary::~SQLiteBinary()
{
    clear();
}


void SQLiteBinary::setBinary(const unsigned char* pBuf, int nLen)
{
    mpBuf = allocBuffer(nLen);
    memcpy(mpBuf, pBuf, nLen);
}


void SQLiteBinary::setEncoded(const unsigned char* pBuf)
{
    clear();

    mnEncodedLen = strlen((const char*)pBuf);
    mnBufferLen = mnEncodedLen + 1; // Allow for nullptr terminator

    mpBuf = (unsigned char*)malloc(mnBufferLen);

    if (!mpBuf)
    {
        throw SQLiteException(CPPSQLITE_ERROR, "Cannot allocate memory");
    }

    memcpy(mpBuf, pBuf, mnBufferLen);
    mbEncoded = true;
}


const unsigned char* SQLiteBinary::getEncoded()
{
    if (!mbEncoded)
    {
        unsigned char* ptmp = (unsigned char*)malloc(mnBinaryLen);
        memcpy(ptmp, mpBuf, mnBinaryLen);
        mnEncodedLen = sqlite3_encode_binary(ptmp, mnBinaryLen, mpBuf);
        free(ptmp);
        mbEncoded = true;
    }

    return mpBuf;
}


const unsigned char* SQLiteBinary::getBinary()
{
    if (mbEncoded)
    {
        // in/out buffers can be the same
        mnBinaryLen = sqlite3_decode_binary(mpBuf, mpBuf);

        if (mnBinaryLen == -1)
        {
            throw SQLiteException(CPPSQLITE_ERROR, "Cannot decode binary");
        }

        mbEncoded = false;
    }

    return mpBuf;
}

int SQLiteBinary::getBinaryLength()
{
    getBinary();
    return mnBinaryLen;
}

unsigned char* SQLiteBinary::allocBuffer(int nLen)
{
    clear();

    // Allow extra space for encoded binary as per comments in
    // SQLite encode.c See bottom of this file for implementation
    // of SQLite functions use 3 instead of 2 just to be sure ;-)
    mnBinaryLen = nLen;
    mnBufferLen = 3 + (257*nLen)/254;

    mpBuf = (unsigned char*)malloc(mnBufferLen);

    if (!mpBuf)
    {
        throw SQLiteException(CPPSQLITE_ERROR, "Cannot allocate memory");
    }

    mbEncoded = false;
    return mpBuf;
}

void SQLiteBinary::clear()
{
    if (mpBuf)
    {
        mnBinaryLen = 0;
        mnBufferLen = 0;
        free(mpBuf);
        mpBuf = 0;
    }
}

}
