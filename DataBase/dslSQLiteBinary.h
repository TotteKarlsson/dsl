#ifndef dslSQLiteBinaryH
#define dslSQLiteBinaryH
#include "DataBaseExporter.h"
#include "dslObject.h"
//---------------------------------------------------------------------------

namespace dsl
{
class DSL_DB SQLiteBinary : public DSLObject
{
    public:
                                SQLiteBinary();
                               ~SQLiteBinary();
        void                    setBinary(const unsigned char* pBuf, int nLen);
        void                    setEncoded(const unsigned char* pBuf);
        const unsigned char*     getEncoded();
        const unsigned char*     getBinary();
        int                     getBinaryLength();
        unsigned char*             allocBuffer(int nLen);
        void                     clear();
		
    private:
        unsigned char*                mpBuf;
        int                     mnBinaryLen;
        int                     mnBufferLen;
        int                     mnEncodedLen;
        bool                    mbEncoded;
};
}

#endif

