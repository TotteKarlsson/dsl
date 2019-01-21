%module(docstring="Dune Scientific Library (dsl), (c) 1987-2018 Totte Karlsson",threads="1", directors="0" ) dsl

// ************************************************************
// Module Includes
// ************************************************************
// These are copied directly to the .cxx file and are not parsed
// by SWIG.  
%{
#include <string>
#include <iostream>
#include "dslObject.h"
#include "dslTypeInfo.h"
#include "dslProperties.h"
#include "dslProperty.h"
#include "dslBaseProperty.h"
#include "dslStringList.h"
#include "dslPlugin.h"
#include "dslPluginWithEvents.h"
#include "dslPythonPlugin.h"
#include "dslPluginMetaData.h"
#include "dslPluginmanager.h"
#include "dslPythonPluginManager.h"
#include "dslLogger.h"
#include "dslVersion.h"
#include "dslCommon.h"
#include "dslUtils.h"
using namespace dsl;
using namespace std;
%}
 
%include "std_string.i"
%include "std_vector.i"
%include "std_map.i"
%include "std_list.i"
%include "std_pair.i"
%include "std_set.i"
//%include "std_iostream.i"
//%include "std_sstream.i"
//%include "std_wsstream.i"
//%include "windows.i"
%include "cpointer.i"

%pythonprepend dsl::Properties::add(dsl::BaseProperty* o) %{
     o.thisown = 0
%}


%pythonprepend dsl::Plugin::addProperty(dsl::BaseProperty* p) %{
     p.thisown = 0
%}

#define DSL_COMMON
#define DSL_PLUGINS
#define DSL_PYTHONPLUGINS
#define Foundation_API

%ignore *::operator[];
%ignore *::operator=;
%ignore std::ostream;
%ignore operator<<;
%ignore operator int;
%ignore operator std::string;

%warnfilter(315) ostream; 
%warnfilter(315) stringstream; 


//We dont need these interfaces
%import "dslConstants.h"

%ignore getVersion;

//Expose these in Python
%include "dslObject.h"
%include "dslTypeInfo.h"
%include "dslBaseProperty.h"
%include "dslProperties.h"
%include "dslProperty.h"
%include "dslPluginMetaData.h"
%include "dslPlugin.h"
%include "dslPluginWithEvents.h"
%include "dslPluginManager.h"
%include "dslPythonPlugin.h"
%include "dslPythonPluginManager.h"
%include "dslUtils.h"
%include "dslCommon.h"

%template(intProperty)          dsl::Property<int>;
%template(floatProperty)        dsl::Property<double>;
%template(stringProperty)       dsl::Property<std::string>;

//The getVersion() function returns a Version object.
//Simplify for Python clients and just return a string
%rename("getVersion") _getVersion_Swig;

%inline %{
std::string _getVersion_Swig()
{
    Version v = getVersion();
    return v.asString();
}
%}

%extend dsl::Plugin {
%template(setPropertyValue) setPropertyValue<std::string>;
%template(setPropertyValue) setPropertyValue<int>;
%template(setPropertyValue) setPropertyValue<double>;

%template(getPropertyValueString)   getPropertyValue<std::string>;
%template(getPropertyValueInt)      getPropertyValue<int>;
%template(getPropertyValueFloat)   getPropertyValue<double>;
}

//Callbacks
%inline %{
void pluginEvent(void* a1 = NULL, void* a2 = NULL)
{
  printf("In on progress");
}

%}

%constant void pluginEvent(void*, void*);
