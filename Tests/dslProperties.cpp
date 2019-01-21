#pragma hdrstop
#include <sstream>
#include <iomanip>
#include "dslProperties.h"
//---------------------------------------------------------------------------

namespace dsl
{


Properties::Properties(const string& regSubSection)
:
mSection(regSubSection)
{}

Properties::~Properties()
{
    mProperties.clear();
}


BaseProperty* Properties::getProperty(int index)
{
	return mProperties[index];
}

void Properties::add(BaseProperty* para)
{
    mProperties.push_back(para);
}

}

