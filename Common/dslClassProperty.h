#ifndef dslClassPropertyH
#define dslClassPropertyH
#include "dslProperty.h"
//---------------------------------------------------------------------------

namespace dsl
{

//Define a property of type T with a class of type C
//A class using this pattern need to implement get and set functions
//and initialize the property in its constructor

template<class T, class C>
class ClassProperty
{
    //Typedef function pointers Get and Set
    typedef T       (C::*Get)() const;
    typedef void    (C::*Set)(T);
    typedef void    (C::*SetFromConst)(const T&);

    public:
                                ClassProperty(Get get, Set set, C& h);
                                ClassProperty(Get get, SetFromConst set, C& h);
                                operator T() const;
        void                    operator=(T value);
//        void                    operator=(const T& value);

    private:
        C&                      mH;
        Get                     mGet;
        Set                     mSet;
        T                       mValue;
};

//Think about away to use internal value for this class..

template<class T, class C>
ClassProperty<T, C>::ClassProperty(Get get, Set set, C& h)
:
mH(h),
mGet(get),
mSet(set)
{}

template<class T, class C>
void ClassProperty<T, C>::operator =(T value)
{
    (mH.*mSet)(value);
    mValue = value;
}

//template<class T, class C>
//void ClassProperty<T, C>::operator =(const T& value)
//{
//    (mH.*mSet)(value);
//    mValue = value;
//}

template<class T, class C>
ClassProperty<T, C>::operator T() const
{
//    return mValue;
    return (mH.*mGet)();
}

}
#endif
