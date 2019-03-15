#ifndef dslPropertyH
#define dslPropertyH
#include "dslObject.h"
#include "dslIniFile.h"
#include "dslStringUtils.h"
#include "dslCommonExporter.h"
#include "dslBaseProperty.h"
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include <string>
//---------------------------------------------------------------------------

namespace dsl
{

using std::string;
using std::ostream;
using Poco::DateTimeFormatter;

template <class T>
class Property : public BaseProperty
{
    public:
                                                    Property(const T& value, const string& lbl = gNoneString);

                                                    ~Property();
		void                                        setDefaultValue(const T& val);
		T	                                        getDefaultValue();
        void                                        setValue(const T& val);
        void                                        setEditValue(const T& val);
        void                                        setComment(const string& val);
        void                                        resetToDefault();
        virtual string                              getTypeName() const;
        T                                           getValue() const;
        string                                      getValueAsString() const;
        string                                      getComment();
        ObjectType                                  getObjectType();
        ObjectType                                  getPropertyType();
        void*                                       getValueHandle();
        void*                                       getEditValueHandle();
        T&                                          getValueReference();
        T&                                          getEditValueReference();

        void                                        setValueReference(T& reference, 	bool transferValue = false);
        void                                        setEditValueReference(T& reference, bool transferValue = false);

                                                    operator T() const;
        T                                           operator+(const T& a);
        void                                        operator+=(const T& val);
        T&                                          operator=(const T& a);

        bool                                        operator==(const T& val);

        friend                                      std::ostream& operator<<(ostream& stream, const Property<T>& val)
                                                    {
                                                        stream << val.getValueAsString();
                                                        return stream;
                                                    }

        string                                      getLabel();
        void                                        setLabel(const string& lbl);

        string                                      getINIRecord();
        const char*                                 c_str() const;

                                                    //The setup function return a reference to the object.
                                                    //The reference allow catching the object immediately after the object is setup.
        Property<T>&                                setup(const string& lbl, const T& val, bool readIt = true);

        bool                                        read(IniFile* iniFile,  const string& section);
        bool                                        write(IniFile* iniFile, const string& section);
        bool                                        assignValueFromString(const string& val);
        void                                        applyEdit();

