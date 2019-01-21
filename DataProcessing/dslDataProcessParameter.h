#ifndef dslDataProcessParameterH
#define dslDataProcessParameterH
#include <string>
#include "dslObject.h"
#include "DataExporter.h"

namespace dsl
{

template <class T>
class mtkDataProcessParameter : public DSLObject
{
    public:
                                    mtkDataProcessParameter(const T& val = 0);
                                      ~mtkDataProcessParameter(){};

        T                           operator+=(const T& val);
        T                             operator-=(const T& val);
        T                             operator=(const T& val);

                                    operator T() const {return mTheParameter;}
        mtkDataProcessParameter*     operator->(){return this;}

        T                               GetParameter(){return mTheParameter;}
        void                            SetParameter(const T& p){mTheParameter = p;}
        bool                            IsApplied(){return mIsApplied;}
        void                            Applied(){mIsApplied = true;}
		
	private:
        T                             mTheParameter;
        bool                         mIsApplied;
};

typedef mtkDataProcessParameter<bool>     boolParameter;
typedef mtkDataProcessParameter<int>     intParameter;
typedef mtkDataProcessParameter<double> doubleParameter;
typedef mtkDataProcessParameter<string> stringParameter;

template <class T>
mtkDataProcessParameter<T>::mtkDataProcessParameter(const T& val)
:
mTheParameter(val),
mIsApplied(false)
{}

template <class T>
T mtkDataProcessParameter<T>::operator+=(const T& val)
{
    mTheParameter += val;
    return mTheParameter;
}

template <class T>
T mtkDataProcessParameter<T>::operator-=(const T& val)
{
    mTheParameter -= val;
      return mTheParameter;
}

template <class T>
T mtkDataProcessParameter<T>::operator=(const T& val)
{
    mTheParameter = val;
      return mTheParameter;
}

}
#endif
