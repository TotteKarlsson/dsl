#ifndef dslIPCMessageBuilderH
#define dslIPCMessageBuilderH
#include <string>
#include "dslObject.h"
#include "dslIPCExporter.h"
//---------------------------------------------------------------------------

namespace dsl
{

using std::string;

#undef GetMessage
class DSL_IPC IPCMessageBuilder : public DSLObject
{
    public:
                                            IPCMessageBuilder(const char& lDel, const char& rDel = '\n');
        bool                                isBuilding(){return mIsBuilding;}
        bool                                isComplete(){return mHasMessage;}
        void                                reset();
        bool                                build(const char& ch);
        string                              getMessage();
        unsigned int                        getMessageSize(){return mMessage.size();}
        void                                setDelimiters(const char& lDel, const char& rDel = '\n');

    private:
        string                              mMessage;
        char                                mLeftDelimiter;
        char                                mRightDelimiter;
        bool                                mIsBuilding;
        bool                                mHasMessage;

        int                                 mNrOfLeftDel;
        int                                 mNrOfRightDel;
};

}
#endif
