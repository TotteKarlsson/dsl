#ifndef SocketH
#define SocketH
#include <deque>
#include <string>
#include <winsock.h>
#include "dslObject.h"
#include "dslIPCExporter.h"
#include "dslProperty.h"
#include <boost/function.hpp>

namespace dsl
{
using std::string;
using std::deque;

#define SERR_NOBIND      3
#define SERR_NOSOCKET    4
#define SERR_UNKNOWNHOST 5

class Socket;
typedef boost::function<void (Socket*)> SocketClientCallBack;
class SocketReceiver;

class DSL_IPC Socket : public DSLObject
{
    public:
        friend SocketReceiver;
        enum                                        SocketAddressFamily { sfUnspec=0,     sfInet  = 2,     sfNetBios = 17};
        enum                                        SocketType          { stStream=1,     stDGram = 2,     stRaw     = 3};
        enum                                        SocketProtocol      { spTCP   =6,     spUDP   = 17,    spRM      = 113};

    public:
                                                    Socket(int socket_handle = -1);
        virtual                                     ~Socket();

        void                                        setSocketProtocol(SocketProtocol proto);
        bool                                        setupSocket();
        int                                         close();
        int                                         receive(long receiveBuffer = 32000);
        int                                         send(const string& msg);
        bool                                        hasHandle();
        bool                                        isConnected();
        int                                         getSocketID();
        int                                         getSocketHandle();
        virtual string                              getRemoteHostName() = 0;
		virtual string                              getLastSentData();

        									        //!Make it simple to consume incoming data
        deque<char>&                                getIncomingDataBuffer();
        string                                      getInfo();
		SocketClientCallBack				        onConnected;
		SocketClientCallBack				        onDisconnected;

		SocketClientCallBack				        onReceiveData;
		SocketClientCallBack				        onSendData;
		string        								getReceivedBufferContent();

    protected:
        SOCKET                                      mSocketHandle;
        bool                                        mIsBroken;
        deque<char>                                 mMessageBuffer;
        WSADATA                                     mWSAData;                     /* Structure for WinSock setup communication */
        SocketAddressFamily                         mSocketAddressFamily;
        SocketType                                  mSocketType;
        SocketProtocol                              mSocketProtocol;

        string                                      mLastSentData;
};

template<> inline
string Property<Socket::SocketProtocol>::getTypeName() const
{
    return "socketProtocol";
}

template<> inline
bool Property<Socket::SocketProtocol>::assignValueFromString(const string& v)
{
    return false;
}

template<> inline
bool Property<Socket::SocketProtocol>::write(IniFile* iniFile, const string& section)
{
    if(&iniFile == nullptr)
    {
        return false;
    }

    string toWrite;
    toWrite = dsl::toString(getValue());
    iniFile->writeString(mKey, toWrite, "", section);
    return true;
}

template<> inline
bool Property<Socket::SocketProtocol>::read(IniFile* iniFile, const string& section)
{
    if(&iniFile == nullptr)
    {
        return false;
    }

    string val(iniFile->readString(mKey, section, dsl::toString(mDefaultValue)));

//    LogLevel tempVal = getLogLevel(val);
//
//    mWasRead = iniFile->wasItFound();
//    setValue( mWasRead ? tempVal : mDefaultValue);
    return mWasRead;
}


}
#endif
