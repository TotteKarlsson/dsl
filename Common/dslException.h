#ifndef dslExceptionH
#define dslExceptionH
#include "dslObject.h"
#include "dslCommonExporter.h"
#include <sstream>

//---------------------------------------------------------------------------

namespace dsl
{
using std::stringstream;
class DSL_COMMON DSLException : public std::exception, public DSLObject
{
    public:
                                            DSLException(const string& desc);
                                            DSLException(const stringstream& msg);
        virtual                             ~DSLException() throw();
        virtual const char*                 what() const throw();
        string                              Message() const;

    protected:
                                            //DSLException message
        string                              mMessage;
};

class DSL_COMMON DerivedDSLException : public DSLException
{
    public:
                                            DerivedDSLException(const string& msg);
};

}

#endif
