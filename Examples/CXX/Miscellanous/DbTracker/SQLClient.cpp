#ifdef WINDOWS
#ifdef USEPCH
#include "pch.h"
#endif
#pragma hdrstop
#endif
//==============================

#include <iostream>
#include "SQLClient.h"
using namespace std;

SQLClient::SQLClient(const string& _u, const string& _h, const string& _usrp)
    : sqlUserName(_u), sqlHost(_h), sqlPassword(_usrp), connection(use_exceptions), query(&connection)
{
    iniFileSection = "SQL_USER_INFO";
    SetupIniParameters();
}

bool SQLClient::Setup()
{
    SetupTableNames();
    return true;
}

void SQLClient::SetupIniParameters()
{
    iniParameters.push_back(&sqlUserName.Setup("SQL_USER", "<none>"));
    iniParameters.push_back(&sqlHost.Setup("SQL_HOST", "<none>"));
    iniParameters.push_back(&sqlPassword.Setup("SQL_PASSWORD", "<none>"));
    iniParameters.push_back(&sqlDataBase.Setup("SQL_DATABASE", "<none>"));
    iniParameters.push_back(&sqlTable1.Setup("SQL_TABLE1", "<none>"));
}

void SQLClient::SetupTableNames()
{
    string path = GetFilePath(iniFileName);

    table1.SetTableName(sqlTable1);
    table1.SetupFromFile(path + string(sqlTable1) + ".sql");
    sqlTables.push_back(table1);
}

string SQLClient::GetInfo() const
{
    stringstream info;
    info<<"\nSQL User Info ==============================================\n";
    info<<"User Name:\t"<<string(sqlUserName)<<endl;
    info<<"SQL Host:\t"<<string(sqlHost)<<endl;
    info<<"SQL Password:\t"<<string(sqlPassword)<<endl;
    info<<"SQL DataBase:\t"<<string(sqlDataBase)<<endl;
    info<<"SQL Table1:\t"<<string(sqlTable1)<<endl;
    return info.str();
}

bool SQLClient::Connect()
{
    try
    {
        connection.real_connect(DataBase().c_str(), SQLHost().c_str(), UserName().c_str(), Password().c_str());
    }
    catch(BadQuery &er)// handle any connection problems
    {
        stringstream error;
        error << "Error: " << er.error << endl;
        cerr<<error.str();
        return false;
    }
    return true;
}

bool SQLClient::CheckAndCreateTables()
{

    //Check that all required tables are present
    Result res = ExecQuery("SHOW TABLES");
    list<string> tables;
    stringstream outStr;
    outStr << "Nr of existing tables: " << res.size() << "\n";
    outStr.setf(ios::left);

    // The Result class has a read-only Random Access Iterator
    if(query.success())
    {
        for (Result::iterator iter = res.begin(); iter != res.end(); iter++)
        {
            Row row = *iter;
            for(unsigned int col = 0; col < row.size(); col++)
            {
                outStr << setw(10) << row[col].c_str();
                tables.push_back(row[col].c_str());
            }
            outStr << "\n";
        }
    }

    clog<<outStr.str();

    //Check in internal list of tables if all of our tables are there
    list<string>::iterator str_iter;
    for(unsigned int i = 0; i < sqlTables.size(); i++)
    {
        str_iter = find(tables.begin(), tables.end(), (string) sqlTables[i].TableName());
        outStr.str("");
        if (str_iter != tables.end())
        {
            outStr<<"Table " << (*str_iter) << " found." << endl;
            clog<<outStr.str();
        }
        else
        {
            outStr << "Table: "<<sqlTables[i].TableName()<<" not found in database." << endl;
            clog<<(outStr.str());

            //Create this table
            if(!CreateDataBaseTable(sqlTables[i]) )
            {
                outStr.str("");
                outStr<<"The table " << (sqlTables[i].TableName()) << " could not be created.." << endl;
                clog<<outStr.str();
            }
        }
    }
    return true;
}

bool SQLClient::CreateDataBaseTable(const SQLTable& sqlTable)
{
    //Create the query
    stringstream theQuery;
    theQuery<<"CREATE TABLE "<<sqlTable.TableName()<<"(";
    for(int i = 0; i < sqlTable.NrOfFields();i++)
    {
        SQLTableField aField = sqlTable(i);
        theQuery<<aField.GetCreateFieldString();
        if(i < sqlTable.NrOfFields() -2)
            theQuery<<",";

    }
    //If one field has autoincrement, make it a primary key
    string primaryKeys;
    for(int i = 0; i < sqlTable.NrOfFields();i++)
    {
        SQLTableField aField = sqlTable(i);
        if(aField.Key().size() > 0)
        {
            if(primaryKeys.size() == 0)
                primaryKeys += aField.Field();
            else
            {
                primaryKeys = primaryKeys + ", " + aField.Field();
            }
        }
    }

    if(primaryKeys.size())
    {
        primaryKeys = ", PRIMARY KEY(" + primaryKeys;
        primaryKeys += ")";
        theQuery<<primaryKeys;
    }
        theQuery<<");";

    Result res = ExecQuery(theQuery.str());

    if(query.success())
    {
        clog<<"The table :"<<sqlTable.TableName()<<" was created\n";
    }
    else
    {
        clog<<"The table :"<<sqlTable.TableName()<<" was not created!\n";
    }
    clog.flush();
    return true;
}


bool SQLClient::DropDataBaseTable(const string& tableName)
{
    //Create the query
    stringstream theQuery;
    theQuery<<"DROP TABLE "<<tableName<<";";
    Result res = ExecQuery(theQuery.str());

    if(query.success())
    {
        clog<<"The table :"<<tableName<<" was dropped\n";
    }
    else
    {
        clog<<"The table :"<<tableName<<" was not dropped! Did not exist?\n";
    }
    clog.flush();
    return true;
}


Result SQLClient::ExecQuery(const string& qStr)
{
    query.reset();
    query << qStr;
    return query.store();
}

Result SQLClient::QueryResult()
{
    return query.store();
}

bool SQLClient::ReadIniFile(const string& fName, const string& sec)
{
    iniFileName = fName;
    if(sec.size())
        iniFileSection = sec;

    if(!iniFile.Init(fName))
    {
        cerr<<"Could not open ini file: "<<iniFile.GetFilePath()<<endl;
        return false;
    }


       for(unsigned int i = 0; i < iniParameters.size(); i++)
    {
        iniParameters[i]->ReadFromIniFile(iniFile, iniFileSection);
        if(!iniParameters[i]->WasRead())
        {
            //LogError("The Parameter " + m_tIniParameters[i]->GetLabel() + " was not found in the ini file: " + m_tIniFile.GetFilePath() + " under section " + m_sIniFileSection);
            cerr<<("The Parameter " + iniParameters[i]->GetLabel() + " was not found in the ini file: " + iniFile.GetFilePath() + " under section " + string(iniFileSection))<<endl;
        }
    }
    return true;
}


