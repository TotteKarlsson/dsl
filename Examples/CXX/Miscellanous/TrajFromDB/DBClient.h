//---------------------------------------------------------------------------

#ifndef DBClientH
#define DBClientH
//---------------------------------------------------------------------------
#include <string>
#include <vector>
#include "IPCMessage.h"
#include "MVLINSModule.h"
#include "SQLClient.h"

class Dipole;
class DBClient : public MVLINSModule
{
    private:
        SQLClient sqlClient;                    //Responsible for the MySQL connection, and queries
        void SetupIniParameters();
        bool terminateMe;
        
    public:
        DBClient();
        bool ReadIniFile(const string& fName, const string& section = "");
        bool Setup();
        void HandleIPCMessage(const IPCMessage& msg);
        bool ConnectToDataBase();
        bool CheckAndCreateTables();
        bool TerminateMe(){return terminateMe;}
        SQLClient& GetSQLClient(){return sqlClient;}
};

#endif
