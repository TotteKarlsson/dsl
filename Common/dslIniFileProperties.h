#ifndef dslIniFilePropertiesH
#define dslIniFilePropertiesH
#include "dslCommonExporter.h"
#include "dslProperties.h"
#include <string>
#include "dslSharedPointer.h"

//---------------------------------------------------------------------------

namespace dsl
{
class IniFile;
using std::vector;
using std::string;

//IniFileProperties is a container for a group of properties
//that can be written and retrieved from a INI file
class DSL_COMMON IniFileProperties : public Properties
{
	public:

                                                            IniFileProperties(IniFile* iniFile = nullptr, const string& iniSection = dsl::gEmptyString);
                                                            ~IniFileProperties();

        void                                                setIniFile(IniFile* iniFile);
        IniFile*                                            getIniFile();
        string                                              getIniFileName();

        void                                                addStringProperty(const string& label, const string& value);
        void                                                addIntProperty(const string& label, int value);

        virtual bool                                        read();
        virtual bool                                        write();

    protected:
        IniFile*                     	                    mIniFile;

};

#if defined(__BORLANDC__) && !defined(__clang__)
	typedef std::tr1::shared_ptr<IniFileProperties> IniFilePropertiesSP;
#elif defined(_MSC_VER) || defined (__clang__)
	typedef std::shared_ptr<IniFileProperties> IniFilePropertiesSP;
#endif

}
#endif
