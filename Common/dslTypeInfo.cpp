#pragma hdrstop
#include "dslTypeInfo.h"
//---------------------------------------------------------------------------

namespace dsl
{

string toString(ObjectType val)
{
    switch(val)
    {
        case otBool:
            return "bool";
        break;
        case otUnsignedInt:
            return "unsignedInt";
        break;
        case otInt:
            return "int";
        break;
        case otDouble:
            return "double";
        break;
        case otStdString:
            return "string";
        break;
        case otChar:
            return "char";
        break;
        case otStringList:
            return "stringList";
        break;
        case otPoint:
            return "point";
        break;
        case otColor:
            return "color";
        break;
        case otAmazonQuery:
            return "amazonQuery";
        break;
        case otAmazonCredentials:
            return "amazonCredentials";
        break;
        case otLogLevel:
            return "logLevel";
        break;
        case otUndefined:
            return "undefined";
        break;
        default:
            return "????";
    }
}
}
