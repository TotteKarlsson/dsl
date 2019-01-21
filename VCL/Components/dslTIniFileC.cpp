#pragma hdrstop
#include "dslComponentsPackageDefs.h"
#include "dslVCLUtils.h"
#include "dslTIniFileC.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

using namespace dsl;

__fastcall TIniFileC::TIniFileC(TComponent* Owner)
:
TComponent(Owner),
FIniFileName(""),
FRootFolder("."),
mIniFile("")
{
     if(!ComponentState.Contains(csDesigning))
     {}
}

__fastcall TIniFileC::~TIniFileC()
{}

void __fastcall TIniFileC::init(const string& fldr)
{
    if(fldr.size())
    {
        setRootFolder(fldr.c_str());
    }
    else
    {
        string path = getApplicationPath();
        setRootFolder(path);
    }

    setIniFileName(FIniFileName);
}

void __fastcall TIniFileC::setIniFileName(String fName)
{
    if(!ComponentState.Contains(csDesigning))
    {
        if(fName.Length())
        {
            FIniFileName = fName;
            mIniFile.setFileName(getFullFileName());
        }
    }
}

void __fastcall TIniFileC::setRootFolder(const string& folder)
{
    if(!ComponentState.Contains(csDesigning))
    {
        if(folder.size())
        {
            FRootFolder = vclstr(folder);
            mIniFile.setFileName(getFullFileName());
        }
    }
}

bool __fastcall TIniFileC::setFilePath(const String& path)
{
    if(path.Length())
    {
        FRootFolder = path;
        return mIniFile.setFilePath(stdstr(path));
    }
    return false;
}

//---------------------------------------------------------------------------
string __fastcall TIniFileC::getFullFileName()
{
    string fName;
    if(FRootFolder.Length())
    {
        fName =  stdstr(FRootFolder) + "\\";
        fName += stdstr(FIniFileName);
    }
    else
    {
        fName = "";
    }
    return fName;
}

bool __fastcall TIniFileC::load()
{
    return mIniFile.load(getFullFileName());
}

bool __fastcall TIniFileC::save(ios_base::openmode openMode)
{
    return mIniFile.save(openMode);
}

bool __fastcall TIniFileC::unLoad()
{
    return mIniFile.unLoad();
}

//!Boolean indicating if the last key was found in the ini file
bool __fastcall TIniFileC::wasItFound()
{
    return mIniFile.wasItFound();
}

string __fastcall TIniFileC::getIniFileName()
{
    return stdstr(FIniFileName);
}

string __fastcall TIniFileC::getRootFoler()
{
    return stdstr(FRootFolder);
}

IniFile* __fastcall TIniFileC::getFile()
{
    return &mIniFile;
}

IniFile* __fastcall TIniFileC::getIniFile()
{
    return &mIniFile;
}

bool __fastcall TIniFileC::sectionExists(const string& section)
{
    return mIniFile.sectionExists(section);
}

string __fastcall TIniFileC::readValue(const string& key, const string& section)
{
    return mIniFile.readValue(key, section);
}

string __fastcall TIniFileC::readString(const string& key, const string& section, const string& def_val)
{
    return mIniFile.readString(key, section, def_val);
}

float __fastcall TIniFileC::readDouble(const string& key, const string& section, double def_val)
{
    return mIniFile.readDouble(key, section, def_val);
}

float __fastcall TIniFileC::readFloat(const string& key, const string& section, double def_val)
{
    return mIniFile.readFloat(key, section, def_val);
}

int __fastcall TIniFileC::readInteger(const string& key, const string& section, int def_val)
{
    return mIniFile.readInteger(key, section, def_val);
}

bool __fastcall TIniFileC::readBool(const string& key, const string& section, bool def_val)
{
    return mIniFile.readBool(key, section, def_val);
}

//bool __fastcall TIniFileC::WriteValue(const string& key, const string& value, const string& comment const string& section)
//{
//    return mIniFile.WriteValue(key, value, comment, section);
//}

//bool __fastcall TIniFileC::WriteFloat(const string& key, float value, const string& comment const string& section)
//{
//    return mIniFile.WriteFloat(key, value, comment, section);
//}

bool __fastcall TIniFileC::writeInteger(const string& key, int value, const string& comment, const string& section)
{
    return mIniFile.writeInteger(key, value, comment, section);
}

bool __fastcall TIniFileC::writeBool(const string& key, bool value, const string& comment, const string& section)
{
    return mIniFile.writeBool(key, value, comment, section);
}

bool __fastcall TIniFileC::writeString(const string& key, const string& value, const string& comment, const string& section)
{
    return mIniFile.writeString(key, value, comment, section);
}

bool __fastcall TIniFileC::setKeyComment(const string& key, const string& comment, const string& section)
{
    return mIniFile.setKeyComment(key, comment, section);
}

bool __fastcall TIniFileC::setSectionComment(const string& section, const string& comment)
{
    return mIniFile.setSectionComment(section, comment);
}

bool __fastcall TIniFileC::deleteSectionsWithKeyValue(const string& key, const string& value)
{
    return mIniFile.deleteSectionsWithKeyValue(key, value);
}

bool __fastcall TIniFileC::deleteKey(const string& key, const string& section)
{
    return TIniFileC::mIniFile.deleteKey(key, section);
}

bool __fastcall TIniFileC::deleteSection(const string& section)
{
    return mIniFile.deleteSection(section);
}

bool __fastcall TIniFileC::createKey(const string& key, const string& value, const string& comment, const string& section)
{
    return mIniFile.createKey(key, value, comment, section);
}

bool __fastcall TIniFileC::createSection(const string& section, const string& comment)
{
    return mIniFile.createSection(section, comment);
}

bool __fastcall TIniFileC::createSection(const string& section, const string& comment, KeyList keys)
{
    return mIniFile.createSection(section, comment, keys);
}

int    __fastcall TIniFileC::sectionCount()
{
    return mIniFile.sectionCount();
}

int __fastcall TIniFileC::keyCount()
{
    return mIniFile.keyCount();
}

void __fastcall TIniFileC::clear()
{
    mIniFile.clear();
}

void __fastcall TIniFileC::setFileName(const string& fName)
{
    mIniFile.setFileName(fName);
}

IniKey* __fastcall TIniFileC::getKey(const string& key, const string& section)
{
    return mIniFile.getKey(key, section);
}

IniSection* __fastcall TIniFileC::getSection(const string& section)
{
    return mIniFile.getSection(section);
}

IniSection* __fastcall TIniFileC::getSection(const int secNr)
{
    return mIniFile.getSection(secNr);
}


