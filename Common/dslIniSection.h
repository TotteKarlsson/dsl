#ifndef dslIniSectionH
#define dslIniSectionH
#include "dslIniKey.h"
#include <vector>
#include <string>

//---------------------------------------------------------------------------

namespace dsl
{

using std::vector;
class IniKey;

typedef vector<IniKey*>                             KeyList;
typedef KeyList::iterator                           KeyItor;
typedef KeyList::const_iterator                     ConstKeyItor;

typedef vector<string>                              NonKeyList;
typedef NonKeyList::iterator                        NonKeyItor;

// This class stores the definition of a section. A section contains any number
// of keys (see IniKeys), and may or may not have a comment.
class DSL_COMMON IniSection : public DSLObject
{
    public:
        string            	                        mName;
        string            	                        mComment;
        KeyList            	                        mKeys;            //vector of pointers to keys
        NonKeyList			                        mNonKeys;         //vector of pointers to non_keys
							                        IniSection();
							                        IniSection(const std::string& nameValueString, const char& sep);
						                            ~IniSection();
        IniKey*				                        createKey(const string& _keyName, const string& Value = gEmptyString, const string& Comment = gEmptyString);
        IniKey*   			                        getKey(int i);
        IniKey*   			                        getKey(const string& keyName, bool create = false);
        IniKey*   			                        getFirst();
        IniKey*   			                        getNext();
        IniKey*                                     operator[](int i);

        size_t             	                        keyCount();
        size_t             	                        nonKeyCount();
        void            	                        clear();
        string    	                                getNonKeysAsString();
        string				                        asString(const char& delimiter) const;

	private:
        bool                                        mIsDirty;
        KeyItor            	                        mKeyIter;            //vector of pointers to keys
};

}
#endif
