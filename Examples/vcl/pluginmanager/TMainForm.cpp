#pragma hdrstop
#include "TMainForm.h"
#include "dslException.h"
#include "dslLogger.h"
#include "dslVCLUtils.h"
#include "dslPluginWithEvents.h"
#include "dslPythonPlugin.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTAboutFrame"
#pragma link "dslTLogMemoFrame"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TMainForm *MainForm;

void onPluginStarted(	void* a, 		void* b);
void onPluginProgress(	void* a, 		void* b);
void onPluginExit(		void* a, 		void* b);


using namespace dsl;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TForm(Owner),
    mDSLPython("", "Plugins")
{
    mPythonPM.assignInterpreter(&mDSLPython);
    LogOutput::mShowLogTime = false;
}

__fastcall TMainForm::~TMainForm()
{
	mPythonPM.unloadAll();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::LoadPluginsBtnClick(TObject *Sender)
{
    TButton* b = dynamic_cast<TButton*>(Sender);

    if(b == LoadPluginsBtn)
    {
        loadPythonPlugins();
    }
    else if(b == GetPluginsInfoBtn)
    {
        //Get information about the plugin manager
        Log(lInfo) << PluginManager1->mPM.getInfo();
    }
}

void TMainForm::loadPythonPlugins()
{
	try
	{
        int j = mPythonPM.loadPlugins();
        if(j == 0)
        {
            Log(lInfo) << "No plugins were loaded.";
        }
        else
        {
            Log(lInfo) << "Loaded " << j << " plugins.";
            Log(lInfo) << mPythonPM.getInfo();
            PluginsLB->Clear();

            StringList pl = mPythonPM.getPluginNames();
            for(int i = 0; i < pl.count(); i++)
            {
                Plugin* p = mPythonPM.getPlugin(i);
                Log(lInfo) << "Adding plugin: " << p->getName();

                PluginsLB->AddItem(pl[i].c_str(), (TObject*) p);
            }
        }
    }
	catch(const DSLException& e)
	{
		Log(lError) << "Exception: "<<e.what();
	}
}

void __fastcall TMainForm::FormShow(TObject *Sender)
{
    PluginInfoFrame = new TPluginInfoFrame(NULL, this);
	TLogMemoFrame1->init();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == vkEscape)
	{
		Close();
	}
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
    if(PluginManager1->getNumberOfPlugins())
    {
        CanClose = false;
    }
    else
    {
        CanClose = true;
    }

    if(!CanClose)
    {
	    ShutDownTimer->Enabled = true;
    }
}

void __fastcall TMainForm::ShutDownTimerTimer(TObject *Sender)
{
	ShutDownTimer->Enabled = false;

    if(PluginManager1->getNumberOfPlugins())
    {
		PluginManager1->unLoadAllPlugins();
    }

    Close();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::PythonPluginsLBClick(TObject *Sender)
{
    //Retrieve plugin
    int indx = PluginsLB->ItemIndex;
    if(indx > -1)
    {
        Plugin* p = (Plugin*) PluginsLB->Items->Objects[indx];
        if(p)
        {
            Log(lInfo) << "Examining the plugin: "<<p->getName();
            Log(lInfo) << "\n" << p->getExtendedInfo();

            if(!PluginInfoFrame)
            {
                MessageDlg("Hoops", mtError, TMsgDlgButtons() << mbOK, 0);
            }

            if(PluginInfoFrame->populate(p))
            {
                PluginInfoFrame->Parent = PythonGB;
                PluginInfoFrame->Left = PluginsLB->Left + 100;
                PluginInfoFrame->Align = alClient;
            }

            if(dynamic_cast<PluginWithEvents*>(p))
            {
            	PluginWithEvents* pwe = dynamic_cast<PluginWithEvents*>(p);
            	pwe->assignOnStartedEvent(onPluginStarted, 		this, nullptr);
           	 	pwe->assignOnProgressEvent(onPluginProgress, 	pwe, nullptr);
            	pwe->assignOnFinishedEvent(onPluginExit, 		pwe, nullptr);
            }
        }
    }
}

Plugin* TMainForm::getSelectedPlugin()
{
    int indx = PluginsLB->ItemIndex;
    if(indx > -1)
    {
        Plugin* p = (Plugin*) PluginsLB->Items->Objects[indx];
        return p;
    }
    return nullptr;
}

TPluginInfoFrame* TMainForm::getPluginInfoFrame(Plugin* p)
{
    return PluginInfoFrame;
}


void TMainForm::setLogMemoMessage(UnicodeString Msg)
{
    struct TLocalArgs
    {
        UnicodeString Msg;
        void __fastcall f()
        {
            MainForm->TLogMemoFrame1->infoMemo->Lines->Add(Msg);
        }
    };

    TLocalArgs Args;
    Args.Msg = Msg;
    TThread::Synchronize(NULL, &Args.f);
}

void onPluginStarted(void* a, void* b)
{
    Log(lInfo) << "Plugin called its OnStarted method";
}


//This program assumes that first argument is a PythonPlugin and second is a Property<int>*
void onPluginProgress(void* a, void* b)
{
    Log(lDebug5) << "Plugin calling its OnProgress method";
    PythonPlugin* p = (PythonPlugin*) a;
    if(p)
    {
        Log(lDebug5) << "<CALLBACK> The Plugin: " << p->getName() <<" is progressing";

        //The work started data contain a pointer to the Main Form
        pair<void*, void* > data = p->getWorkStartedData();
        TMainForm* f = (TMainForm*) data.first;
        if(f)
        {
            Property<int>* value = (Property<int>*)b;

            //This need to synchronize with main thread

            f->getPluginInfoFrame(p)->showProgress(value->getValue());
            f->setLogMemoMessage("Test");
	        Log(lDebug5) << "<CALLBACK> Property Value is: "<< value->getValue();
        }
    }
}

void onPluginExit(void* a, void* b)
{
    Log(lInfo) << "Plugin worker exited";

    if(b)
    {
	    Property<int>* p = (Property<int>*) b;
	    Log(lInfo) << "The plugins property: " << p->getLabel() << " value is " << p->getValue();
    }
}



