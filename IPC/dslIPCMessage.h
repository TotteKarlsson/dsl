#ifndef dslIPCMessageH
#define dslIPCMessageH
#include <ostream>
#include "dslIPCData.h"
//---------------------------------------------------------------------------

namespace dsl
{

using std::ostream;
#undef GetMessage

class DSL_IPC IPCMessage : public IPCData
{
    public:
                                                    IPCMessage(int msgID = -1, const string& msgData = gEmptyString, int from_socket = -1);
                                                    IPCMessage(const IPCMessage& rhs);
        int                                         GetCommand()    {return mMessageID;}
        int                                         GetID()         {return mMessageID;}
        int                                         GetMessageID()  {return mMessageID;}
        int                                         GetSocketID()   {return mSocketID;}
        void                                        SetSocketID(int id){mSocketID = id;}
        friend ostream&                             operator << (ostream& stream, IPCMessage& rhs)
        {
            stream << rhs.GetMessage();
            return stream;
        }
        void                                        Empty();

        friend string                               operator + (const string& lhs, IPCMessage& rhs)
        {
            string temp = lhs + rhs.GetMessage();
            return temp;
        }
        IPCMessage&                                 operator +(const string& rhs){  mData = mData + rhs; return *this;}
        IPCMessage&                                 operator =(const string& rhs){  mData = rhs; return *this;}

        operator const                              string()                const {return mData;}
        int                                         GetOrigin()             const {return mSocketID;}
        string                                      GetMessage();
        virtual string                              GetMessageName()        const;
        string                                      GetPackedMessage();
        string                                      GetMessageBody();   //Returns the message without messageID. If message is the messageID, the ID string is returned
        char                                        GetSeparator() const {return mSeparator;}

        bool                                        IsProcessed()            const {return mIsProcessed;}
        void                                        IsProcessed(bool isIt)       {mIsProcessed = isIt;}
        void                                        InsertRecord(const string& record){mRecords.push_back(record);}
        string                                      GetRecord(const unsigned int& rec) const;
        bool                                        UnPack();
        bool                                        Pack();

    protected:
													//The server may need to talk back to a client
        int                             			mSocketID;
        int                             			mMessageID;
        bool                            			mIsProcessed;
};

}
#endif
