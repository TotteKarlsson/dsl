#ifndef dslIPCServerH
#define dslIPCServerH
#include <deque>
#include "dslObject.h"
#include "dslIPCMessage.h"
#include "dslIPCMessageProcessor.h"
#include "dslIniFile.h"
#include "dslProperties.h"
#include "dslLogLevel.h"

//We are not using boost threads, only conditions and mutexes
//See http://stackoverflow.com/questions/16443989/warnings-when-compiling-boost-libraries-in-c-builder
//for explanation of the #define
//#define BOOST_THREAD_USE_LIB

//TODO:: use poco thread and mutexes and sockets..

#include <boost/thread/condition.hpp>
#include "dslSocket.h"
#include "dslIPCExporter.h"
#include "dslSocketServer.h"
//---------------------------------------------------------------------------

namespace dsl
{
using std::pair;

class IPCReceiver;
class SocketWorker;

typedef SocketWorker* (*CreateWorker)(int port_number, SOCKET connection, void* parent);
typedef boost::function< void(void) >    					voidCB;
class DSL_IPC IPCServer : public DSLObject
{
    public:
        boost::mutex                                    mListMutex;
        boost::condition                                mListDataArrived;

                                                        IPCServer(int port = 0, const string& iniSection = gEmptyString, CreateWorker createWorkerFPtr = NULL);
                                                        ~IPCServer();

        virtual bool                                    shutDown();
        virtual bool                                    init(int pNumber = -1, CreateWorker createWorkerPtr = NULL);

        size_t                                          getNumberOfClients();
        string                                          getServerInfo();
        void                                            setSocketServer(SocketServer* aServer);
        string                                          getConnectionInfo();
        int                                             servingPort();
        SocketServer&                                   getSocketServer(){return mSocketServer;}

        bool                                            clientRequestResponse(const string& msg, int socketID);
        virtual bool                                    broadcast(const string& msg);
        bool                                            removeLostConnections();
        size_t                                          nrOfMessages(){return mMessages.size();}

        bool                                            request(const string& msg);            	//Post a message to the message list
        bool                                            postRequest(IPCMessage& msg);       	//Post a message to the message list
        virtual void                                    processRequests();
        virtual void                                    processNextRequest();

        virtual bool                                    processRequest(IPCMessage& msg);
        unsigned int                                    numberOfProcessedRequests(){return mNrOfProcessedRequests;}

        bool                                            isRunning();
        bool                                            isProcessorRunning();
        void                                            readProperties(IniFile& iniFile);

        bool                                            start(const int portNumber = -1);
        void                                            stop();

                                                        //Ini Parameter stuff
        virtual bool                                    readIniFile(const string& fileName){return false;}
        bool                                            saveParameters();

                                                        //Pass on factory function to the socker server
        void                                            assignCreateWorkerFunctionPtr(CreateWorker ptr){mCreateWorkerFunction = ptr;}
        bool                                            setLogLevel(LogLevel lvl);
        string                                          getUpTime();
        void                                            setIncomingMessageDelimiters(const char& left, const char& right='\n');
        virtual string                                  getUsage();
        void                                            setSocketProtocol(Socket::SocketProtocol proto = Socket::spTCP);
        bool                                            shutDownServer();
        bool                                            shutDownProcessor();

        SocketClientCallBack                  			onClientConnect;
        SocketClientCallBack                  			onClientDisconnect;

    protected:
        SocketServer                                    mSocketServer;
        pair<char, char>                                mMessageDelimiters;
        time_t                                          mStartTime;

        void                                            privateOnClientConnect(Socket* s);
        void                                            privateOnClientDisconnect(Socket* s);

        unsigned int                                    mNrOfProcessedRequests;
        virtual bool                                    initServer(int pNumber = -1, CreateWorker aCreateIPCWorkerFunction = NULL);
        bool                                            initProcessor();

        deque<IPCMessage>                               mMessages;
        IPCMessageProcessor                             mMessageProcessor;
        Properties                                      mProperties;

        CreateWorker                                    mCreateWorkerFunction;
        string                                          mIniSection;
        Property<int>                                   mServerPort;
        Property<string>                                mServerName;
        Property<Socket::SocketProtocol>                mSocketProtocol;
        bool                                            logProcessResult(IPCMessage& msg);

        virtual bool                                    setupProperties();
        virtual bool                                    readProperties();
        bool                                            sendResponse(const string& response, int origin);
        bool                                            sendResponse(bool  response, int origin);

        //Friends can access our mutexes
        friend                                          IPCReceiver;
        friend                                          IPCMessageProcessor;
        virtual int                                     getMessageID(const string& msg);
};

}
#endif
