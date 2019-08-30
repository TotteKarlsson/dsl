#ifndef dslIniSectionFrameH
#define dslIniSectionFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "dslIniSection.h"
#include <Vcl.ExtCtrls.hpp>
#include <list>
//---------------------------------------------------------------------------

using std::list;
using dsl::IniSection;
using dsl::IniKey;
class TLabeledPropertyEdit;

class PACKAGE TIniSectionFrame : public TFrame
{
    __published:
		TGroupBox *SectionGB;
		TFlowPanel *FlowPanel;

    private:
        IniSection*             		mSection;
        list<TLabeledPropertyEdit*>     mEdits;

        void                   	 		addKey(IniKey* key);

    public:
        					__fastcall 	TIniSectionFrame(IniSection* section, TComponent* Owner);
        					__fastcall 	~TIniSectionFrame();
        void                            write();
};

extern PACKAGE TIniSectionFrame *IniSectionFrame;
#endif
