#ifndef dslNameValueH
#define dslNameValueH
#include "dslObject.h"
#include "dslException.h"
#include "dslStringUtils.h"
#include "dslStringList.h"
//---------------------------------------------------------------------------
namespace dsl
{

template<class T>
class DSL_COMMON NameValue : public DSLObject
{

        public:
                            NameValue(const string& str, char delimiter = '=');

            T               getValue();
            void            setValue(const T& val){mValue = val;}



        private:
            string          mName;
            T               mValue;

};



template<class T>
NameValue<T>::NameValue(const string& str, char delimiter)
{
    StringList nv(str, delimiter);
    if(nv.count() != 2)
    {
        throw(DSLException("Bad Name Value pair"));
    }
    mName = nv[0];
    mValue = T(nv[1]);
}

template<>
NameValue<int>::NameValue(const string& str, char delimiter)
{
    StringList nv(str, delimiter);
    if(nv.count() != 2)
    {
        throw(DSLException("Bad Name Value pair"));
    }
    mName = nv[0];
    mValue = toInt(nv[1]);
}

template<>
int NameValue<int>::getValue()
{
	return mValue;
}
}
#endif
