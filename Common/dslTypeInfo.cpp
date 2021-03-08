#pragma hdrstop
#include "dslTypeInfo.h"
//---------------------------------------------------------------------------

namespace dsl
{

string toString(ObjectType val)
{
    switch(val)
    {
        case otBool:                return "bool";
        case otUnsignedInt:         return "unsignedInt";
        case otInt:                 return "int";
        case otDouble:              return "double";
        case otStdString:           return "string";
        case otPairOfInts:          return "pairOfInts";
        case otChar:                return "char";
        case otStringList:          return "stringList";
        case otPoint:               return "point";
        case otColor:               return "color";
        case otAmazonQuery:         return "amazonQuery";
        case otAmazonCredentials:	return "amazonCredentials";
        case otLogLevel:        	return "logLevel";
        case otUndefined:           return "undefined";
        default:               		return "????";
    }
}
}
