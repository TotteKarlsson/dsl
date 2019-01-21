#include <vcl.h>
#pragma hdrstop
#include "TRigidBodyRotationsFrame.h"
#include "dslRigidBody.h"
#include "dslExplorer.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TRigidBodyRotationsFrame *RigidBodyRotationsFrame;

using namespace dsl;
//---------------------------------------------------------------------------
__fastcall TRigidBodyRotationsFrame::TRigidBodyRotationsFrame(TComponent* Owner)
:
TFrame(Owner),
mTheBody(nullptr),
mExplorer(nullptr)
{}

void TRigidBodyRotationsFrame::setExplorer(Explorer* ex)
{
	mExplorer = ex;
}

void TRigidBodyRotationsFrame::setBody(RigidBody* b)
{
	mTheBody = b;
}


//---------------------------------------------------------------------------
void __fastcall TRigidBodyRotationsFrame::zTBChange(TObject *Sender)
{
	TTrackBar *bar = dynamic_cast<TTrackBar*>(Sender);
	int currentPos = bar->Position;

	Log(lInfo) << "Trackbar position: "<<currentPos;

    const AxisSystem* axes(nullptr);

    if(frameOfRotation->ItemIndex == 0)
    {
        axes = &mExplorer->getWorldAxes();
    }
    else
    {
        axes = &mTheBody->getLocalFrame();
    }

	if(bar == xTB && mTheBody != nullptr)
	{
		static int lastXPos = 0;
		int delta = currentPos - lastXPos;
		Log(lInfo) << "Delta is : "<<delta;

        if(delta > 0 || delta < 0)
        {
		    //Figure out delta...
    		mTheBody->rotateX(delta, axes);
	    	lastXPos = currentPos;
        }
	}
	if(bar == yTB && mTheBody != nullptr)
	{
		static int lastYPos = 0;
		int delta = currentPos - lastYPos;
		Log(lInfo) << "Delta is : "<<delta;

		//Figure out delta...
		mTheBody->rotateY(delta, axes);
		lastYPos = currentPos;
	}

	if(bar == zTB && mTheBody != nullptr)
	{
		static int lastZPos = 0;
		int delta = currentPos - lastZPos;
		Log(lInfo) << "Delta is : "<<delta;

		//Figure out delta...
		mTheBody->rotateZ(delta, axes);
		lastZPos = currentPos;
	}

	if(mExplorer)
	{
		mExplorer->render();
	}
}

void __fastcall TRigidBodyRotationsFrame::xTBExit(TObject *Sender)
{
	Log(lInfo) << "Exit Trackbar position: ";//<<currentPos;
}

//---------------------------------------------------------------------------
void __fastcall TRigidBodyRotationsFrame::ScrollBar1MouseLeave(TObject *Sender)
{
	Log(lInfo) << "Exit Trackbar position: ";//<<currentPos;
}


void __fastcall TRigidBodyRotationsFrame::CheckBox1Click(TObject *Sender)
{
	if(mTheBody != nullptr && mExplorer != nullptr)
	{
		AxisSystem& ax = mTheBody->getLocalFrame();
		if(CheckBox1->Checked)
		{
			AxisSystem& ax = mTheBody->getLocalFrame();
			ExplorerObject* obj = mExplorer->add(ax);
			if(obj)
			{
				obj->setVisibility(true);
			}
		}
		else
		{
			ExplorerObject* obj = mExplorer->getExplorerObject(ax);
			if(obj)
			{
				obj->setVisibility(false);
			}
		}
	}

	if(mExplorer)
	{
		mExplorer->render();
	}
}

