#ifndef dslStringListH
#define dslStringListH
#include "dslObject.h"
#include "dslConstants.h"
#include "dslProperty.h"
#include "dslTypeInfo.h"
#include <vector>
#include <string>
//---------------------------------------------------------------------------

namespace dsl
{

using std::vector;
using std::string;
using std::ostream;

class DSL_COMMON StringList : public DSLObject
{
    public:

																StringList(const string& str = gEmptyString, const char delimiter = gEOL);
																StringList(const vector<string>& strings);
                                                                StringList(const vector<int>& ints);

                                                                //Copy constructor
                                                                StringList(const StringList& cp);
                                                                ~StringList();

        virtual void                                            reSize(int size);
        virtual void                                            insertAt(int index, const string& item);

        virtual void                                            append(const string& item);
        virtual void                                            appendList(const StringList& list);
        void                                                    truncate(int linesAfter);
        virtual string                                          asString(const char& delimiter = '\0') const;
//        void													setDelimiter(char del) {mDelimiter = del;}
        char                                                    getDelimiter() const;
        unsigned int                                            size() const;
        unsigned int                                            count() const;
        void													sort();

        virtual StringList&                                     operator=(const StringList& rhs);
        virtual StringList&                                     operator=(const vector<string>& rhs);
        virtual bool		                                    operator!=(const StringList& rhs);
		string						                            at(int i);
        string&                                                 operator[](int index);
        const string&                                           operator[](int index) const;
        StringList                                              operator-(const StringList& rhs);
        void                                                    removeAt(int index);
        int                                                     find(const string& item) const;
        int                                                     indexOf(const string& item);
        string													getLineContaining(const string& item);
        void                                                    clear();
        void                                                    empty();
        bool                                                    contains(const string& item) const;
        bool                                                    dontContain(const string& item) const;
        string                                                  getLongest();
        string                                                  getShortest();
        bool													reverse();

        string													popBack();
        string													popFront();

        vector<string>::iterator                                begin();
        vector<string>::iterator                                end();
        void                                                    preFix(const string& fix);
        void                                                    postFix(const string& fix);

		const vector<string>&		                            getContainer();

        DSL_COMMON friend ostream&                              operator<<(ostream& stream, const StringList& list);
        operator const                                          vector<string>&() const;

    protected:
        vector<string>                                          mStrings;
        vector<string>::iterator                                mLI;
        char                                                    mDelimiter;
};

//When being a property
//DSL_COMMON std::string toString(const vector<string>& strings);
DSL_COMMON std::string toString(const StringList& lvl);

template<> inline
string Property<dsl::StringList>::getTypeName() const
{
    return "StringList";
}

template<> inline
bool Property<StringList>::assignValueFromString(const string& v)
{
    return false;
}

template<> inline
bool Property<StringList>::write(IniFile* iniFile, const string& section)
{
    if(&iniFile == nullptr)
    {
        return false;
    }

    StringList sl = getValue();
    string toWrite = sl.asString();
    iniFile->writeString(mKey, toWrite, "", section);
    return true;
}

template<> inline
bool Property<StringList>::read(IniFile* iniFile, const string& section)
{
    if(&iniFile == nullptr)
    {
        return false;
    }

    string val(iniFile->readString(mKey, section, dsl::toString(mDefaultValue)));
    StringList sl = getValue();

    StringList tempVal(val, sl.getDelimiter());

    mWasRead = iniFile->wasItFound();
    setValue( mWasRead ? tempVal : mDefaultValue);
    return mWasRead;
}


//template<>
//std::string Property<StringList>::getValueAsString() const
//{
//    return dsl::toString(getValue());
//}
//
//
//
//
//template<>
//dsl::ObjectType dsl::Property<StringList>::getPropertyType()
//{
//    return otStringList;
//}
//

}


#endif
