#include <iostream>
#include <string>
#include "Poco/Common.h"
#include "Poco/Data/MySQL/Connector.h"
#include <Poco/Data/MySQL/MySQLException.h>
#include <Poco/Data/SessionFactory.h>
#include "Poco/Data/Session.h"


using namespace Poco::Data::Keywords;
using namespace std;
using namespace Poco::Data;
//using Poco::Data::Session;
//using Poco::Data::Statement;



void init()
{
    MySQL::Connector::registerConnector();
}


void shutdown()
{
    MySQL::Connector::unregisterConnector();
}


int main(int argc, char* argv[])
{
    init();

	try
    {
		string str = "host=127.0.0.1;user=atdb_client;password=atdb123;db=atdb";
	    Poco::Data::Session ses(Poco::Data::SessionFactory::instance().create(Poco::Data::MySQL::Connector::KEY, str ));
    	int count = 0;
        ses << "SELECT COUNT(*) FROM user", into(count), now;
        std::cout << "People in DB " << count;
        shutdown();
    }
	catch (const Poco::Data::MySQL::ConnectionException& e)
    {
        cout << e.message() <<endl;
        return -1;
    }
    catch(const Poco::Data::MySQL::StatementException& e)
    {
        cout << e.what() << endl;
        return -1;
    }
    catch(const Poco::Data::MySQL::MySQLException& e)
    {
        cout << e.what() << endl;
        return -1;

    }
}

#pragma comment(lib, "poco_data-static.lib")
#pragma comment(lib, "poco_foundation-static.lib")
#pragma comment(lib, "poco_mysql_connector-static.lib")
#pragma comment(lib, "libmysqlB.lib")
