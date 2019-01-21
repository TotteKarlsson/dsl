#ifndef TRigidBodyRotationsFrameH
#define TRigidBodyRotationsFrameH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
namespace dsl
{
	class RigidBody;
	class Explorer;
    class AxisSystem;
}

class TRigidBodyRotationsFrame : public TFrame
{
__published:	// IDE-managed Components
	TTrackBar *xTB;
	TTrackBar *yTB;
	TTrackBar *zTB;
    TRadioGroup *frameOfRotation;
	TCheckBox *CheckBox1;
	void __fastcall zTBChange(TObject *Sender);
	void __fastcall xTBExit(TObject *Sender);
	void __fastcall ScrollBar1MouseLeave(TObject *Sender);
	void __fastcall CheckBox1Click(TObject *Sender);
private:	// User declarations
	dsl::RigidBody*			mTheBody;
	dsl::Explorer*			mExplorer;
    dsl::AxisSystem*        mSystem;

public:		// User declarations
			__fastcall 		TRigidBodyRotationsFrame(TComponent* Owner);
	void					setBody(dsl::RigidBody* b);
	void					setExplorer(dsl::Explorer* ex);
};
//---------------------------------------------------------------------------
extern PACKAGE TRigidBodyRotationsFrame *RigidBodyRotationsFrame;
//---------------------------------------------------------------------------
#endif
