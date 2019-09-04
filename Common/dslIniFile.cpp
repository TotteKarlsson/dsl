#pragma hdrstop
#include <float.h>
#include <stdarg.h>
#include <string.h>
#include "dslUtils.h"
#include "dslStringUtils.h"
#include "dslLogger.h"
#include "dslFileUtils.h"
#include "dslIniFile.h"

#ifdef _MSC_VER && _MSC_VER < 1900 
#include <stdio.h>
#include <stdlib.h>

#define snprintf(buf,len, format,...) _snprintf_s(buf, len,len, format, __VA_ARGS__)

#endif
namespace dsl
{

using namespace std;

IniFile::IniFile(const string& szFileName, bool autoLoad, bool autoSave)
:
mFlags(0),
mIniFileName(szFileName),
mIsDirty(false),
mAutoSave(autoSave),
mCommentIndicators(";#"),
mEqualIndicator("="),
mWhiteSpace(" \t\n\r"),
mAutoCreateKeys(true),
mAutoCreateSections(true)
{
    if(mAutoCreateSections)
    {
        mFlags |= ifAutoCreateSections;
    }

    if(mAutoCreateSections)
    {
      mFlags |= ifAutoCreateKeys;
    }

    if(mIniFileName.size() > 2 && autoLoad == true)
    {
        load();    //Load all sections and keys upon creation...
        Log(lDebug3)<<"Loaded INI file: " << mIniFileName;
    }
}

IniFile::~IniFile()
{
//    if (mIsDirty && mAutoSave)
    if (mAutoSave)
    {
        save();
    }
    clear();
}

StringList IniFile::getListOfSections()
{
	StringList sections;
    for(int i = 0; i < mSections.size(); i++)
    {
    	sections.append(mSections[i]->mName);
    }
    return sections;
}


// Resets the member variables to their defaults
void IniFile::clear()
{
    mIsDirty = true;            //A save after clear, will clear the phuysica; file
    for(unsigned int i = 0; i < mSections.size(); i++)
    {
        IniSection* section = mSections[i];
        delete section;
    }
    mSections.clear();
}

bool IniFile::setFilePath(const string& path)
{
    mIniFileName = joinPath(path, getFileNameNoPath(mIniFileName));
    //return (filePathExist(path) ? true : false;
    return true;
}

bool IniFile::clearSection(const string& aSection)
{
    IniSection* section = getSection(aSection);
    if(section)
    {
        section->clear();
        return true;
    }
    return false;
}

// Set's the mFileName member variable. For use when creating the IniFile
// object by hand versus loading it from a file
void IniFile::setFileName(const string& FileName)
{
    if (mIniFileName.size() != 0 && compareNoCase(FileName, mIniFileName) != true)
    {
        mIsDirty = true;
    }
    mIniFileName = FileName;
}

// Attempts to load in the text file. If successful it will populate the
// Section list with the key/value pairs found in the file. Note that comments
// are saved so that they can be rewritten to the file later.
bool IniFile::load(const string& newfName)
{
    if(newfName.size())
    {
        mIniFileName = newfName;
    }

    if(mIniFileName.size() < 1)
    {
        Log(lError)<<"Ini file name is not set!";
        return false;
    }
    else
    {
        Log(lDebug3)<<"Loading IniFile: " <<mIniFileName;
    }

    if(!fileExists(mIniFileName))
    {
        Log(lDebug2)<<"The ini file: \"" <<mIniFileName<<"\" does not exist. It will be created";
        if(!createFile(mIniFileName))
        {
            Log(lError)<<"Failed to create ini file.. returning..";
            return false;
        }
    }

    string fName(mIniFileName);
    fstream file;
    file.open(fName.c_str(), ios::in|ios::out);
    if(file.fail())
    {
        Log(lError)<<"Opening file caused failbit to be set";
    }
    if (!file.is_open() )
    {
        Log(lError)<<"The ini file: '" <<mIniFileName<<"' could not be opened";
        return false;
    }
    else
    {
        bool bDone = false;
        bool bAutoKey = (mFlags & ifAutoCreateKeys)  > 0 ? true : false;
        bool bAutoSec = (mFlags & ifAutoCreateSections) > 0 ? true : false;
        IniSection* pSection = getSection("");

        // These need to be set, we'll restore the original values later.
        mFlags |= ifAutoCreateKeys;
        mFlags |= ifAutoCreateSections;

        char* buffer = new char[MAX_LINE_BUFFER_SIZE];
        int lines = 0;
        while(!bDone)
        {
            string Comment;
            memset(buffer, 0, MAX_LINE_BUFFER_SIZE);
            file.getline(buffer, MAX_LINE_BUFFER_SIZE);
            lines++;

            string Line = buffer;
            trimChars(Line, mWhiteSpace);

            bDone = ( file.eof() || file.bad() || file.fail() );

            if ( Line.find_first_of(mCommentIndicators) == 0 )
            {
                Comment += "\n";
                Comment += Line;
            }
            else if ( Line.find_first_of('[') == 0 ) // Found a section
            {
                Line.erase( 0, 1 );
                Line.erase( Line.find_last_of(']'), 1 );
                pSection = getSection(Line, true);
                Log(lDebug3)<<"Located INI File Section: " + pSection->mName;
                Comment = string("");
            }
            else if ( Line.size() > 0 ) // we have a key, add this key/value pair
            {
                string Comment  = "";
                string Key      = "";
                string Value    = "";

                vector<string> record = splitString(Line, mEqualIndicator + mCommentIndicators);
                if(record.size() > 1)
                {
                    string Comment = "";
                    string Key = trimChars(record[0], mWhiteSpace);
                    string Value = trimChars(record[1], mWhiteSpace);
                    if(record.size() > 2)
                    {
                        Comment = trimChars(record[2], mWhiteSpace);
                    }

                    if(pSection)
                    {
                        writeValue(Key, Value, Comment, pSection->mName);
                        Log(lDebug5)<<Key << " = "  <<Value;
                    }
                    else
                    {
                        //Log(lDebug5)<<Key << " = " << Value;
                        Log(lWarning)<<"No section found for key"<<Key<<". The key was ignored..";
                    }
                    Comment = string("");
                }
                else    //Not a valid Key. Store as a NonKey
                {
                    if(pSection)
                    {
                        writeNonKey(Line, pSection->mName);
                    }
                    Log(lDebug5)<<"Read NonKey on line: " << lines;
                }
            }
        }

        delete [] buffer;

        // Restore the original flag values.
        if(!bAutoKey)
        {
            mFlags &= ~ifAutoCreateKeys;
        }

        if(!bAutoSec)
        {
            mFlags &= ~ifAutoCreateSections;
        }
    }
    file.close();
    return true;
}

bool IniFile::loadFromString(const string& iniData)
{
    stringstream file;
    file<<iniData;
    {
        bool bDone = false;
        bool bAutoKey = (mFlags & ifAutoCreateKeys) > 0 ? true : false;
        bool bAutoSec = (mFlags & ifAutoCreateSections) > 0 ? true : false;

        IniSection* pSection = getSection("");

        // These need to be set, we'll restore the original values later.
        mFlags |= mAutoCreateKeys;
        mFlags |= mAutoCreateSections;

        char* buffer = new char[MAX_LINE_BUFFER_SIZE];
        int lines = 0;
        while(!bDone)
        {
            string Comment;
            memset(buffer, 0, MAX_LINE_BUFFER_SIZE);
            file.getline(buffer, MAX_LINE_BUFFER_SIZE);
            lines++;

            string Line = buffer;
            trimChars(Line, mWhiteSpace);

            bDone = ( file.eof() || file.bad() || file.fail() );

            if ( Line.find_first_of(mCommentIndicators) == 0 )
            {
                Comment += "\n";
                Comment += Line;
            }
            else if ( Line.find_first_of('[') == 0 ) // Found a section
            {
                Line.erase( 0, 1 );
                Line.erase( Line.find_last_of(']'), 1 );
                pSection = getSection(Line, true);
                Log(lDebug3)<<"Located section: " + pSection->mName;
                Comment = string("");
            }
            else if ( Line.size() > 0 ) // we have a key, add this key/value pair
            {
                string Comment = "";
                string Key = "";
                string Value = "";

                vector<string> record = splitString(Line, mEqualIndicator + mCommentIndicators);
                if(record.size() > 1)
                {
                    string Comment = "";
                    string Key = trimChars(record[0], mWhiteSpace);
                    string Value = trimChars(record[1], mWhiteSpace);
                    if(record.size() > 2)
                    {
                        Comment = record[2];
                    }

                    //Log(lDebug5)<<Key << " = "  <<Value;
                    if(pSection)
                    {
                        writeValue(Key, Value, Comment, pSection->mName);
                    }
                    else
                    {
                        Log(lWarning)<<"No section for key"<<Key<<". Key was ignored..";
                    }
                    Comment = string("");
                }
                else    //Not a valid Key. Store as a NonKey
                {
                    if(pSection)
                    {
                        writeNonKey(Key, pSection->mName);
                    }
                    Log(lDebug5)<<"Read NonKey on line: " << lines;
                }
            }
        }

        delete [] buffer;
        // Restore the original flag values.
        if(!bAutoKey)
        {
            mFlags &= ~ifAutoCreateKeys;
        }
        if(!bAutoSec)
        {
            mFlags &= ~ifAutoCreateSections;
        }
    }
    return true;
}

IniSection* IniFile::loadSection(const string& theSection)
{
    IniSection* pSection = nullptr;
    if(mIniFileName.size() < 1)
    {
        Log(lError)<<"Ini file name is not set!";
        return nullptr;
    }
    else
    {
        Log(lDebug3)<<"Loading IniFile: " <<mIniFileName;
    }

    fstream file;
    if(!fileExists(mIniFileName))
    {
        Log(lDebug2)<<"The ini file: \"" <<mIniFileName<<"\" does not exist. It will be created";
    }

    string fName(mIniFileName);
    file.open(fName.c_str(), ios::in|ios::out);
    if(file.fail())
    {
        Log(lError)<<"Opening file caused failbit to be set";
    }
    if (!file.is_open() )
    {
        Log(lError)<<"The ini file: '" <<mIniFileName<<"' could not be opened";
        return nullptr;
    }
    else
    {
        bool bDone = false;
        bool bAutoKey = (mFlags & ifAutoCreateKeys) > 0 ? true : false;
        bool bAutoSec = (mFlags & ifAutoCreateSections) > 0 ? true : false;

        char* buffer = new char[MAX_LINE_BUFFER_SIZE];
        pSection = getSection("");

        // These need to be set, we'll restore the original values later.
        mFlags |= mAutoCreateKeys;
        mFlags |= mAutoCreateSections;

        while(!bDone)
        {
            string Comment;
            memset(buffer, 0, MAX_LINE_BUFFER_SIZE);
            file.getline(buffer, MAX_LINE_BUFFER_SIZE);

            string Line = buffer;
            trimChars(Line, mWhiteSpace);

            bDone = ( file.eof() || file.bad() || file.fail() );

            if ( Line.find_first_of(mCommentIndicators) == 0 )
            {
                Comment += "\n";
                Comment += Line;
            }
            else
            if ( Line.find_first_of('[') == 0 ) // Found a section
            {
                Line.erase( 0, 1 );
                Line.erase( Line.find_last_of(']'), 1 );

                if(theSection == Line)
                {
                    createSection(Line, Comment);
                    pSection = getSection(Line);
                                        Log(lDebug3)<<"Located ini section: " + pSection->mName;
                    Comment = string("");
                    bDone = true;
                }
            }
            else if ( Line.size() > 0 ) // we have a key, add this key/value pair
            {
                string Key = getNextWord(Line);
                string Value = Line;

                if ( Key.size() > 0 && Value.size() > 0 )
                {
                    if(pSection)
                    {
                        writeValue(Key, Value, Comment, pSection->mName);
                                        Log(lDebug3)<<"Read Key " + Key + " Value = " + Value;
                    }
                    else
                    {
                                        Log(lDebug3)<<"Read Key " + Key + " Value = " + Value;
                                        Log(lWarning)<<"No section for key" + Key + ". Key was ignored..";
                    }
                    Comment = string("");
                }
                else    //Not a valid Key. Store as a NonKey
                {
                    if(pSection)
                    {
                        writeNonKey(Key, pSection->mName);
                        Log(lDebug5)<<"Read a NonKey: " + Key;
                    }
                }
            }
        }

        // Restore the original flag values.
        if (!bAutoKey)
        {
            mFlags &= ~ifAutoCreateKeys;
        }
        if (!bAutoSec)
        {
            mFlags &= ~ifAutoCreateSections;
        }
    }
    file.close();
    return pSection;
}

// Attempts to save the Section list and keys to the file. Note that if Load
// was never called (the IniFile object was created manually), then you
// must set the mFileName variable before calling save.
bool IniFile::save(ios_base::openmode openMode)
{
    if (mIniFileName.size() == 0 )
    {
		Log(lError)<<"No INI filename has been set. Can't save..";
        return false;
    }

    string aFName = mIniFileName;
    fstream aFstream(aFName.c_str(), openMode);

    if(aFstream.is_open())
    {
        SectionItor s_pos;
        KeyItor k_pos;
        IniSection* Section;
        IniKey* Key;

        for (s_pos = mSections.begin(); s_pos != mSections.end(); s_pos++)
        {
            Section = (*s_pos);
            bool bWroteComment = false;

            if ( Section->mComment.size() > 0 )
            {
                bWroteComment = true;
                writeLine(aFstream, "\n%s", commentStr(Section->mComment).c_str());
            }

            if ( Section->mName.size() > 0 )
            {
                writeLine(aFstream, "%s[%s]",
                        bWroteComment ? "" : "\n",
                        Section->mName.c_str());
            }

            for (k_pos = Section->mKeys.begin(); k_pos != Section->mKeys.end(); k_pos++)
            {
                Key = (*k_pos);

                if ( Key->mKey.size() > 0 && Key->mValue.size() > 0 )
                {
                    aFstream << Key->mKey <<'='<<Key->mValue;
                    if(Key->mComment.size() > 0 )
                    {
                        aFstream << " ; " << Key->mComment;
                    }
                    aFstream << '\n';
                }
            }
        }
    }
    else
    {
        Log(lError)<<"[IniFile::Save] Unable to save file.";
        return false;
    }

    mIsDirty = false;
    aFstream.flush();
    aFstream.close();
                                Log(lDebug3)<<"IniFile ("<<mIniFileName<<") was saved";
    return true;
}

// Set the comment of a given key. Returns true if the key is not found.
bool IniFile::setKeyComment(const string& mKey, const string& mComment, const string& szSection)
{
    KeyItor k_pos;
    IniSection* pSection = getSection(szSection);

    if(pSection == nullptr )
    {
        return false;
    }

    for(k_pos = pSection->mKeys.begin(); k_pos != pSection->mKeys.end(); k_pos++)
    {
        if (compareNoCase( (*k_pos)->mKey, mKey ) )
        {
            (*k_pos)->mComment = mComment;
            mIsDirty = true;
            return true;
        }
    }
    return false;
}

// Set the comment for a given section. Returns false if the section
// was not found.
bool IniFile::setSectionComment(const string& Section, const string& Comment)
{
    SectionItor s_pos;

    for (s_pos = mSections.begin(); s_pos != mSections.end(); s_pos++)
    {
        string name = (*s_pos)->mName;
        if ( compareNoCase( name , Section ) )
        {
            (*s_pos)->mComment = Comment;
            mIsDirty = true;
            return true;
        }
    }
    return false;
}

bool IniFile::sectionExists(const string& section)
{
    for (SectionItor s_pos = mSections.begin(); s_pos != mSections.end(); s_pos++)
    {
        IniSection* iSection = (*s_pos);
        if(iSection && iSection->mName == section)
        {
            return true;
        }
    }
    return false;
}

// Given a key, a value and a section, this function will attempt to locate the
// Key within the given section, and if it finds it, change the keys value to
// the new value. If it does not locate the key, it will create a new key with
// the proper value and place it in the section requested.
bool IniFile::writeValue(const string& mKey, const string& mValue, const string& mComment, const string& szSection)
{
    IniKey*         pKey         = getKey(mKey, szSection);
    IniSection*     pSection     = getSection(szSection);

    if (pSection == nullptr)
    {
        if ( !(mFlags & ifAutoCreateSections) || !createSection(szSection))
        {
            return false;
        }

        pSection = getSection(szSection);
    }

    // Sanity check...
    if (pSection == nullptr )
    {
        return false;
    }

    // if the key does not exist in that section, and the value passed
    // is not string("") then add the new key.
    bool isAutoCreateTrue = (mFlags & ifAutoCreateKeys) > 0 ? true : false;

    if (pKey == nullptr && mValue.size() > 0 && (mFlags & ifAutoCreateKeys))
    {
        pKey = new IniKey;
        pKey->mKey = mKey;
        pKey->mValue = mValue;
        pKey->mComment = mComment;
        mIsDirty = true;
        pSection->mKeys.push_back(pKey);
        return true;
    }

    if (pKey != nullptr)
    {
        pKey->mValue = mValue;
        pKey->mComment = mComment;
        mIsDirty = true;
        return true;
    }
    return false;
}

bool IniFile::writeNonKey(const string& nonKey, const string& section)
{
    IniSection*     pSection     = getSection(section);
    if(pSection == nullptr)
    {
        if ( !(mFlags & ifAutoCreateSections) || !createSection(section))
        {
            return false;
        }

        pSection = getSection(section);
    }

    // Sanity check...
    if(pSection == nullptr)
    {
        return false;
    }

    pSection->mNonKeys.push_back(nonKey);
    return true;
}

// Passes the given float to WriteValue as a string
bool IniFile::writeFloat(const string& key, double value, const string& comment, const string& section)
{
    string v = toString(value);
    return writeValue(key, v, comment, section);
}

// Passes the given int to writeValue as a string
bool IniFile::writeInteger(const string& mKey, int nValue, const string& mComment, const string& szSection)
{
    char szStr[64];
    snprintf(szStr, 64, "%d", nValue);
    return writeValue(mKey, szStr, mComment, szSection);
}

// Passes the given bool to writeValue as a string
bool IniFile::writeBool(const string& mKey, bool bValue, const string& mComment, const string& szSection)
{
    string mValue = bValue ?  "true" : "false";
    return writeValue(mKey, mValue, mComment, szSection);
}

// Returns the key value as a string object. A return value of
// string("") indicates that the key could not be found.
string IniFile::readValue(const string& mKey, const string& szSection)
{
    IniKey* pKey = getKey(mKey, szSection);
      mWasFound = pKey ? true : false;
    string value;
    if(pKey)
    {
        value = pKey->mValue;
    }
    else
    {
        value = "";
    }
    return value;
}

// Returns the key value as a string object. A return value of
// string("") indicates that the key could not be found.
string IniFile::readString(const string& mKey, const string& szSection, const string& def_val)
{
    string     str =  readValue(mKey, szSection);
    if(mWasFound)
    {
        return str;
    }
    return def_val;
}

// Returns the key value as a double type. Returns FLT_MIN if the key is
// not found.
double IniFile::readDouble(const string& mKey, const string& szSection, double def_value)
{
    string mValue = readValue(mKey, szSection);
    if(mWasFound)
    {
        return atof( mValue.c_str() );
    }
    return def_value;
}

// Returns the key value as an integer type. Returns INT_MIN if the key is
// not found.
int    IniFile::readInteger(const string& mKey, const string& szSection, int def_val)
{
    string mValue = readValue(mKey, szSection);
    if(mWasFound)
    {
        return    atoi(mValue.c_str());
    }
    return def_val;
}

// Returns the key value as a bool type. Returns false if the key is
// not found.
bool IniFile::readBool(const string& mKey, const string& szSection, bool def_value)
{
    bool bValue = def_value;
    string mValue = readValue(mKey, szSection);
    if(mWasFound)
    {
        if ( mValue.find("1")                         == 0
                || compareNoCase(mValue, "true")
                || compareNoCase(mValue, "yes")     )
        {
            bValue = true;
        }
        else
        {
            bValue = false;
        }
    }
    return bValue;
}

// Delete a specific section. Returns false if the section cannot be
// found or true when sucessfully deleted.
bool IniFile::deleteSection(const string& Section)
{
    SectionItor s_pos;
    for (s_pos = mSections.begin(); s_pos != mSections.end(); s_pos++)
    {
        if (compareNoCase( (*s_pos)->mName, Section ) )
        {
            //Found a section..
            IniSection *aSection =  (*s_pos);
            mSections.erase(s_pos);
            delete (aSection);
            return true;
        }
    }
    return false;
}

bool IniFile::deleteSectionsWithKeyValue(const string& keyName, const string& value)
{
    //First find sections containing the key
    SectionItor s_pos = mSections.begin();
    s_pos = mSections.begin();
    while (s_pos != mSections.end())
    {
        IniKey* key = getKey(keyName, (*s_pos)->mName);
        {
            if(key && key->mValue == value)
            {
                   //remove section
                deleteSection((*s_pos)->mName);
                s_pos = mSections.begin();
            }
            else
            {
                ++s_pos;
            }
        }
    }
    return true;
}

// Delete a specific key in a specific section. Returns false if the key
// cannot be found or true when sucessfully deleted.
bool IniFile::deleteKey(const string& Key, const string& FromSection)
{
    KeyItor k_pos;
    IniSection* pSection;
    if ( (pSection = getSection(FromSection)) == nullptr )
        return false;
    for (k_pos = pSection->mKeys.begin(); k_pos != pSection->mKeys.end(); k_pos++)
    {
        if ( compareNoCase( (*k_pos)->mKey, Key ) )
        {
            IniKey* aKey = (*k_pos);
            pSection->mKeys.erase(k_pos);
            delete aKey;
            return true;
        }
    }
    return false;
}

// Given a key, a value and a section, this function will attempt to locate the
// Key within the given section, and if it finds it, change the keys value to
// the new value. If it does not locate the key, it will create a new key with
// the proper value and place it in the section requested.
bool IniFile::createKey(const string& mKey, const string& mValue, const string& mComment, const string& szSection)
{
    bool bAutoKey = (mFlags & ifAutoCreateKeys) > 0 ? true : false;
    bool bReturn  = false;

    mFlags |= mAutoCreateKeys;

    bReturn = writeValue(mKey, mValue, mComment, szSection);
    if (!bAutoKey)
    {
        mFlags &= ~ifAutoCreateKeys;
    }
    return bReturn;
}

// Given a section name, this function first checks to see if the given section
// allready exists in the list or not, if not, it creates the new section and
// assigns it the comment given in mComment.  The function returns true if
// sucessfully created, or false otherwise.
IniSection* IniFile::createSection(const string& Section, const string& mComment)
{
    IniSection* pSection = getSection(Section);
    if ( pSection )
    {
        Log(lDebug5)<<"[IniFile::CreateSection] Section "<<Section.c_str()<<" already exists. Aborting.";
        return nullptr;
    }
    pSection = new IniSection(*this);
    pSection->mName = Section;
    pSection->mComment = mComment;
    mSections.push_back(pSection);
    mIsDirty = true;
    return pSection;
}

// Given a section name, this function first checks to see if the given section
// allready exists in the list or not, if not, it creates the new section and
// assigns it the comment given in mComment.  The function returns true if
// sucessfully created, or false otherwise. This version accpets a KeyList
// and writes up the newly created Section with the keys in the list.
IniSection* IniFile::createSection(const string& Section, const string& Comment, KeyList Keys)
{
    if ( !createSection(Section, Comment) )
    {
        return nullptr;
    }

    IniSection* pSection = getSection(Section);
    if (!pSection )
    {
        return nullptr;
    }

    KeyItor k_pos;
    pSection->mName = Section;
    for (k_pos = Keys.begin(); k_pos != Keys.end(); k_pos++)
    {
        IniKey* pKey = new IniKey;
        pKey->mComment = (*k_pos)->mComment;
        pKey->mKey = (*k_pos)->mKey;
        pKey->mValue = (*k_pos)->mValue;
        pSection->mKeys.push_back(pKey);
    }
    mSections.push_back(pSection);
    mIsDirty = true;
    return pSection;
}

// Simply returns the number of sections in the list.
unsigned int IniFile::sectionCount()
{
    return mSections.size();
}

// Returns the total number of keys contained within all the sections.
unsigned int IniFile::keyCount()
{
    int nCounter = 0;
    SectionItor s_pos;
    for (s_pos = mSections.begin(); s_pos != mSections.end(); s_pos++)
        nCounter += (*s_pos)->mKeys.size();
    return nCounter;
}

unsigned int IniFile::keyCount(const string& section)
{
    //Get the section
    IniSection* iniSection = getSection(section);
    return iniSection->keyCount();
}

// Given a key and section name, looks up the key and if found, returns a
// pointer to that key, otherwise returns nullptr.
IniKey* IniFile::getKey(const string& Key, const string& Section)
{
    IniSection* pSection;
    KeyItor k_pos;
    // Since our default section has a name value of string("") this should
    // always return a valid section, wether or not it has any keys in it is
    // another matter.
    if ( (pSection = getSection(Section)) == nullptr )
    {
        return nullptr;
    }

    for (k_pos = pSection->mKeys.begin(); k_pos != pSection->mKeys.end(); k_pos++)
    {
        if ( compareNoCase( (*k_pos)->mKey, Key ) )
        {
            return (*k_pos);
        }
    }
    return nullptr;
}

// Given a section name, locates that section in the list and returns a pointer
// to it. If the section was not found, returns nullptr
IniSection* IniFile::getSection(const string& Section, bool create)
{
    SectionItor s_pos;
    for (s_pos = mSections.begin(); s_pos != mSections.end(); s_pos++)
    {
        if(s_pos == mSections.end())
        {
            return nullptr;
        }
        string secName = (*s_pos)->mName;
        if ( compareNoCase( secName, Section ) )
        {
            IniSection* sec = (*s_pos);
            return sec;
        }
    }
    if(create)
    {
        createSection(Section);
        return getSection(Section, false);
    }
    return nullptr;
}

IniSection* IniFile::getSection(unsigned int sectionNr)
{
    if(sectionNr < mSections.size() && mSections.size() > 0)
    {
        return mSections[sectionNr];
    }
    return nullptr;
}

string IniFile::commentStr(string& mComment)
{
    string szNewStr = string("");
    trimChars(mComment, mWhiteSpace);
    if ( mComment.size() == 0 )
    {
        return mComment;
    }

    if ( mComment.find_first_of(mCommentIndicators) != 0 )
    {
        szNewStr = mCommentIndicators[0];
        szNewStr += " ";
    }
    szNewStr += mComment;
    return szNewStr;
}

// Given a key+delimiter+ value string, pulls the key name from the string,
// deletes the delimiter and alters the original string to contain the
// remainder.  Returns the key
string IniFile::getNextWord(string& CommandLine)
{
    size_t nPos = CommandLine.find_first_of(mEqualIndicator);
    string sWord = string("");
    if ( nPos > -1 )
    {
        sWord = CommandLine.substr(0, nPos);
        CommandLine.erase(0, nPos+1);
    }
    else
    {
        sWord = CommandLine;
        CommandLine = string("");
    }
    trimChars(sWord, mWhiteSpace);
    return sWord;
}

// writes the formatted output to the file stream, returning the number of
// bytes written.
int IniFile::writeLine(fstream& stream, const char* fmt, ...)
{
    char *buf = new char[MAX_LINE_BUFFER_SIZE];
    int nLength;
    string szMsg;

    memset(buf, 0, MAX_LINE_BUFFER_SIZE);
    va_list args;

    va_start (args, fmt);
      nLength = vsnprintf(buf, MAX_LINE_BUFFER_SIZE, fmt, args);
    va_end (args);

    if ( buf[nLength] != '\n' && buf[nLength] != '\r' )
        buf[nLength++] = '\n';

    stream.write(buf, nLength);

    delete [] buf;
    return nLength;
}

unsigned int IniFile::getNumberOfSections()
{
    return (int) mSections.size();
}

string IniFile::getFileName()
{
    return getFileNameNoPath(mIniFileName);
}

string IniFile::getFullFileName()
{
    return mIniFileName;
}

bool IniFile::unLoad()
{
    return save();
}

bool IniFile::wasItFound()//!Boolean indicating if the last key was found in the ini file
{
    return mWasFound;
}

float IniFile::readFloat(const string& Key, const string& Section, double def_value)
{
    return (float) readDouble(Key, Section, def_value);
}

bool IniFile::writeString(const string& Key, const string& Value, const string& Comment, const string& Section)
{
    return IniFile::writeValue(Key, Value, Comment, Section);
}

bool IniFile::isModified()
{
    return mIsDirty;
}
}
