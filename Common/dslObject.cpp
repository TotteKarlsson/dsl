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
    return "Implement asString(const char delimiter) function in derived class \"" + this->getTypeName() + "\"";
}

const char* DSLObject::c_str() const
{
    return string("Implement c_str() function in derived class \"" + this->getTypeName() + "\"").c_str();
}

}
