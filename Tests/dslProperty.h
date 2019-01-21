#ifndef dslPropertyH
#define dslPropertyH
#include <string>
#include "dslCommonExporter.h"
#include "dslBaseProperty.h"
//---------------------------------------------------------------------------

namespace dsl
{

using std::string;
using std::ostream;

template <class T>
class Property : public BaseProperty
{
    public:
                                                    Property(const T& value, const string& lbl = "");

                                                    ~Property(){}
        string                                      getLabel()                                  {return mKey;}


    protected:
        T                                           mDefaultValue;
        T                                           mDummyValue;
        T                                           mTemporaryValue;
        T*                                          mValue;
                                                    //Initially the mValue points to DummyValue
                                                    //However, the value can be set to point to
                                                    //another variable by using the function setReference
                                                    //and set back to setReferenceToDummy
};

template <class T>
Property<T>::Property(const T& value, const string& lbl)
:
BaseProperty(lbl)
{
    mDummyValue = value;
    mValue = &mDummyValue;
}

}
#endif

