#ifndef dslIPCModuleH
#define dslIPCModuleH
#include <string>
#include <vector>
#include "dslIniFile.h"
#include "dslProperty.h"
#include "dslIPCMessage.h"
#include "dslObject.h"
//---------------------------------------------------------------------------

namespace dsl
{
using std::string;

class DSL_IPC mtkIPCModule : public DSLObject
{
    public:
        								mtkIPCModule();
        virtual 						~mtkIPCModule();

        //Inifile stuff
        virtual bool 					SetIniFileName(const string& fName){mIniFileName = fName; return true;}
        virtual bool 					ReadIniFile(const string& fName, const string& section);

        void                            UseIniFile(const string& iFile){mIniFileName = iFile;}
        void                            SetIniFileSection(const string& isec){mIniFileSection = isec;}
        string                          GetIniFileName()const {return mIniFileName.getValue();}
        string                          GetIniFileSection() const{return mIniFileSection.getValue();}
        string                          LogFileName(){return mLogFileName.getValue();}

        //Logger stuff
        void 							SetLogFileName(const string& fName);

        //Standard in and out uses the IPCMessage class..
        virtual void 					HandleIPCMessage(const IPCMessage& msg);
        virtual vector<IPCMessage> 		PopMessageBuffer();

    protected:
        IniFile 						mIniFile;
        Property<string>                mIniFileName;
        Property<string>                mIniFileSection;
        Property<string>        		mLogFileName;

        vector<BaseProperty*> 			iniParameters;       //!Container for the ini parameters

        virtual void 					SetupProperties() {}
        vector<IPCMessage> 				msgOutBuffer;       //Empty this one by a call to WriteIPC
        virtual bool 					Setup();
};

}
#endif
