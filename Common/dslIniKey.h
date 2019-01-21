#ifndef dslIniKeyH
#define dslIniKeyH
#include "dslObject.h"
#include "dslStringUtils.h"
#include "dslIniSection.h"
#include <vector>
#include <fstream>
#include <string>
//---------------------------------------------------------------------------

namespace dsl
{

using std::string;

// This class stores the definition of a INI key. A key is a named identifier
// that is associated with a value. It may or may not have a comment.
class DSL_COMMON IniKey : public DSLObject
{
    public:
				                  	        IniKey(const string& key = gEmptyString);
                                            ~IniKey();

        string	                  	        mKey;
        string	                  	        mValue;
        string	                  	        mComment;

        void	                  	        reKey(const string& key);
        string	                  	        asString(const char& delimiter = '\n') const;
        int                                 asBool() const;
        int                                 asInt() const;
        double	                  	        asFloat() const;
        DSL_COMMON
        friend ostream&                     operator<<(ostream& stream, const IniKey& aKey);

    protected:
        void                                setupKey(const string& key);
};

}
#endif
