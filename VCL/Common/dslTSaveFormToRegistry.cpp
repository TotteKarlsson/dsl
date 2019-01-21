#pragma hdrstop
#include "dslVCLUtils.h"
#include "dslTSaveFormToRegistry.h"
#pragma package(smart_init)

using std::string;
using namespace dsl;

TSaveFormToRegistry::TSaveFormToRegistry(const string& regSection, const string& formName, TForm* f)
:
mRegistryRoot(regSection),
mFormName(formName),
mForm(f)
{
	mRegistryRoot = joinPath(mRegistryRoot, mFormName);
}

TSaveFormToRegistry::~TSaveFormToRegistry()
{

}

void TSaveFormToRegistry::read()
{
    std::auto_ptr<TRegIniFile> Registry(new TRegIniFile(mRegistryRoot.c_str()));

    bool isFirstTime = Registry->ReadBool("", "IsFirstTime", true);
    if(isFirstTime)
    {
        //Don't bother to read the rest..
        //setup default values and put the form in the middle of the screen
		//mForm->Position = poScreenCenter;
		//mForm->Top = 0;
        //mForm->Left = 0;
        return;
    }

    try
    {
        //If value not in registry, try to use the default settins
        if(mForm->Position != poDefaultPosOnly)
        {
            int top         =   Registry->ReadInteger("", "Top", 0);
            int left        =   Registry->ReadInteger("", "Left", 0);

            //Check that the window is inside the desktop
            if(top < 0 || top > Screen->Height)
            {
                top = 0;
            }

            mForm->Top = top;
            mForm->Left = left;
        }

        if(mForm->BorderStyle != bsToolWindow)
        {
            int height        =   Registry->ReadInteger("", "Height",        mForm->Height);
            int width         =   Registry->ReadInteger("", "Width",         mForm->Width);

            mForm->Height = height;
            mForm->Width = width;

//            //Don't want main form to maximize...
//            if(Application->MainForm != mForm)
//            {
//                mForm->WindowState = (TWindowState) windowState;
//            }
        }
    }
    //Catch errors and ignore them
    //usual case is that the registry did not exist on first run
    catch (...)
    {}
}

void  TSaveFormToRegistry::write()
{
    std::auto_ptr<TRegIniFile> Registry(new TRegIniFile(mRegistryRoot.c_str()));

    Registry->WriteBool("",          "IsFirstTime", false);
    if(mForm->Position != poDefaultPosOnly)
    {
        Registry->WriteInteger("",   "Left",    mForm->Left);
        Registry->WriteInteger("",   "Top",     mForm->Top);
    }

    if(mForm->BorderStyle != bsToolWindow)
    {
        Registry->WriteInteger("",   "Height",         mForm->Height);
        Registry->WriteInteger("",   "Width",          mForm->Width);
//        Registry->WriteInteger("",   "WindowState",    mForm->WindowState);
    }

//    Registry->WriteBool("",          "IsVisible", mForm->Visible);
}


