#ifndef dslLogFileReaderH
#define dslLogFileReaderH
#include <string>
#include <fstream>
#include "dslVCLCommonExporter.h"
#include "dslThread.h"
//---------------------------------------------------------------------------

typedef void __fastcall (__closure *Callback)(void);

class VCLCOMMON LogFileReader : public dsl::Thread
{
	public:
											LogFileReader(const string& fName, Callback AMethod = NULL, bool startAtEnd = true);
		void					            assignOnMessageCallBack(Callback AMethod);
		bool                                reStart();
		void                                worker();
		void                                setFileName(const string& fName);
		string                              getLogFileName();
		bool                                hasData();
		string&                             getData();
		void                                purge();
		void                                run();

	protected:
		ifstream                            mFS;
		bool                                mStartAtFileEnd;
		string                              mFileName;
		string                              mTheData;
		Callback	                        mCallBackFnc;
		bool                                init();
};


#endif
