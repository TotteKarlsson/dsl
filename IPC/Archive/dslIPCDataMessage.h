#ifndef dslIPCDataMessageH
#define dslIPCDataMessageH
#include "DataProcessing\mtkData.h"
#include "dslIPCMessage.h"
//---------------------------------------------------------------------------

namespace dsl
{

class MTK_DATA mtkIPCDataMessage : public IPCMessage
{
	public:
		mtkIPCDataMessage(mtkComplexData* data);
		~mtkIPCDataMessage(){}
};

}
#endif
