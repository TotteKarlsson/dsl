#ifndef dslFileFilterH
#define dslFileFilterH
#include "Poco/Path.h"
#include "dslObject.h"
#include "dslStringList.h"
//---------------------------------------------------------------------------

namespace dsl
{

using Poco::Path;

enum FILE_FILTER
{
    ffCPPHeaders    = 0x01,
    ffCPPSource     = 0x02,
    ffCPPUnits      = 0x04,
    ffCMakeFiles    = 0x08
};

//Class holding a set of file filters
class DSL_COMMON FileFilter : DSLObject
{
    public:
        DSL_COMMON
        friend ostream&                     operator<<(ostream& os, const FileFilter& ff);

                                            FileFilter(int filter = 0);
        string                              toString() const;
        bool                                containExtension(const string& path) const;
        size_t                              size() const;
        string                              operator[](int index) const;
        bool                                addFilter(unsigned int filter);
        bool                                addFilters(const StringList& filters);

	private:
        StringList                          mFilters;
};

}
#endif
