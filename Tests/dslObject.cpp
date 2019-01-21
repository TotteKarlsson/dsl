#pragma hdrstop
#include "dslObject.h"
//---------------------------------------------------------------------------
namespace dsl
{

DSLObject::DSLObject()
{}

DSLObject::DSLObject(const DSLObject& /*obj*/)
{}

DSLObject::~DSLObject()
{}


string DSLObject::getTypeName() const
{
    return "DSLObject";
}

string DSLObject::asString(const char& delimiter) const
{
    return "Implement asString(const char delimiter) function in derived class!";
}

const char* DSLObject::c_str() const
{
    return "Implement const char* asCString(const char delimiter) function in derived class!";
}

}
