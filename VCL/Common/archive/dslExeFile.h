#ifndef dslExeFileH
#define dslExeFileH
#include <Classes.hpp>
#include "dslObject.h"
//#include "dslFile.h"
#include "dslFileName.h"
#include "VCLCommonExporter.h"

namespace dsl
{

enum MESSAGEHANDLING {IGNOREMESSAGE = 0, CATCHMESSAGE, SHOWMESSAGE};

class VCL_COMMON ExeFile : public DSLObject
{

	public:

                                ExeFile(const string& name = gEmptyString);
	                            ~ExeFile();
//		void                    SetProPerties(const TStringList* list);
		MESSAGEHANDLING         getMessageHandling(){return messageHandling;}
		String 	                getMessageHandlingAsString();
		void 	                setMessageHandling(const MESSAGEHANDLING& msg){messageHandling = msg;}
        bool 	                hasIniFile() const;
        string                  getFileNameNoExtensions() const {return mFileName.getFileNameNoExtension();}
        string                  getFileName()	  const		{return mFileName.getFileName();}
        string                  getPath()		  const		{return mFileName.getPath();}
        string                  getPathAndName()  const			{return mFileName.getPathAndFileName();}
        void                    setFileName(const string& fName){mFileName = fName;}

	private:
        FileName        	    mFileName;			//Keep track of the name and path
//		TStringList*            Properties;        //Use this when reading and writing to the registry
		MESSAGEHANDLING         messageHandling;
//		void                    UpdateStringsFromProperties();
//		void                    FillProperties();
		                        ExeFile(const ExeFile& obj);

};

}
#endif
