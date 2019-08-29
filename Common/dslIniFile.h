#ifndef dslIniFileH
#define dslIniFileH
#include "dslObject.h"
#include "dslStringUtils.h"
#include "dslIniSection.h"
#include "dslIniKey.h"
#include "dslConstants.h"
#include <vector>
#include <fstream>
#include <string>
//---------------------------------------------------------------------------

namespace dsl
{

using std::string;
using std::fstream;
using std::ios;
using std::ios_base;

const int MAX_LINE_BUFFER_SIZE = 2048;
class IniKey;
class IniSection;

// IniFile typedefs
typedef std::vector<IniKey*>            KeyList;
typedef std::vector<string>             NonKeyList;
typedef std::vector<IniSection*>        SectionList;
typedef SectionList::iterator           SectionItor;

class DSL_COMMON IniFile : public DSLObject
{

    public:
        // Settings flags.
        int                                     mFlags;
        enum INI_FLAGS                          {ifAutoCreateSections = 0x01, ifAutoCreateKeys = 0x02};

                                                IniFile(const string& fName = gEmptyString, bool autoLoad = false, bool autoSave = false);
        IniFile&                                operator=(const IniFile& rhs){return *this;}

        virtual                                ~IniFile();

        unsigned int                            getNumberOfSections();
        bool                                    loadFromString(const string& iniData);

        // File handling methods
        string                                  getFileName();
        string                                  getFullFileName();
        bool                                    setFilePath(const string& path);
        bool                                    load(const string& fName = dsl::gEmptyString);
        IniSection*                             loadSection(const string& theSection);
        bool                                    save(ios_base::openmode openMode = ios::out|ios::trunc);
        bool                                    unLoad();
        bool                                    wasItFound(); //!Boolean indicating if the last key was found in the ini file
        bool                                    sectionExists(const string& section);

        //Reading
        // ReadValue: Default ac                cess method. Returns the raw string value
        string                                  readValue(const string& Key, const string& Section = dsl::gEmptyString);
        string                                  readString(const string& Key, const string& Section = dsl::gEmptyString, const string& def_val=dsl::gEmptyString);
        double                                  readDouble(const string& Key, const string& Section = dsl::gEmptyString, double def_value = 0);
        float                                   readFloat(const string& Key, const string& Section = dsl::gEmptyString, double def_value = 0);
        int                                     readInteger(const string& Key, const string& Section = dsl::gEmptyString, int def_value = 0);
        bool                                    readBool(const string& Key, const string& Section = dsl::gEmptyString, bool def_value = false);

        //Writing
        bool                                    writeValue(const string& Key, const string& Value, const string& Comment = dsl::gEmptyString, const string& Section = dsl::gEmptyString);
        bool                                    writeFloat(const string& Key, double value, const string& Comment = dsl::gEmptyString, const string& Section = dsl::gEmptyString);
        bool                                    writeInteger(const string& Key, int nValue, const string& Comment = dsl::gEmptyString, const string& Section = dsl::gEmptyString);
        bool                                    writeBool(const string& Key, bool bValue, const string& Comment = dsl::gEmptyString, const string& Section = dsl::gEmptyString);
        bool                                    writeString(const string& Key, const string& Value, const string& Comment = dsl::gEmptyString, const string& Section = dsl::gEmptyString);
        bool                                    writeNonKey(const string& nonKey, const string& Section = dsl::gEmptyString);

        //KeyHandling
        bool                                    setKeyComment(const string& Key, const string& Comment, const string& Section = dsl::gEmptyString);
        bool                                    setSectionComment(const string& Section, const string& Comment);
        bool                                    deleteKey(const string& Key, const string& FromSection = dsl::gEmptyString);
        bool                                    deleteSection(const string& Section);
        bool                                    deleteSectionsWithKeyValue(const string& key, const string& value);
        bool                                    createKey(const string& Key, const string& Value, const string& Comment = dsl::gEmptyString, const string& Section = dsl::gEmptyString);

        //Section stuff
        IniSection*                             createSection(const string& Section, const string& Comment = dsl::gEmptyString);
        IniSection*                             createSection(const string& Section, const string& Comment, KeyList Keys);

        // Utility Methods
        unsigned int                            sectionCount();
        unsigned int                            keyCount();
        unsigned int                            keyCount(const string& section);
        void                                    clear();
        void                                    setFileName(const string& fName);
        string                                  commentStr(string& Comment);
        IniKey*                                 getKey(const string& Key, const string& Section);
		IniSection*                             getSection(unsigned int secNr);
		IniSection*                             getSection(const string& Section, bool create = false);
        StringList								getListOfSections();

		bool                                    clearSection(const string& section);
		bool                                    isModified();


	protected:
		SectionList                             mSections;          // List of sections
		string                                  mIniFileName;       // with full path
		bool                                    mIsDirty;           // Tracks whether or not data has changed.
		bool                                    mWasFound;
		bool                                    mAutoSave;          //Save ini file automatically on destruction

												// When set to true, this will cause SetValue() to create a new section, if
												// the requested section does not allready exist.
		bool                                    mAutoCreateSections;

												// When set to true, this causes SetValue() to create a new key, if the
												// requested key does not allready exist.
		bool                                    mAutoCreateKeys;

        string                                  mCommentIndicators;
        const string                            mEqualIndicator;
        const string                            mWhiteSpace;

                                                // General Purpose Utility Functions
        string                                  getNextWord(string& CommandLine);
        int                                     writeLine(fstream& stream, const char* fmt, ...);
};

}
#endif
