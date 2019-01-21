#include <iostream>
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketStream.h"
#include "Poco/StreamCopier.h"

using namespace std;
using namespace Poco::Net;
using namespace Poco;

int main(int argc, char *argv[])
{
    SocketAddress sa("www.moleculix.com", 80);
    StreamSocket socket(sa);
    SocketStream str(socket);
    str << "GET / HTTP/1.1\r\n"
     "Host: www.reddit.com\r\n"
     "\r\n";
    str.flush();

    StreamCopier::copyStream(str, cout);

    system("PAUSE");
}

//
//
//#include <Poco/Net/HTTPClientSession.h>
//#include <Poco/Net/HTTPRequest.h>
//#include <Poco/Net/HTTPResponse.h>
//#include <Poco/StreamCopier.h>
//#include <Poco/Path.h>
//#include <Poco/URI.h>
//#include <Poco/Exception.h>
//#include <iostream>
//#include <string>
//
//using namespace Poco::Net;
//using namespace Poco;
//using namespace std;
//
//int main(int argc, char **argv)
//{
//
//    try
//    {
//        // prepare session
//        string url = "http://www.moleculix.com";
//        URI uri(url);
//        HTTPClientSession session(uri.getHost(), uri.getPort());
//
//        // prepare path
//        string path(uri.getPathAndQuery());
//        if (path.empty())
//            path = "/";
//
//        // send request
//        HTTPRequest req(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
//        session.sendRequest(req);
//
//        // get response
//        HTTPResponse res;
//        cout << res.getStatus() << " " << res.getReason() << endl;
//
//        // print response
//        istream &is = session.receiveResponse(res);
//        StreamCopier::copyStream(is, cout);
//    }
//    catch (DSLException &ex)
//    {
//        cerr << ex.displayText() << endl;
//        return -1;
//    }
//
//    return 0;
//}
//
//

