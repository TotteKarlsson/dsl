#pragma hdrstop
#include "dslApplicationProperties.h"
#include "dslUtils.h"
#include "dslFileUtils.h"
#include "dslWin32Utils.h"
#include "dslLogger.h"
#include "dslRegistryProperties.h"
#include "dslException.h"
#include "dslVCLUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

namespace dsl
{
ApplicationProperties::ApplicationProperties(const string& appName, const string& regRoot, const string& version)
:
AppName						(appName),
AppRegistryRoot    			(joinPath(regRoot, version)),
AppDataFolder				(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), AppName)),
//TempFileFolder 				(joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), AppName)),
mIniFile                    (joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), AppName, AppName + ".ini")),
RestartMutexName            (AppName + "RestartMutex"),
AppMutex                    (NULL),
RestartMutex                (NULL),
OtherAppWindow             	(NULL),
AppTheme       			    (""),
FullDateTimeFormat          ("%Y-%m-%dT%H:%M:%S"),
DateFormat                  ("%Y-%m-%d"),
TimeFormat                  ("%H:%M:%S"),
CommonAppDataLocation       (joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), AppName)),
//LogFileLocation             (joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), AppName)),
//LogFileName                 (AppName + ".log"),
IsDevelopmentRelease        (false),
AppIsStartingUp             (true),
AppIsClosingDown            (false)
{
	if(!folderExists(AppDataFolder))
	{
		createFolder(AppDataFolder.c_str());
	}

	//Load ini file
	mIniFile.load();
}

ApplicationProperties::~ApplicationProperties()
{}

void ApplicationProperties::writeProperties()
{
    //Write all properties
    for(mSectionIterator = mSections.begin(); mSectionIterator != mSections.end(); mSectionIterator++)
    {
        PropertiesSP props = (*mSectionIterator);
        if(props)
        {
            Log(lInfo) << "Writing property section: "<<props->getSectionName()<< " with " << props->count()<<" properties";
            props->write();
        }
    }
}

bool ApplicationProperties::saveIniFile()
{
    mIniFile.save();
}

void ApplicationProperties::init()
{
    string appMutexName = string(AppName + "Mutex").c_str();
    AppMutex = ::CreateMutexA(NULL, FALSE, appMutexName.c_str());
    if(GetLastError() == ERROR_ALREADY_EXISTS)
    {
    	throw(DSLException("Application \"" + AppName + "\" is already running!"));
    }

//    setupLogging();

     try
     {
        AppTheme = readStringFromRegistry(AppRegistryRoot, "", "Theme",  AppTheme);
        if(AppTheme.size())
        {
    		TStyleManager::TrySetStyle(AppTheme.c_str());
	   	   	TStyleManager::SetStyle(AppTheme.c_str());
        }
     }
     catch(...)
     {}
}

void ApplicationProperties::append(PropertiesSP props)
{
    mSections.push_back(props);
}

shared_ptr<IniFileProperties> ApplicationProperties::appendNewINISection(const string& secName)
{
	shared_ptr<IniFileProperties> p = shared_ptr<IniFileProperties>(new IniFileProperties(&mIniFile, secName));
    mSections.push_back(p);
    return p;
}

shared_ptr<TRegistryProperties> ApplicationProperties::appendNewRegistrySection(const string& secName)
{
	shared_ptr<TRegistryProperties> p = shared_ptr<TRegistryProperties>(new TRegistryProperties(secName));
    mSections.push_back(p);
    return p;
}

IniFile& ApplicationProperties::getIniFile()
{
    return mIniFile;
}

PropertiesSP ApplicationProperties::getSection(const string& sec)
{
    for(mSectionIterator = mSections.begin(); mSectionIterator != mSections.end(); mSectionIterator++)
    {
        PropertiesSP props = (*mSectionIterator);
        if(props && props->getSectionName() == sec)
        {
            return props;
        }
    }
    return PropertiesSP();
}

bool ApplicationProperties::hasChanges()
{
    for(mSectionIterator = mSections.begin(); mSectionIterator != mSections.end(); mSectionIterator++)
    {
        PropertiesSP props = (*mSectionIterator);
        if(props && props->isModified())
        {
            return true;
        }
    }
    return false;
}

PropertiesSP ApplicationProperties::getFirstSection() const
{
    mSectionIterator = mSections.begin();
    return (*mSectionIterator);
}

PropertiesSP ApplicationProperties::getNextSection()
{
    mSectionIterator++;
    if(mSectionIterator == mSections.end())
    {
        return PropertiesSP();
    }
    return (*mSectionIterator);
}

PropertiesSP ApplicationProperties::getCurrentSection()
{
    return  (*mSectionIterator);
}

//Todo, move this away
string ApplicationProperties::getLogFileNameAndPath()
{
    return joinPath(AppDataFolder, AppName + ".log");
}

}
