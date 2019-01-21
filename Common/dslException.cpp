#pragma hdrstop
#include "dslException.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
namespace dsl
{

DSLException::DSLException(const string& desc)
:
mMessage(desc)
{}

DSLException::DSLException(const stringstream& msg)
:
mMessage(msg.str())
{}

DSLException::~DSLException() throw()
{}


const char* DSLException::what() const throw()
{
    Log(lError) << mMessage;
    return mMessage.c_str();
}

string DSLException::Message() const
{
    return mMessage;
}

DerivedDSLException::DerivedDSLException(const string& msg)
:
DSLException(msg)
{}

}
