#ifndef dslRangeH
#define dslRangeH
#include "dslObject.h"
#include "dslProperty.h"
//---------------------------------------------------------------------------

namespace dsl
{

template <class T>
class Range : public DSLObject
{
	public:
    				        Range(T min = 0, T max = 0);
    				        Range(const Range& r);
	   	Range& 				operator=(const Range& rhs);
    	bool 		        setMax(T v);
    	T 			        getMax() const;
    	T& 			        getMaxReference() {return mMax;}

    	bool 		        setMin(T v);
    	T 			        getMin() const;
    	T& 			        getMinReference() {return mMin;}

    private:

    	T			        mMin;
        T			        mMax;
};

typedef Range<double> DoubleRange;

template<class T>
Range<T>::Range(T min, T max)
:
mMin(min),
mMax(max)//,
//mDefaultValue(0.0,0.0)
{}

template<class T>
Range<T>::Range(const Range& c)
{
	mMin = c.mMin;
	mMax = c.mMax;
}

template<class T>
Range<T>& Range<T>::operator=(const Range& rhs)
{
	if (this != &rhs)
	{
		mMin = rhs.mMin;
		mMax = rhs.mMax;
    }
    return *this;
}

template<class T>
bool Range<T>::setMax(T v)
{
	mMax = v;
}

template<class T>
T Range<T>::getMax() const
{
	return mMax;
}

template<class T>
bool Range<T>::setMin(T v)
{
	mMin = v;
}

template<class T>
T Range<T>::getMin() const
{
	return mMin;
}

DSL_COMMON Range<double> getRange(const string& val);
//Property stuff

//Double Ranges
DSL_COMMON std::string toString(const Range<double>& lvl);

template<> inline
Range<double>::Range(double min, double max)
:
mMin(min),
mMax(max)
{}

template<> inline
std::string Property< Range<double> >::getValueAsString() const
{
    return dsl::toString(getValue());
}

template<> inline
bool Property< Range<double> >::write(IniFile* iniFile, const string& section)
{
    if(iniFile == nullptr)
    {
        return false;
    }

    string toWrite;
    toWrite = dsl::toString(getValue());
    iniFile->writeString(mKey, toWrite, "", section);
    return true;
}

template<> inline
bool Property< Range<double> >::read(IniFile* iniFile, const string& section)
{
    if(iniFile == nullptr)
    {
        return false;
    }

    string val(iniFile->readString(mKey, section, dsl::toString(mDefaultValue)));

    Range<double> tempVal = getRange(val);

    mWasRead = iniFile->wasItFound();
    setValue( mWasRead ? tempVal : mDefaultValue);
    return mWasRead;
}

template<> inline
bool Property< Range<double> >::assignValueFromString(const string& v)
{
    return false;
}

template<> inline
string Property< Range<double> >::getTypeName() const
{
    return "Range";
}

}
#endif
