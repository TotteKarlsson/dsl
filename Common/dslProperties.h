#ifndef dslPropertiesH
#define dslPropertiesH
#include "dslCommonExporter.h"
#include "dslProperty.h"
#include "dslObject.h"
#include "dslException.h"
#include <vector>
#include <string>
#include <sstream>
#include "dslSharedPointer.h"
//---------------------------------------------------------------------------

namespace dsl
{

using std::vector;
using std::string;
using std::stringstream;

//Properties is a container for a group of properties
//See also INIFileProperties and Registry properties
class DSL_COMMON Properties : public DSLObject
{
	public:

                                                            Properties(const string& iniSection = dsl::gEmptyString);
        virtual                                             ~Properties();
        virtual string                                      asString(const char&) const;

        void                                                add(dsl::BaseProperty* o);

        void                                                setSectionName(const string& sec);
        string                                              getSectionName() const;
        unsigned int                                        count() const;

        BaseProperty*				                        operator [](int index);
        BaseProperty*				                        operator [](const string& label);
		BaseProperty*				                        getProperty(const string& paraLabel);
        BaseProperty*				                        getProperty(int index);

        template <class T>
        T                                                   getPropertyValue(const string& propName);

        template <class T>
        T&                                                  getPropertyValueReference(const string& propName);

        template <class T>
        T&                                                  getPropertyEditValueReference(const string& propName);

        template <class T>
        bool                                                setPropertyValue(const string& propName, const T& newValue);

        string                                              getListing() const;
        StringList                                          getNames() const;

        virtual bool                                        read();
        virtual bool                                        write();

        void                                                enableEdits();
        void                                                applyEdits();
        void                                                disableEdits();
        void                                                discardEdits();
        bool                                                isModified() const;

		DSL_COMMON friend ostream&                          operator<<(ostream& stream, const Properties& p);

    protected:
        vector<BaseProperty*>     	                        mProperties;
        string                       	                    mSectionName;

                                                            //Implement in derived classes
        virtual void                                        setupProperties();
};

typedef shared_ptr<Properties> PropertiesSP;

DSL_COMMON string toString(const Properties& props);

DSL_COMMON string getFormattedParStr(const string& str, const Properties& props);

template<> inline
bool Property<Properties>::write(IniFile* iniFile, const string& section)
{
    return false;
}

template<> inline
bool Property<Properties>::read(dsl::IniFile* iniFile, const std::string& section)
{
    return false;
}

template<> inline
bool Property<Properties>::assignValueFromString(const string& val)
{
    return false;
}

template<> inline
string Property<Properties>::getTypeName() const
{
    return "properties";
}


//template <class T> inline
//T& Properties::getPropertyValueReference<T>(const string& propName)
//{
//    BaseProperty* bp = this->getProperty(propName);
//    if(!bp)
//    {
//        stringstream str;
//        str << "The property: "<<propName<<" could not be found!";
//        throw(DSLException(str.str()));
//    }
//
////    if(bp->getPropertyType() != otStdString)
////    {
////        stringstream str;
////        str<<"Property \""<<propName<<"\" is of type: "<<dsl::toString(bp->getPropertyType())<<". Tried to use property type: "<<dsl::toString(otInt);
////        throw(DSLException(str.str()));
////    }
//
//    T* valueHandle = (T*) bp->getValueHandle();
//    return *valueHandle;
//}
//
//template <class T> inline
//T& Properties::getPropertyEditValueReference<T>(const string& propName)
//{
//    BaseProperty* bp = this->getProperty(propName);
//    if(!bp)
//    {
//        stringstream str;
//        str << "The property: "<<propName<<" could not be found!";
//        throw(DSLException(str.str()));
//    }
//
////    if(bp->getPropertyType() != otStdString)
////    {
////        stringstream str;
////        str<<"Property \""<<propName<<"\" is of type: "<<dsl::toString(bp->getPropertyType())<<". Tried to use property type: "<<dsl::toString(otInt);
////        throw(DSLException(str.str()));
////    }
//
//    T* valueHandle = (T*) bp->getEditValueHandle();
//    return *valueHandle;
//}

}
#endif
