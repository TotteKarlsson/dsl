#ifdef WINDOWS
#ifdef USEPCH
#include "pch.h"
#endif
#pragma hdrstop
#endif
//==============================
#include <iomanip>
#include "StringExtensions.h"
#include "DBClient.h"
#include "mvlinsUtils.h"

using namespace mysqlpp;

DBClient::DBClient(const string& iniSection) : atCurrentRecord(0), terminateMe(false)
{
    iniFileSection = iniSection;
    sqlClient.SetIniFileSection(iniFileSection);
    SetupIniParameters();
}

void DBClient::SetupIniParameters()
{
    iniParameters.push_back(&logFileName.Setup("LOG_FILE_NAME", "dbClient.log"));
    iniParameters.push_back(&refreshTime.Setup("REFRESH_TIME", 1));
    iniParameters.push_back(&trackCols.Setup("TRACK_COLS", "1"));
}

bool DBClient::Setup()
{
    SetLogFileName(logFileName);
    MVLINSModule::Setup();      //Setup in base class
    sqlClient.Setup();
    return true;
}

bool DBClient::ReadIniFile(const string& fName, const string& section)
{
    if(section.size())
        iniFileSection = section;

    if(MVLINSModule::ReadIniFile(fName, iniFileSection))
    {
        //Parse the cols to show to real numbers
        vector<string> cols = splitString(trackCols,",");
        for(int i = 0; i < cols.size(); i++)
        {
            colsToShow.push_back(toInt(cols[i]));
        }

        return sqlClient.ReadIniFile(iniFileName);
    }
    return false;
}

bool DBClient::ConnectToDataBase()
{
    if(!sqlClient.Connect())
    {
                    LogMessage("The sqlClient could not connect to database using parameters: ");
        stringstream str;
        str <<"User: "<<sqlClient.UserName()<<"\n"
            <<"Host: "<<sqlClient.SQLHost()<<"\n"
            <<"DataBase: "<<sqlClient.DataBase()<<"\n"
            <<"Password: "<<sqlClient.Password()<<endl;
                    LogMessage(str.str());
        return false;
    }
    string time = GetFormattedDateTimeString("%H:%M:%S on %x");
                    LogMessage("sqlClient connected to database at: " + string(time));
    return true;
}

bool DBClient::CheckAndCreateTables()
{
    try
    {
        if(!sqlClient.CheckAndCreateTables())
        {
                    LogMessage("Some tables missin in database. Trying to create them..");
        }

    }
    catch (BadQuery &er)
    {
        // handle any connection problems
        stringstream error;
        error << "Error: " << er.error << endl;
        LogError(error.str());
        return false;
    }
                    LogMessage("Database table check succesfull!");
    return true;
}

vector<string> DBClient::GetAllRecords()
{
                LogMessage("dbClient is retrieving all records..");
    Query query = sqlClient.GetQuery();
    query << "select * from "<<sqlClient.GetSQLTableName(0);    // You can write to the query object like you would any other ostrem
    Result res = query.store();                                 // Query::store() executes the query and returns the results
    Row row;
    Result::iterator iter;                                      // The Result class has a read-only Random Access Iterator
    stringstream outStr;
    for (iter = res.begin(); iter != res.end(); iter++)
    {
        row = *iter;
        int cols = row.size();
        outStr.clear();
        for(int col = 0; col < cols; col++)
        {
            if(find(colsToShow.begin(), colsToShow.end(), col+1))
                outStr << setw(10) << row[col].c_str();
        }
        outStr<<"\n";
    }

    //Now parse each string to record
    vector<string> records = splitString(outStr.str(),"\n");
    return records;
}

void DBClient::ScrollRecords()
{
                LogMessage("dbClient is checking for new records..");
    Query query = sqlClient.GetQuery();
    query << "select * from "<<sqlClient.GetSQLTableName(0)<<" WHERE dipole_id > "<<toString(atCurrentRecord);
    Result res = query.store();
    Row row;
    Result::iterator iter;
    stringstream outStr;
    for (iter = res.begin(); iter != res.end(); iter++)
    {
        row = *iter;
        int cols = row.size();
        outStr.clear();
        for(int col = 0; col < cols; col++)
        {
            if(find(colsToShow.begin(), colsToShow.end(), col+1) != colsToShow.end())
                outStr << setw(10) << row[col].c_str();
        }
        outStr<<"\n";
    }

    vector<string> records = splitString(outStr.str(),"\n");
    for(int i = 0; i < records.size(); i++)
    {
        msgOutBuffer.push_back(records[i]);
        atCurrentRecord++;  //Each time a record is sent to the outBuffer, increase current record..
    }
}

void DBClient::HandleIPCMessage(const IPCMessage& msgIn)
{
    //Any output generated in this function is buffered in the msgOutBuffer, emptied by calling WriteIPC
    if(!msgIn.IsEmpty())
    {
                        LogMessage(string("dbClient received message: ") + string(msgIn));
        stringstream outStr;

        string msgRecordZERO = toUpper(msgIn[0]);
        if(toUpper(msgIn[0]) == string("TERMINATE") || toUpper(msgIn[0]) == string("EXIT"))
        {
                        LogMessage("dbClient was told to terminate.");
            terminateMe = true;
        }
        else if (toUpper(msgIn[0]) == string("UPDATE"))
        {
            ScrollRecords();
        }
        else if (toUpper(msgIn[0]) == string("CLEAR_LOG"))
        {
                        LogMessage("dbClient is clearing the log file.");
            ClearLogFile();
        }
        else if (toUpper(msgIn[0]) == string("CLEAR_DB"))
        {
                        LogMessage("dbClient is truncating its database table.");
                sqlClient.ExecQuery("TRUNCATE TABLE " + sqlClient.GetSQLTableName(0));
        }
        else if (msgRecordZERO == string("SHOW_DB") || msgRecordZERO == string("SHOW_TABLES"))
        {
                        LogMessage("dbClient is showing its database table.");
            Query query = sqlClient.GetQuery();

            query << "select * from "<<sqlClient.GetSQLTableName(0); // You can write to the query object like you would any other ostrem
            Result res = query.store();  // Query::store() executes the query and returns the results

            outStr << "Contents of the database table: "<<sqlClient.GetSQLTableName(0)<<"\n";
            outStr << "Nr of Records: " << res.size() << "\n";
            Row row;
            outStr.setf(ios::left);
            Result::iterator iter;  // The Result class has a read-only Random Access Iterator
            for (iter = res.begin(); iter != res.end(); iter++)
            {
                row = *iter;
                int cols = row.size();
                for(int col = 0; col < cols; col++)
                {
                    outStr << setw(10) << row[col].c_str();
                }
                outStr << "\n";
            }
            msgOutBuffer.push_back(outStr.str());
        }
        else    //This message has no handler
        {
            msgOutBuffer.push_back(msgIn);
        }
    }
}

