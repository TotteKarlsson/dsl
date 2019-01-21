#pragma hdrstop
#include "dslVCLUtils.h"
#include "dslFormSaver.h"
#include "dslIniFile.h"
#include "dslLogger.h"
#pragma package(smart_init)

using std::string;
using namespace dsl;
dslFormSaver::dslFormSaver(TForm* f, const string& iniSection, IniFile* iniFile)
    : mForm(f),
    mIniFile(iniFile),
    mIniSection(iniSection)
{}

dslFormSaver::~dslFormSaver(){}

void __fastcall dslFormSaver::ReadPosition()
{
    try
    {
        //IniSection* section = mIniFile->getSection(mIniSection);
        //IniKey* key = section->GetKey("Top");
        //If value not in registry, try to use the default settins
        int left, top, height, width;
        if(mForm->Position != poDefaultPosOnly)
        {
              top         =     mIniFile->readInteger(    "Top", mIniSection, 0);
              left        =     mIniFile->readInteger(    "Left", mIniSection, 0);

              //Check that the form is on the screen!
              mForm->Top = top;
              mForm->Left = left;
        }
    }
    //Catch errors and ignore them
    //usual case is that the iniFile did not exist on first run
    catch (...)
    {}
}

void __fastcall dslFormSaver::Read()
{
    IniSection* section = mIniFile->getSection(mIniSection, true);

    bool isFirstTime = mIniFile->readBool("IsFirstTime", mIniSection, true);
    if(isFirstTime == true)
    {
        //Don't bother to read the rest.. setup default values and put the mForm in the middle of the window
        mForm->Position = poDesktopCenter;

    }
    else
    {
      ReadPositionAndSize();
      ReadVisiblity();
    }
}

void __fastcall dslFormSaver::Write()
{
    mIniFile->writeBool(    "IsFirstTime",  false,          "", mIniSection);
    mIniFile->writeInteger( "Left",         mForm->Left,    "", mIniSection);
    mIniFile->writeInteger( "Top",          mForm->Top,     "", mIniSection);
    mIniFile->writeInteger( "Height",       mForm->Height,  "", mIniSection);
    mIniFile->writeInteger( "Width",        mForm->Width  , "", mIniSection);
    mIniFile->writeBool(    "IsVisible",    mForm->Visible, "", mIniSection);

    if(IsIconic(Application->Handle))
    {
        mIniFile->writeBool("IsIconic",     true, "", mIniSection);
    }
    else
    {
        mIniFile->writeBool("IsIconic",     false, "", mIniSection);
    }
}


void __fastcall dslFormSaver::ReadPositionAndSize()
{
    try
    {
        //If value not in registry, try to use the default settins
        int left, top, height, width;
        if(mForm->Position == poDefaultPosOnly)
        {
            top          =   mIniFile->readInteger("Top",     mIniSection );
            left         =   mIniFile->readInteger("Left",    mIniSection );
            left         =   mIniFile->readInteger("Left",    mIniSection,     mForm->Left);
            left         =   mIniFile->readInteger("Left",    mIniSection,     mForm->Left);

            //Check that the window is inside the desktop
            if(top < 0)
            {
                top = 0;
            }

            if(top > Screen->Height)
            {
                top = 0;
            }
        }

        if(mForm->BorderStyle == bsSizeable || mForm->BorderStyle == bsSizeToolWin)
        {
            top       =     mIniFile->readInteger("Top",     mIniSection,       mForm->Top);
            left      =     mIniFile->readInteger("Left",    mIniSection,     mForm->Left);
            height    =     mIniFile->readInteger("Height", mIniSection,    mForm->Height);
            width     =     mIniFile->readInteger("Width",  mIniSection,    mForm->Width);

            if(width > Screen->Width)
            {
                width = Screen->Width;
            }

            if(height > Screen->Height)
            {
                height = Screen->Height;
            }

            mForm->Height   = height;
            mForm->Width    = width;
        }

        mForm->Top      = top;
        mForm->Left     = left;
    }
    //Catch errors and ignore them
    //usual case is that the registry did not exist on first run
    catch (...)
    {}
}


void __fastcall dslFormSaver::ReadVisiblity()
{
//    bool isIcon     = mIniFile->readBool("IsIconic",  mIniSection,    false);
//    bool isVisible  = mIniFile->readBool("IsVisible",   mIniSection,    true);
//
//    if(isIcon)
//    {
//        Application->MainForm->WindowState = wsMinimized;
//    }
//    else
//    {
//        mForm->Visible = isVisible;
//    }
}



