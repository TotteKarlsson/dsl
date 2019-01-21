#pragma hdrstop
#include "dslCompareStrings.h"
//---------------------------------------------------------------------------

namespace dsl
{

CompareStrings::CompareStrings(const std::string& n)
:
name(n)
{}

CompareStrings::CompareStrings(const char* s)
: name(s)
{}

bool CompareStrings::operator () (const string& obj) const
{
    return obj == name;
}
}
