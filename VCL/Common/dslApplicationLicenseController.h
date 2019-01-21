#ifndef dslApplicationLicenseControllerH
#define dslApplicationLicenseControllerH

//#include <System.hpp>
#include <string>
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormat.h"
#include "dslVCLCommonExporter.h"

using Poco::DateTime;
using Poco::Timespan;
using Poco::Timestamp;
using std::string;
//---------------------------------------------------------------------------

namespace dsl
{

enum LicenseMode {lmTrial, lmActivated, lmPreRelease, lmUnknown};
std::string toString(LicenseMode lm);
LicenseMode toLicenseMode(const string& lms);

class VCLCOMMON ApplicationLicenseController
{
    public:
                                        ApplicationLicenseController(const string& registryRoot);
                                        ~ApplicationLicenseController();
        bool                            hasValidLicense();
        LicenseMode                     getLicenseMode();
        bool                            setLicenseMode(LicenseMode mode);
        bool                            isPreRelease();

        bool                            storeActivationKey(const string& key);
        string                          retrieveActivationKey();

        void                            setTrialPeriod(const Poco::Timespan& timeSpan);
        Poco::Timespan                  getTrialPeriod();
        Poco::Timespan                  getTrialPeriodLeft();
        bool                            isTrialModeExhausted();

        void                            isActivated(bool isIt);
        bool                            isActivated();

        void                            hasExpirationDate(bool setit);
        bool                            hasExpirationDate();
        Poco::DateTime                  getExpirationDate();
        void                            setExpirationDate(const Poco::DateTime& exp);

    protected:
        void                            readLicenseInfo();
        bool                            mHasExpirationDate;
        string                          mActivationKey;
        string                          mRegistryRoot;
        LicenseMode                     mLicenseMode;

        //Use UTC times
        Poco::DateTime                  mToday;
        Poco::DateTime                  mFirstExecutionDate;
        Poco::Timespan                  mTrialPeriod;
        Poco::DateTime                  mExpirationDate;
};

}
#endif
