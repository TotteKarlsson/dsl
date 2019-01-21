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
#include "DipoleRotateMessage.h"
#include "mvlinsUtils.h"
#include "Dipole.h"
#include "Vector3D.h"
using namespace mysqlpp;

DBClient::DBClient()
{
    iniFileSection = "SQL_USER_INFO";
    terminateMe = false;
    sqlClient.SetIniFileSection(iniFileSection);
    SetupIniParameters();
}

void DBClient::SetupIniParameters()
{
    iniParameters.push_back(&logFileName.Setup("LOG_FILE_NAME", "dbClient.log"));
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
    if(MVLINSModule::ReadIniFile(fName, ""))
    {
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

void DBClient::HandleIPCMessage(const IPCMessage& msgIn)
{
    //Any output generated in this function is buffered in the msgOutBuffer, emptied by calling WriteIPC
    if(!msgIn.IsEmpty())
    {
                        LogMessage(string("dbClient received message: ") + string(msgIn));
        Dipole* dipole = nullptr;
        stringstream outStr;

        if(msgIn.NrOfRecords() == 10)   //This is a dipole coming in
        {
                        LogMessage("dbClient is processing a dipole");
            dipole = new Dipole(msgIn);
            if(!dipole)
            {
                        LogError("could not create a dipole from message!");
                return;
            }
        }

        string msgRecordZERO = toUpper(msgIn[0]);
        if(toUpper(msgIn[0]) == string("TERMINATE") || toUpper(msgIn[0]) == string("EXIT"))
        {
                        LogMessage("dbClient was told to terminate.");
            terminateMe = true;
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
        else if (toUpper(msgIn[0]) == string("SHOW_DIPOLES"))
        {
                            LogMessage("dbClient is showing its dipoles in the table.");
            Query query = sqlClient.GetQuery();
            query << "select * from "<<sqlClient.GetSQLTableName(0);

            Result res = query.store();  // Query::store() executes the query and returns the results
            int nrOfDipoles = res.size();
            outStr << "Nr of Dipoles: " << nrOfDipoles << endl;
            Result::iterator iter;  // The Result class has a read-only Random Access Iterator
            Row row;
            string aRow;
            vector<Dipole> dipoles(0);
            for (iter = res.begin(); iter != res.end(); iter++)
            {
                row = *iter;
                int cols = row.size();
                aRow.clear();
                for(int col = 0; col < cols; col++)
                {
                    aRow += string(row[col]) + string("\t");
                }
                dipoles.push_back(aRow);
            }

            for (u_int i = 0; i < dipoles.size(); i++)
            {
                outStr <<dipoles[i].AsString() << "\n";
            }
            outStr << endl;
            vector<string> strs = splitString(outStr.str(), "\n");
            for(u_int i = 0; i < strs.size(); i++)
                msgOutBuffer.push_back(strs[i]);

        }
        else    //This message has no handler
        {
            msgOutBuffer.push_back(msgIn);
        }
    }
}


