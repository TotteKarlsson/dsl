#ifndef dslLogLevelH
#define dslLogLevelH
#include "dslCommonExporter.h"
#include "dslProperty.h"
#include "dslTypeInfo.h"
#include <string>

//---------------------------------------------------------------------------

namespace dsl
{

using std::string;

//DSL_COMMON
enum  LogLevel
{
    lUndef      = -1,
    lError      = 0,
    lWarning    = 1,
    lInfo       = 2,
    lDebug      = 3,
    lDebug1     = 4,
    lDebug2     = 5,
    lDebug3     = 6,
    lDebug4     = 7,
    lDebug5     = 8,
    lAny        = 9,
    lUser
};

DSL_COMMON int 			getHighestLogLevel();
DSL_COMMON LogLevel 	toLogLevel(const string& level);
DSL_COMMON LogLevel 	getLogLevel(int lvl);
DSL_COMMON std::string 	toString(const LogLevel& lvl);

template<>
inline Property<LogLevel>::operator LogLevel () const
{
    return (*mValue);
}

template<> inline
std::string Property<LogLevel>::getValueAsString() const
{
    return dsl::toString(getValue());
}

template<> inline
bool Property<LogLevel>::write(IniFile* iniFile, const string& section)
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
bool Property<LogLevel>::read(IniFile* iniFile, const string& section)
{
    if(iniFile == nullptr)
    {
        return false;
    }

    string val(iniFile->readString(mKey, section, dsl::toString(mDefaultValue)));

    LogLevel tempVal = toLogLevel(val);

    mWasRead = iniFile->wasItFound();
    setValue( mWasRead ? tempVal : mDefaultValue);
    return mWasRead;
}

template<> inline
bool Property<LogLevel>::assignValueFromString(const string& v)
{
    return false;
}

template<> inline
string Property<dsl::LogLevel>::getTypeName() const
{
    return "LogLevel";
}

template<> inline
dsl::ObjectType dsl::Property<LogLevel>::getPropertyType()
{
    return otLogLevel;
}

}
#endif
