#ifndef TLogFileReaderH
#define TLogFileReaderH
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include "dslLogFileReader.h"
//---------------------------------------------------------------------------

class PACKAGE TLogFileReader : public TComponent
{
	public:
    							__fastcall 	TLogFileReader(TComponent* Owner);
    							__fastcall 	~TLogFileReader();
		bool                                start();
		bool                                stop();
        bool                                isRunning();

	protected:
		LogFileReader               		mReader;
		bool                              	FReadFromStart;
		TMemo*                              FLogMemo;
		void 			     	__fastcall	callback();


		virtual TMemo* 		    __fastcall 	getLogMemo(){return FLogMemo;}
		virtual void            __fastcall 	setLogMemo(TMemo* m){FLogMemo = m;}

	__published:
		__property bool 			ReadFromStart= {read = FReadFromStart, 		write = FReadFromStart};
		__property TMemo*			LogFileMemo  = {read = getLogMemo, 			write = setLogMemo};

};

#endif
