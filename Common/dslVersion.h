#ifndef dslVersionH
#define dslVersionH
#include "dslObject.h"
//---------------------------------------------------------------------------

namespace dsl
{

//Class to track an application or library version
class DSL_COMMON Version
{
    public:
                                                Version(const string& version = gEmptyString);
        bool                                    parse(const string& input);
        int                                     getMajor() const;
        int                                     getMinor() const;
        int                                     getPatch() const;
        int                                     getBuild() const;
        string                                  asString(const string& format = gEmptyString) const;

        DSL_COMMON friend bool                  operator < (const Version& l, const Version& r);
        DSL_COMMON friend bool                  operator > (const Version& l, const Version& r);
        DSL_COMMON friend bool                  operator == (const Version& l, const Version& r);
        DSL_COMMON friend ostream&              operator << (ostream& st, const Version& ver);

    private:
        int                                     mMajor;
        int                                     mMinor;
        int                                     mPatch;
        int                                     mBuild;
};

double toDouble(const Version& ver);
}

#endif
