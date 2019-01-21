#ifndef SQLClientH
#define SQLClientH
#include "SQLTable.h"
#include "IniFile.h"
#include "MVLINSObject.h"
#include "IniParameter.h"
#include "mysql++.h"

using std::string;
using namespace mysqlpp;
class SQLClient : public MVLINSObject
{
    private:
        IniParameter<string> sqlUserName;
        IniParameter<string> sqlHost;
        IniParameter<string> sqlPassword;
        IniParameter<string> sqlDataBase;
        IniParameter<string> sqlTable1;
        SQLTable table1;

        //!Ini file
        CIniFile iniFile;
        IniParameter<string> iniFileSection;
        IniParameter<string> iniFileName;

        //!Container for the ini parameters
        vector<BaseProperty*> iniParameters;
        void SetupIniParameters();
        Connection connection;                          //A MySQL connection
        Query query;
        vector<SQLTable> sqlTables;
        void SetupTableNames();

    public:
        SQLClient(const string& _u = "", const string& _h = "", const string& _usrp = "");
        virtual ~SQLClient(){}
        bool Setup();
        void SetUserName(const string& name){sqlUserName = name;}
        void SetSQLHost(const string& h){sqlHost = h;}
        void SetPassword(const string& p){sqlPassword = p;}
        void SetDataBase(const string& db){sqlDataBase = db;}
        string GetInfo() const;
        bool ReadIniFile(const string& fName, const string& section = "");
        string SQLHost()  const {return sqlHost;}
        string UserName() const {return sqlUserName;}
        string Password() const {return sqlPassword;}
        string DataBase() const {return sqlDataBase;}

        //Inifile stuff
        void SetIniFileSection(const string& isec){iniFileSection = isec;}

        bool Connect();
        Query GetQuery(){return connection.query();}
        Result ExecQuery(const string& qStr);
        Result QueryResult();
        Connection GetConnection(){return connection;}
        bool CheckAndCreateTables();
        bool CreateDataBaseTable(const SQLTable& table);
        bool DropDataBaseTable(const string& table);
        string GetSQLTableName(int table) const {return (string) sqlTables[table].TableName();}
};

#endif
