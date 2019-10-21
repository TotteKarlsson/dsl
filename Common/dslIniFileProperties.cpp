#pragma hdrstop
#include "dslIniFileProperties.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------

namespace dsl
{

IniFileProperties::IniFileProperties(IniFile* iniFile, const string& iniSection)
:
Properties(iniSection),
mIniFile(iniFile)
{}

IniFileProperties::~IniFileProperties()
{}

bool IniFileProperties::read()
{
    //The actual ini file should be loaded before parameters are 'read'
    if(!mSectionName.size())
    {
        if(mIniFile)
        {
            Log(lWarning)<<"INI section is not set for parameters using the INI file: "<<mIniFile->getFileName();
        }
        else
        {
            Log(lWarning)<<"INI section and INI file is not setup yet. Can't read!";
            return false;
        }
    }

    Log(lDebug1)<<"Starting reading the INI section: "<<mSectionName;
    if(!mIniFile)
    {
        Log(lError)<<"No INI file is assigned to ini parameter container.";
        return false;
    }

    for(unsigned int i = 0; i < mProperties.size(); i++)
    {
        BaseProperty* para = mProperties[i];
        if(para->doReadFromINI())
        {
            para->read(mIniFile, mSectionName);
            if(!para->wasRead())
            {
                Log(lError)<<"The parameter "<<para->getLabel()<<" was not found in the ini file: "<<mIniFile->getFullFileName()<<" under section \""<<mSectionName << "\"";
                if(mIniFile->createKey(para->getLabel(), para->getValueAsString(), "", mSectionName))
                {
                    Log(lDebug4)<<"The parameter "<<para->getLabel()<<" was created. Default value is :"<<para->getValueAsString();
                }
            }
            else
            {
                //Log(lDebug4)<<"Read INI Key"<< para->getLabel()<<" = "<<para->getValueAsString();
            }
        }
    }

    Log(lDebug1)<<"Finished reading INI section:"<<mSectionName;
    return true;
}

bool IniFileProperties::write()
{
    //This function writes the values to the iniFile.
    //iniFile has to be saved explicitly to save values to file!

    if(mIniFile == nullptr)
    {
		Log(lDebug3) << "No inifile in IniFileProperties -> no saving";
        return false;
    }

    Log(lDebug3) << "Writing section: " << mSectionName;

    for(unsigned int i = 0; i < mProperties.size(); i++)
    {
        if(!mProperties[i]->write(mIniFile, mSectionName))
        {
            Log(lWarning)<<"The Parameter "<<mProperties[i]->getLabel()<<" was not written to the ini file: "<<" under section "<<mSectionName;
        }
        else
        {
            Log(lDebug4)<<mProperties[i]->getLabel()<<" = "<<mProperties[i]->getValueAsString();
        }
    }
    return true;
}

void IniFileProperties::addStringProperty(const string& label, const string& value)
{
	BaseProperty* bp = new Property<string>(value, label);
	add(bp);
}

void IniFileProperties::addIntProperty(const string& label, int value)
{
	BaseProperty* bp = new Property<int>(value, label);
	add(bp);
}

void IniFileProperties::setIniFile(IniFile* iniFile)
{
	mIniFile = iniFile;
}

IniFile* IniFileProperties::getIniFile()
{
	return mIniFile;
}

}
