#ifndef dslIPCPipeH
#define dslIPCPipeH
#include <windows.h>
#include <string>
#include "dslObject.h"
//---------------------------------------------------------------------------

namespace dsl
{
using namespace std;

const size_t PIPE_BUFSIZE = 1024;

class mtkIPCPipe : public DSLObject
{
	public:
    						        mtkIPCPipe(const string& _pipeName);
		virtual                     ~mtkIPCPipe(void);
		virtual HANDLE              GetPipeHandle(){return mPipeHandle;}
		string                      GetPipeName(){return mPipeName;}
		bool                        DeletePipe();

	protected:
		HANDLE                      mPipeHandle;
		string                      mPipeName;
		string                      CreatePipeName(const string& sPipeName);
};

}
#endif
