#ifndef DBClientH
#define DBClientH
//---------------------------------------------------------------------------
#include <string>
#include <vector>
#include "IPCMessage.h"
#include "MVLINSModule.h"
#include "SQLClient.h"

class DBClient : public MVLINSModule
{
    private:
        SQLClient sqlClient;                    //Responsible for the MySQL connection, and queries
        void SetupIniParameters();
        bool terminateMe;
        int atCurrentRecord;
        IniParameter<float> refreshTime;
        IniParameter<string> trackCols;
        vector<int> colsToShow;

    public:
        DBClient(const string& iniSection);
        bool ReadIniFile(const string& fName, const string& section = "");
        bool Setup();
        void HandleIPCMessage(const IPCMessage& msg);
        bool ConnectToDataBase();
        bool CheckAndCreateTables();
        bool TerminateMe(){return terminateMe;}
        SQLClient& GetSQLClient(){return sqlClient;}
        vector<string> GetAllRecords();
        void ScrollRecords();
        float GetRefreshTime(){return refreshTime;}
};

#endif
