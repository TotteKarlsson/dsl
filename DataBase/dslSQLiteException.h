#ifndef dslSQLiteExceptionH
#define dslSQLiteExceptionH
#include "DataBaseExporter.h"
#include "dslException.h"
#include "dslObject.h"
//---------------------------------------------------------------------------

namespace dsl
{

class DSL_DB SQLiteException : public DSLException
{
    public:
                                SQLiteException(const int nErrCode, const char* szErrMess);
                                SQLiteException(const int nErrCode, char* szErrMess, bool bDeleteMsg = true);
                                SQLiteException(const SQLiteException&  e);
        virtual                ~SQLiteException() throw();
        const int               errorCode() const;
        const char*             errorMessage() const;
		const char*             errorCodeAsString(int nErrCode) const;

	private:
        int                     mnErrCode;
        char*                   mpszErrMess;
};

}
#endif