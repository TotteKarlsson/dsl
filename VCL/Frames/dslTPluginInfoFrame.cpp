#pragma hdrstop
#include "dslTPluginInfoFrame.h"
#include "dslPlugin.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"
#include "dslTIntegerLabeledEdit.h"
#include "dslTFloatLabeledEdit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTSTDStringLabeledEdit"
#pragma link "dslTIntegerLabeledEdit"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

namespace dsl
{
TPluginInfoFrame *PluginInfoFrame;

//---------------------------------------------------------------------------
__fastcall TPluginInfoFrame::TPluginInfoFrame(Plugin* p, TComponent* Owner)
	: TFrame(Owner),
    mPlugin(p)
{
    populate(p);
}

bool TPluginInfoFrame::populate(Plugin* p)
{
    this->Visible = false;
    mPlugin = p;
    if(!mPlugin)
    {
        return false;
    }
   	PluginNameE->setValue(mPlugin->getName());
    Properties* ps = mPlugin->getProperties();
    clearVisualControls();


    for(int i = 0; i < ps->count(); i++)
    {
        BaseProperty* bp = ps->getProperty(i);
        TPanel* backPanel = new TPanel(PropertiesPanel);
        backPanel->AutoSize = false;
        backPanel->Width = 150;
        backPanel->Height = 50;
        backPanel->Padding->Top = 5;
        backPanel->Padding->Bottom = 5;
        backPanel->Padding->Left = 5;
        backPanel->BevelOuter = bvNone;


        TLabeledEdit* e;
		switch(bp->getPropertyType())
        {
            case otInt:
            {
                //Create an integer edit box
                e = new TIntegerLabeledEdit(backPanel);
                ((TIntegerLabeledEdit*) e)->assignExternalProperty(dynamic_cast< Property<int>* >(bp), true);
            }
            break;
            case otDouble:
            {
                //Create an integer edit box
                e = new TFloatLabeledEdit(backPanel);
                ((TFloatLabeledEdit*) e)->assignExternalProperty(dynamic_cast< Property<double>* >(bp), true);
            }
            break;

            case otStdString:
            {
                //Create an integer edit box
                e = new TSTDStringLabeledEdit(backPanel);
				((TSTDStringLabeledEdit*) e)->assignExternalProperty(dynamic_cast< Property<string>* >(bp), true);

                if(bp->getLabel() == "LogFile")
                {
                    string logFile = gLogger.getLogFileName();
                    bp->assignValueFromString(logFile);
                    ((TSTDStringLabeledEdit*) e)->update();
                    backPanel->Width = 500;
                }
            }
            break;
        }


        e->Parent = backPanel;
        e->EditLabel->Caption = vclstr(bp->getLabel());
        e->Align = alBottom;
        mVisualControls.push_back(backPanel);

    }

    for(int i = 0; i < ps->count(); i++)
    {
		mVisualControls[i]->Parent = PropertiesPanel;
    }


   	//PropertiesPanel->Visible = true;
    this->Visible = true;
    return true;
}

bool TPluginInfoFrame::clearVisualControls()
{

    for(int i = 0; i < mVisualControls.size(); i++)
    {
        PropertiesPanel->RemoveControl(mVisualControls[i]);
        delete mVisualControls[i];
    }

    mVisualControls.clear();
}

//---------------------------------------------------------------------------
void __fastcall TPluginInfoFrame::RunningTimerTimer(TObject *Sender)
{
    if(!mPlugin)
    {
		RunningTimer->Enabled = false;
        return;
    }

    if(mPlugin->isWorking())
    {
        WorkerButton->Caption = "Terminate";
    }
    else
    {
        WorkerButton->Caption = "Run";
    }
}

//---------------------------------------------------------------------------
void __fastcall TPluginInfoFrame::WorkerButtonClick(TObject *Sender)
{
	if(WorkerButton->Caption == "Terminate")
    {
        Log(lInfo) << "Terminating Plugin: " << mPlugin->getName();
        mPlugin->terminate();
    }
    else if(WorkerButton->Caption == "Run")
    {
        mPlugin->execute(NULL, true);
        RunningTimer->Enabled = true;
        WorkerButton->Caption = "Terminate";
    }
}

void TPluginInfoFrame::showProgress(int pos)
{
    ProgressBar1->Position = pos;
}

}