    protected:
        T                                           mDefaultValue;
        T                                           mDummyValue;
        T                                           mEditValue;
        T*                                          mValue;
                                                    //Initially the mValue points to DummyValue
                                                    //However, the value can be set to point to
                                                    //another variable by using the function setReference
                                                    //and set back to setReferenceToDummy
};

template <class T> inline
Property<T>::Property(const T& value, const string& lbl)
:
BaseProperty(lbl)
{
    mDummyValue = value;
    mValue = &mDummyValue;
}

template <class T> inline
Property<T>::~Property()
{}

template<class T> inline
void Property<T>::applyEdit()
{
    (*mValue) = mEditValue;
    mIsModified = false;
}

template<class T> inline
void Property<T>::setDefaultValue(const T& val)
{
    mDefaultValue = val;
}

template<class T> inline
T Property<T>::getDefaultValue()
{
    return mDefaultValue;
}

template<class T> inline
void Property<T>::setValue(const T& val)
{
	if(isInEditMode())
    {
        mEditValue = val;
        mIsModified = true;
    }
    else
    {
    	*mValue = val;
    }
}

template<class T> inline
void Property<T>::setEditValue(const T& val)
{
    mEditValue = val;
}

template<class T> inline
void Property<T>::setComment(const string& val)
{
    mComment = val;
}

template<class T> inline
void Property<T>::resetToDefault()
{
    *mValue = mDefaultValue;
}

template<class T> inline
T Property<T>::getValue() const
{
    return (T) (*mValue);
}

template<class T> inline
string Property<T>::getComment()
{
    return mComment;
}

template<class T> inline
ObjectType Property<T>::getObjectType()
{
    return otUndefined;
}

template<class T> inline
void* Property<T>::getValueHandle()
{
    return mValue;
}

template<class T> inline
void* Property<T>::getEditValueHandle()
{
    return &mEditValue;
}

template<class T> inline
T& Property<T>::getValueReference()
{
    return *mValue;
}

template<class T> inline
T& Property<T>::getEditValueReference()
{
    return mEditValue;
}

template<class T> inline
void Property<T>::setValueReference(T& reference, bool transferValue)
{
	if(transferValue)
    {
        reference = *mValue;
    }

    mValue = &reference;
}

template<class T> inline
void Property<T>::setEditValueReference(T& reference, bool transferValue)
{
	if(transferValue)
    {
        reference = *mEditValue;
    }

    mEditValue = &reference;
}

template<class T> inline
bool Property<T>::operator==(const T& val)
{
    return (*mValue) == val;
}

template<class T> inline
string Property<T>::getLabel()
{
    return mKey;
}

template<class T> inline
void Property<T>::setLabel(const string& lbl)
{
    mKey = lbl;
}

template<class T> inline
Property<T>& Property<T>::setup(const string& lbl, const T& val, bool readIt)
{
    mKey = lbl;
    setValue(val);
    mDefaultValue = val;
    mDoReadFromINI = readIt;
    return *this;
}

template<class T> inline
const char* Property<T>::c_str() const
{
    string tmp = getValueAsString();
    return tmp.c_str();
}

template<class T> inline
T Property<T>::operator+(const T& addMe)
{
    T newVal = (*mValue) + addMe;
    return newVal;
}

template<class T> inline
void Property<T>::operator += (const T& val)
{
    (*mValue) += (T) val;
}

template<class T> inline
string Property<T>::getValueAsString() const
{
    T val = getValue();
    return dsl::toString(val);
}

template<class T> inline
string Property<T>::getINIRecord()
{
    return string(mKey + "=" + dsl::toString((T) getValue()));
}

template<class T> inline
ObjectType Property<T>::getPropertyType()
{
    return otUndefined; //(getValue());
}

template<class T> inline
T& Property<T>::operator=(const T& rhs)
{
    (*mValue) = rhs;
    return (*mValue);
}

//======================== SPECIALIZATIONS =================================================
//------------- bool
template<> inline
string Property<bool>::getTypeName() const
{
    return "bool";
}

template<> inline
ObjectType Property<bool>::getPropertyType()
{
	return otBool;
}

template<> inline
Property<bool>::operator bool() const
{
    return (*mValue);
}

template<> inline
void* Property<bool>::getValueHandle()
{
    return (void*) mValue;
}

template<> inline
bool Property<bool>::assignValueFromString(const string& val)
{
    setValue(dsl::toBool(val));
    return true;
}

template<> inline
bool Property<bool>::operator+(const bool& addMe)
{
    bool newVal = (*mValue) | addMe;
    return newVal;
}

template<> inline
void Property<bool>::operator += (const bool& val)
{
    (*mValue) = (*mValue) | val;
}

template<> inline
bool Property<bool>::read(IniFile* iniFile, const string& section)
{
    if(iniFile == nullptr)
    {
        return false;
    }

    bool tempVal = iniFile->readBool(mKey, section, mDefaultValue);
    mWasRead =     iniFile->wasItFound();
    setValue(mWasRead ? tempVal : mDefaultValue);
    return mWasRead;
}

template<> inline
bool Property<bool>::write(IniFile* iniFile, const string& section)
{
    if(iniFile == nullptr)
    {
        return false;
    }

    iniFile->writeBool(mKey, getValue(), "", section);
    return true;
}

//------------- unsigned int -----------------------------------------
template<> inline
bool Property<unsigned int>::read(IniFile* iniFile, const string& section)
{
    if(iniFile == nullptr)
    {
        return false;
    }

    unsigned int tempVal = iniFile->readInteger(mKey, section, mDefaultValue);
    mWasRead = iniFile->wasItFound();
    setValue(mWasRead ? tempVal : mDefaultValue);
    return mWasRead;
}
template<> inline
bool Property<unsigned int>::write(IniFile* iniFile, const string& section)
{
    if(iniFile == nullptr)
    {
        return false;
    }

    iniFile->writeInteger(mKey, getValue(), "", section);
    return true;
}

//------------- int -----------------------------------------
template<> inline
string Property<int>::getTypeName() const
{
    return "int";
}

template<> inline
Property<int>::operator int () const
{
    return (*mValue);
}

template<> inline
bool Property<int>::assignValueFromString(const string& val)
{
    setValue(dsl::toInt(val));
    return true;
}

template<> inline
ObjectType Property<int>::getPropertyType()
{
    return otInt;
}

template<> inline
bool Property<int>::write(IniFile* iniFile, const string& section)
{
    if(iniFile == nullptr)
    {
        return false;
    }

    iniFile->writeInteger(mKey, getValue(), "", section);
    return true;
}

template<> inline
bool Property<int>::read(IniFile* iniFile, const string& section)
{
    if(iniFile == nullptr)
    {
        return false;
    }

    int tempVal = iniFile->readInteger(mKey, section, mDefaultValue);
    mWasRead = iniFile->wasItFound();
    setValue(mWasRead ? tempVal : mDefaultValue);
    return mWasRead;
}

//------------- double -----------------------------------------
template<> inline
string Property<double>::getTypeName() const
{
    return "double";
}

template<> inline
Property<double>::operator double () const
{
    return (*mValue);
}

template<> inline
bool Property<double>::assignValueFromString(const string& val)
{
    setValue(dsl::toDouble(val));
    return true;
}

template<> inline
ObjectType Property<double>::getPropertyType()
{
    return otDouble;
}

template<> inline
bool Property<double>::write(IniFile* iniFile, const string& section)
{
    if(iniFile == nullptr)
    {
        return false;
    }

    iniFile->writeFloat(mKey, getValue(), "", section);
    return true;
}

template<> inline
bool Property<double>::read(IniFile* iniFile, const string& section)
{
    if(iniFile == nullptr)
    {
        return false;
    }

    double tempVal = iniFile->readDouble(mKey, section, mDefaultValue);
    mWasRead = iniFile->wasItFound();
    setValue(mWasRead ? tempVal : mDefaultValue);
    return mWasRead;
}

//------------- string -----------------------------------------
template<> inline
string Property<string>::getTypeName() const
{
    return "string";
}

template<> inline
ObjectType Property<string>::getPropertyType()
{
    return otStdString;
}

template<> inline
Property<string>::operator string() const
{
    return *mValue;
}

template<> inline
const char* Property<string>::c_str() const
{
    return mValue->c_str();
}

template<> inline
bool Property<string>::assignValueFromString(const string& val)
{
    setValue(val);
    return true;
}

template<> inline
bool Property<std::string>::write(IniFile* iniFile, const string& section)
{
    if(iniFile)
    {
        iniFile->writeString(mKey, getValue(), "", section);
        return true;
    }
    else
    {
        return false;
    }
}

template<> inline
bool Property<std::string>::read(IniFile* iniFile, const string& section)
{
    if(iniFile == nullptr)
    {
        return false;
    }

    string    tempVal = iniFile->readString(mKey, section, mDefaultValue);
    mWasRead = iniFile->wasItFound();
    setValue(mWasRead ? tempVal : mDefaultValue);
    return mWasRead;
}

//------------- Poco DateTime -----------------------------------------
template<> inline
Property<Poco::DateTime>::operator Poco::DateTime () const
{
    return (*mValue);
}

template<> inline
string Property<Poco::DateTime>::getTypeName() const
{
	return "dateTime";
}

template<> inline
string Property<Poco::DateTime>::getValueAsString() const
{
	DateTime val = getValue();
	return dsl::toString(val);
}

template<> inline
bool Property<Poco::DateTime>::assignValueFromString(const string& val)
{
    //setValue(val);
    return false;
}

template<> inline
bool Property<Poco::DateTime>::write(IniFile* iniFile, const string& section)
{
    if(iniFile)
    {
		//DateTime dt();
		//Seem like poco constants don't work in inlines???
		//string fmt(Poco::DateTimeFormat::ISO8601_FORMAT);
		string fmt("%Y-%m-%dT%H:%m:%SZ");
		string tmp(DateTimeFormatter::format(getValue(), fmt));
        iniFile->writeString(mKey, tmp, "", section);
        return true;
    }
    else
    {
        return false;
    }
}

template<> inline
bool Property<Poco::DateTime>::read(IniFile* iniFile, const string& section)
{
    if(iniFile == nullptr)
    {
        return false;
    }

    string    tempVal = iniFile->readString(mKey, section, "1999-12-01");
    DateTime dt(strToDateTime(tempVal));

    mWasRead = iniFile->wasItFound();
    setValue(mWasRead ? dt : mDefaultValue);
    return mWasRead;
}

}
#endif

