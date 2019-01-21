#ifndef SocketServerH
#define SocketServerH
#include <string>
#include <list>

//We are not really using boost threads, only conditions and mutexes
//See http://stackoverflow.com/questions/16443989/warnings-when-compiling-boost-libraries-in-c-builder
//for explanation of the #define
#define BOOST_THREAD_USE_LIB

//TODO: Change to use Poco mutex and conditions
#include <boost/thread/mutex.hpp>
#include "dslThread.h"
#include "dslSocket.h"
#include "dslSocketWorker.h"

//TODO: add a worker to broadcast messages
namespace dsl
{

typedef SocketWorker* (*CreateWorker)(int port_number, int connection, void* parent);

class DSL_IPC SocketServer : public Thread, public Socket
{
    public:
                                                    SocketServer(int port_nr = -1);
                                                    ~SocketServer();
        string                                      GetServerInfo();
        void                                        SetPortNumber(int pNum){mPortNumber = pNum;}    //!<Sets the portNr
        int                                         GetPortNumber(){return mPortNumber;}            //!<Returns the portNr

        int                                         Start();
        bool                                        Stop();

                                                    // overridden from Thread
        void                                        run();
        void                                        Worker();
        string                                      GetProcessInfo(string indent);
        void                                        AssignParent(void* _parent){mParent = _parent;}

                                                    // Server methods
        void                                        SetSocketProtocol(SocketProtocol sp){mSocketProtocol = sp;}
        bool                                        Broadcast( const string& msg );
        bool                                        SendToWorker(const string& msg, int socketId);
        bool                                        RemoveLostConnections();

        int                                         GetNumberOfClients(){return mWorkerList.size();}

        void                                        SetIncomingMessageDelimiters(const char& left, const char& right='\n');

                                                    //Pointer to CreateWorker function..
                                                    //has to be supplied by client application (use the Assign.. function below)
        CreateWorker                                CreateWorkerFunction;
        void                                        AssignCreateWorkerFunctionPtr(CreateWorker ptr){CreateWorkerFunction = ptr;}
        void                                        ShutDown();
        SocketWorker*                               GetFirstWorker();
        void                                        RetireWorker(SocketWorker* aWorker);

    protected:
        int                                         mPortNumber;
        char                                        mLeftMessageDelimiter;
        char                                        mRightMessageDelimiter;
        string                                      serverName;
        SocketProtocol                              mSocketProtocol;
        static int                                  serverCount;

                                                    /* Local address */
        struct                                      sockaddr_in mServerAddress;

                                                    /* Client address */
        struct                                      sockaddr_in mClientAddress;

        list<SocketWorker*>                         mWorkerList;

                                                    //Child thread accesses the mWorkerList
        boost::mutex                                mWorkerListMutex;

                                                    //The parent is the object that owns the server
        void*                                       mParent;
        int                                         TCPWorker();
        int                                         UDPWorker();
};

}
#endif

