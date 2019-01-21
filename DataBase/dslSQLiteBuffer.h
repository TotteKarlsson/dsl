#ifndef dslSQLiteBufferH
#define dslSQLiteBufferH
#include "dslObject.h"
#include "DataBaseExporter.h"
//---------------------------------------------------------------------------

namespace dsl
{

class DSL_DB SQLiteBuffer : public DSLObject
{
    public:
                            SQLiteBuffer();
                           ~SQLiteBuffer();
		const char*             format(const char* szFormat, ...);
		operator const char*() { return mpBuf; }
		void                     clear();

	private:
		char*                     mpBuf;
};

}

#endif

////class CppSQLite3Buffer
////{
////public:
////
////    CppSQLite3Buffer();
////
////    ~CppSQLite3Buffer();
////
////    const char* format(const char* szFormat, ...);
////
////    operator const char*() { return mpBuf; }
////
////    void clear();
////
////private:
////
////    char* mpBuf;
////};
