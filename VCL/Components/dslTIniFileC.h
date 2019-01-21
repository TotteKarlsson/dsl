#ifndef dslTIniFileCH
#define dslTIniFileCH
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <string>
#include <iostream>
#include "dslIniFile.h"

using dsl::KeyList;
using std::string;
using std::ios_base;

namespace dsl
{
	class IniFile;
}
using dsl::IniFile;

class PACKAGE TIniFileC : public TComponent
{
    public:
                               __fastcall   TIniFileC(TComponent* Owner);
                               __fastcall   ~TIniFileC();
        void                   __fastcall   init(const string& fldr = dsl::gEmptyString);
        IniFile*               __fastcall   getFile();
        IniFile*               __fastcall   getIniFile();
        string                 __fastcall   getFullFileName();
        bool                   __fastcall   setFilePath(const String& path);

        //-----------------    Wrapper around mtkIniFile ..
        bool                   __fastcall   load();
        bool                   __fastcall   save(ios_base::openmode openMode = ios::out|ios::trunc);
        bool                   __fastcall   unLoad();
        bool                   __fastcall   wasItFound();
        bool                   __fastcall   sectionExists(const string& section);
        string                 __fastcall   readValue(const string&     key, const string& section = dsl::gEmptyString);
        string                 __fastcall   readString(const string& key, const string& section = dsl::gEmptyString, const string& def_val=dsl::gEmptyString);
        float                  __fastcall   readDouble(const string& key, const string& section = dsl::gEmptyString, double def_val = 0);
        float                  __fastcall   readFloat(const string& key, const string& section = dsl::gEmptyString, double def_val = 0);
        int                    __fastcall   readInteger(const string& key, const string& section = dsl::gEmptyString, int def_val = 0);
        bool                   __fastcall   readBool(const string& key, const string& section = dsl::gEmptyString, bool def_val = false);
//        bool                 __fastcall   writeValue(const string& key, const string& value, const string& comment = dsl::gEmptyString, const string& section = dsl::gEmptyString);
        bool                   __fastcall   writeFloat(const string& key, float value, const string& comment = dsl::gEmptyString, const string& section = dsl::gEmptyString);
        bool                   __fastcall   writeInteger(const string& key, int value, const string& comment = dsl::gEmptyString, const string& section = dsl::gEmptyString);
        bool                   __fastcall   writeBool(const string& key, bool value, const string& comment = dsl::gEmptyString, const string& section = dsl::gEmptyString);
        bool                   __fastcall   writeString(const string& key, const string& value, const string& comment = dsl::gEmptyString, const string& section = dsl::gEmptyString);
        bool                   __fastcall   setKeyComment(const string& key, const string& comment, const string& section = dsl::gEmptyString);
        bool                   __fastcall   setSectionComment(const string& section, const string& comment);

        bool                   __fastcall   deleteSectionsWithKeyValue(const string& key, const string& value);
        bool                   __fastcall   deleteKey(const string& key, const string& section = dsl::gEmptyString);
        bool                   __fastcall   deleteSection(const string& section);
        bool                   __fastcall   createKey(const string& key, const string& value, const string& comment = dsl::gEmptyString, const string& section = dsl::gEmptyString);
        bool                   __fastcall   createSection(const string& section, const string& comment = dsl::gEmptyString);
        bool                   __fastcall   createSection(const string& section, const string& comment, dsl::KeyList keys);
        int                    __fastcall   sectionCount();
        int                    __fastcall   keyCount();
        void                   __fastcall   clear();
        void                   __fastcall   setFileName(const string& fName);
        dsl::IniKey*           __fastcall   getKey(const string& key, const string& section);
        dsl::IniSection*       __fastcall   getSection(const string& section);
        dsl::IniSection*       __fastcall   getSection(const int secNr);
        //---------------      END WRAPPER FUNCTIONS

    private:
        String                              FIniFileName;
        String                              FRootFolder;
        IniFile                             mIniFile;

    protected:
        string                 __fastcall   getIniFileName();
        void                   __fastcall   setIniFileName(String fName);

        string                 __fastcall   getRootFoler();
        void                   __fastcall   setRootFolder(const string& folder);

    __published:
        __property String     IniFileName   = {read=FIniFileName,       write=FIniFileName};
        __property String     RootFolder    = {read=FRootFolder,        write=FRootFolder};
};


#endif
