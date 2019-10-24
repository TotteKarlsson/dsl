#ifndef dslIPCMessageH
#define dslIPCMessageH
#include <ostream>
#include "dslIPCData.h"
//---------------------------------------------------------------------------

namespace dsl
{

using std::ostream;

class DSL_IPC IPCMessage : public IPCData
{
    public:
                                                    IPCMessage(int msgID = -1, const string& msgData = gEmptyString, int from_socket = -1);
                                                    IPCMessage(const IPCMessage& rhs);
        int                                         getCommand();
        int                                         getID();
        int                                         getMessageID();
        int                                         getSocketID();
        void                                        setSocketID(int id);
        void                                        empty();

        DSL_IPC friend ostream&                     operator << (ostream& stream, IPCMessage& rhs);
        DSL_IPC friend string                       operator + (const string& lhs, IPCMessage& rhs);

        IPCMessage&                                 operator + (const string& rhs);
        IPCMessage&                                 operator = (const string& rhs);

                                                    // return message data
        operator const                              string() const;
        int                                         getOrigin() const;
        string                                      getMessage();
        virtual string                              getMessageName() const;
        string                                      getPackedMessage();

													//Returns the message without messageID. If message is the messageID, the ID string is returned
        string                                      getMessageBody();
        char                                        getSeparator() const;
        bool                                        isProcessed() const;
        void                                        isProcessed(bool isIt);
        void                                        insertRecord(const string& record);
        string                                      getRecord(int rec) const;
        bool                                        unPack();
        bool                                        pack();

    protected:
													//The server may need to talk back to a client
        int                             			mSocketID;
        int                             			mMessageID;
        bool                            			mIsProcessed;
};

}
#endif
