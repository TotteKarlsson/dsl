#pragma hdrstop
#include "dslPluginInformation.h"
//---------------------------------------------------------------------------
namespace dsl
{
PluginInformation::PluginInformation()
:
Name(&PluginInformation::getName, &PluginInformation::setName, *this)
//LibraryName
//Author;
//Category;
//Description
//Hint;
//Version;
//Copyright;
{
}


}
