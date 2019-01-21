#ifndef dslFormSaverH
#define dslFormSaverH
#include <Forms.hpp>
#include <Registry.hpp>
#include <memory>
#include "dslObject.h"
#include "dslIniFile.h"
//---------------------------------------------------------------------------
using dsl::IniFile;

using std::string;
class VCLCOMMON dslFormSaver : dsl::DSLObject
{
    public:
                                        dslFormSaver(TForm* f, const string& iniSection, IniFile* iniFile);
                                        ~dslFormSaver();
        void __fastcall                 ReadPosition();
        void __fastcall                 ReadVisiblity();
        void __fastcall                 Read();
        void __fastcall                 Write();

    private:
        TForm*                          mForm;
        IniFile*                        mIniFile;
        string                          mIniSection;
        void __fastcall                 ReadPositionAndSize();
};

#endif
