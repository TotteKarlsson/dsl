#ifndef dslApplicationPropertiesH
#define dslApplicationPropertiesH
#include <list>
#include <System.hpp>
#include "dslObject.h"
#include "dslProperties.h"
#include "dslVCLCommonExporter.h"
#include "dslIniFile.h"
#include "dslSharedPointer.h"
#include "dslIniFileProperties.h"
#include "dslRegistryProperties.h"
//---------------------------------------------------------------------------

namespace dsl
{

using std::list;
typedef shared_ptr<Properties> PropertiesSP;

//Todo rename to ApplicationUtilities
//Or possibly split up
class VCLCOMMON ApplicationProperties : public DSLObject
{
    public:
                                                                ApplicationProperties(const string& appName, const string& regRoot, const string& version);
                                                                ~ApplicationProperties();

		void													writeProperties();
        PropertiesSP                                  			getSection(const string& sec);
        void                                                    append(PropertiesSP props);

        shared_ptr<IniFileProperties>                           appendNewINISection(const string& secName);
        shared_ptr<TRegistryProperties>                         appendNewRegistrySection(const string& secName);

        PropertiesSP                                            getFirstSection() const;
        PropertiesSP                                            getNextSection();
        PropertiesSP                                            getCurrentSection();
        bool                                                    hasChanges();
		string                                                  AppName;
		HWND         			                                OtherAppWindow;
		HANDLE 					                                AppMutex;
		HANDLE 			  		                                RestartMutex;
		string                                                  RestartMutexName;
		string              	                                AppDataFolder;
		string              	                                AppRegistryRoot;
//		string                                                  TempFileFolder;
		string                                                  AppTheme;
		string                                                  FullDateTimeFormat;
		string                                                  DateFormat;
		string                                                  TimeFormat;
		string                                                  CommonAppDataLocation;
//		string                                                  LogFileLocation;
//		string                                                  LogFileName;
		bool                                                    IsDevelopmentRelease;
		bool                                                    AppIsStartingUp;
		bool                                                    AppIsClosingDown;

		void 					                                init();
//		void 					                                setupLogging();
		string			                                        getLogFileNameAndPath();

        IniFile&                                                getIniFile();
        bool                                					saveIniFile();

	protected:
		IniFile                 						        mIniFile;

                                                    	        //Each item holds a container of related properties
        mutable list<PropertiesSP >   							mSections;
        mutable list<PropertiesSP >::iterator    				mSectionIterator;
};
}
#endif
