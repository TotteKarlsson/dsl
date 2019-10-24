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

typedef SocketWorker* (*CreateWorker)(int port_number, SOCKET connection, void* parent);

class DSL_IPC SocketServer : public Thread, public Socket
{
    public:
                                                    SocketServer(int port_nr = -1);
                                                    ~SocketServer();
        string                                      getServerInfo();
        void                                        setPortNumber(int pNum){mPortNumber = pNum;}    //!<Sets the portNr
        int                                         getPortNumber(){return mPortNumber;}            //!<Returns the portNr

        virtual bool                                start(bool inThread = true);
        void                                        stop();

                                                    // overridden from Thread
        void                                        run();
        void                                        worker();
        string                                      getProcessInfo(string indent);
        void                                        assignParent(void* _parent){mParent = _parent;}

                                                    // Server methods
        void                                        setSocketProtocol(SocketProtocol sp){mSocketProtocol = sp;}
        bool                                        broadcast( const string& msg );
        bool                                        sendToWorker(const string& msg, int socketId);
        bool                                        removeLostConnections();

        size_t                                      getNumberOfClients(){return mWorkerList.size();}

        void                                        setIncomingMessageDelimiters(const char& left, const char& right='\n');

                                                    //Pointer to CreateWorker function..
                                                    //has to be supplied by client application (use the Assign.. function below)
        CreateWorker                                CreateWorkerFunction;
        void                                        assignCreateWorkerFunctionPtr(CreateWorker ptr);
        void                                        shutDown();
        SocketWorker*                               getFirstWorker();
        void                                        retireWorker(SocketWorker* aWorker);

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

