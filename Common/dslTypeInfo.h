#ifndef dslTypeInfoH
#define dslTypeInfoH
#include "dslCommonExporter.h"
#include <string>

namespace dsl
{

using std::string;

//---------------------------------------------------------------------------
enum ObjectType
{
	otBool=0,
	otUnsignedInt,
    otInt,
    otDouble,
    otStdString,
    otChar,
    otStringList,
    otPoint,
    otColor,
    otAmazonQuery,
    otAmazonCredentials,
    otLogLevel,
    otUndefined
};


template <class T>
ObjectType getType(const T& val);

template <class T>
string getTypeAsString(const T& val);

DSL_COMMON string toString(ObjectType val);


}
#endif
