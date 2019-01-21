#include "Poco/Common.h"
#include "Poco/Data/MySQL/Connector.h"
#include <Poco/Data/MySQL/MySQLException.h>
#include <Poco/Data/SessionFactory.h>
#include "Poco/Data/RecordSet.h"
#include <iostream>
#include <string>
#include "dslLogger.h"

using namespace dsl;
using namespace std;
using namespace Poco::Data;


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
    	string aName = ("tes2t");
        int id(0);
        string now("2016-09-22 14:21:12");

//        Statement stmt(ses);
//        stmt << "INSERT INTO user values(?,?,?)", use(id), use(aName), use(now);
//        stmt.execute();


        Statement select(ses);
        select << "SELECT * FROM user";
        int test = select.execute();

        // create a RecordSet
        RecordSet rs(select);
        std::size_t cols = rs.columnCount();

        // print all column names
        for (std::size_t col = 0; col < cols; ++col)
            std::cout << rs.columnName(col) << std::endl;

        // iterate over all rows and columns
        for (RecordSet::Iterator it = rs.begin(); it != rs.end(); ++it)
            std::cout << *it << " ";
//
//        RecordSet rs(sel);
//
//        bool more = rs.moveFirst();
//        int cols = rs.columnCount();
//        int rows = rs.rowCount();
//
//        while(more)
//        {
//            // print all column names
//            for (std::size_t col = 0; col < cols; ++col)
//            {
//                cout << rs.columnName(col) << std::endl;
//            }
//
//            more = rs.moveNext();
//        }

	std::copy(rs.begin(), rs.end(), std::ostream_iterator<Row>(std::cout));


        shutdown();
    }
	catch (const Poco::Data::MySQL::ConnectionException& e)
    {
        cout << e.message() <<endl;
        return -1;
    }
    catch(const Poco::Data::MySQL::StatementException& e)
    {
        cout << e.message() << endl;
        return -1;
    }
    catch(const Poco::Data::MySQL::MySQLException& e)
    {
        cout << e.message() << endl;
        return -1;
    }
    catch(const Poco::InvalidArgumentException& e)
    {
        cout << e.message() << endl;
        return -1;
    }
}

#pragma comment(lib, "dslCommon.lib")
#pragma comment(lib, "poco_foundation-static.lib")

#pragma comment(lib, "poco_mysql_connector-static.lib")
#pragma comment(lib, "poco_data-static.lib")
#pragma comment(lib, "libmysqlB.lib")
