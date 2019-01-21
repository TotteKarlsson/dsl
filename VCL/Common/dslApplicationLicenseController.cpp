#pragma hdrstop
#include "dslVCLUtils.h"
#include "dslApplicationLicenseController.h"

#include <memory>
#include <Registry.hpp>
#include <sstream>
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DateTimeParser.h"
#include "Poco/Timezone.h"

#pragma package(smart_init)
//---------------------------------------------------------------------------

using namespace Poco;
using namespace std;

namespace dsl
{

ApplicationLicenseController::ApplicationLicenseController(const string& registryRoot)
:
mRegistryRoot(registryRoot),
mTrialPeriod(Poco::Timespan::DAYS*30),
mToday(Poco::DateTime()),
mExpirationDate(5000),
mLicenseMode(lmTrial),
mActivationKey(""),
mHasExpirationDate(false)
{
    string today = DateTimeFormatter::format(mToday, DateTimeFormat::SORTABLE_FORMAT);
    readLicenseInfo();
}

ApplicationLicenseController::~ApplicationLicenseController()
{}

void ApplicationLicenseController::hasExpirationDate(bool setit)
{
    mHasExpirationDate = setit;
}

bool ApplicationLicenseController::hasExpirationDate()
{
    return mHasExpirationDate;
}

bool ApplicationLicenseController::setLicenseMode(LicenseMode mode)
{
    mLicenseMode = mode;
    return true;
}

bool ApplicationLicenseController::isPreRelease()
{
    return mLicenseMode == lmPreRelease ? true : false;
}

bool ApplicationLicenseController::storeActivationKey(const string& key)
{
    //Store the key in the registry
    std::auto_ptr<TRegIniFile> Registry(new TRegIniFile(mRegistryRoot.c_str()));
    Registry->WriteString(mRegistryRoot.c_str(), "ActivationKey", vclstr(key));
    return true;
}

string ApplicationLicenseController::retrieveActivationKey()
{
    //Read the key from the registry
    std::auto_ptr<TRegIniFile> Registry(new TRegIniFile(mRegistryRoot.c_str()));
    String key = Registry->ReadString(mRegistryRoot.c_str(), "ActivationKey", "");
    mActivationKey = stdstr(key);
    return mActivationKey;
}

void ApplicationLicenseController::setTrialPeriod(const Poco::Timespan& timeSpan)
{
    mTrialPeriod = timeSpan;
}

Poco::Timespan ApplicationLicenseController::getTrialPeriod()
{
    return mTrialPeriod;
}

Poco::Timespan ApplicationLicenseController::getTrialPeriodLeft()
{
    return mTrialPeriod - (mToday - mFirstExecutionDate);
}

LicenseMode ApplicationLicenseController::getLicenseMode()
{
    return mLicenseMode;
}

//bool ApplicationLicenseController::hasExpirationDate()
//{
//    return (mExpirationDate < Poco::DateTime(3000,1,1)) ? true : false;
//}

Poco::DateTime ApplicationLicenseController::getExpirationDate()
{
    return mExpirationDate;
}

void ApplicationLicenseController::setExpirationDate(const Poco::DateTime& exp)
{
    mExpirationDate = exp;
}

void ApplicationLicenseController::readLicenseInfo()
{
    std::auto_ptr<TRegIniFile> Registry(new TRegIniFile(mRegistryRoot.c_str()));
    bool isFirstTime = Registry->ReadBool("", "IsFirstTime", true);
    String section("Licensing");
    if(isFirstTime)
    {
        //Start with trial mode
        mLicenseMode = lmTrial;

        DateTime now;
        string s = DateTimeFormatter::format(now, DateTimeFormat::SORTABLE_FORMAT);
        Registry->WriteString(section, "StartTrialDate",   s.c_str());
        Registry->WriteBool(section,   "IsFirstTime", false);
    }
    else
    {
        //Read registry
        //Look for activation key
        //The key will need to be validated outside of the controller
        mActivationKey = retrieveActivationKey();

        String regS = Registry->ReadString(section, "StartTrialDate", "Unknown");
        string reg = stdstr(regS);
        DateTime startDate;

        int tzd = 0;
        if(DateTimeParser::tryParse(reg, startDate, tzd))
        {
            mFirstExecutionDate = Poco::DateTime(startDate);
        }
    }
}

bool ApplicationLicenseController::isTrialModeExhausted()
{
    string t = DateTimeFormatter::format(mToday, DateTimeFormat::SORTABLE_FORMAT);
    string f = DateTimeFormatter::format(mFirstExecutionDate, DateTimeFormat::SORTABLE_FORMAT);
    Poco::Timespan span = mToday - mFirstExecutionDate;
    string sSpan = DateTimeFormatter::format(span);
    return (mToday - mFirstExecutionDate > mTrialPeriod) ? true : false;
}

void ApplicationLicenseController::isActivated(bool isIt)
{
    mLicenseMode = (isIt == true) ? lmActivated : lmTrial;
}

bool ApplicationLicenseController::isActivated()
{
    return mLicenseMode == lmActivated ? true : false;
}

std::string toString(LicenseMode lm)
{
    switch(lm)
    {
        case lmTrial:       return "Trial";
        case lmActivated:   return "Activated";
        case lmPreRelease:  return "PreRelease";
        case lmUnknown:     return "Unknown";
        default:            return "Trial";
    }
}

LicenseMode toLicenseMode(const string& lms)
{
    if(compareStrings(lms, dsl::toString(lmTrial), csCaseInsensitive))
    {
        return lmTrial;
    }
    else if(compareStrings(lms, dsl::toString(lmActivated), csCaseInsensitive))
    {
        return lmActivated;
    }
    else
    {
        return lmUnknown;
    }
}

}
