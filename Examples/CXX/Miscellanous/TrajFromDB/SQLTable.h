#ifndef SQLTableH
#define SQLTableH
#include "MVLINSObject.h"

using std::string;
//using namespace mysqlpp;

class SQLTableField : MVLINSObject
{
    private:
        string table_field;
        string table_type;
        string table_attributes;
        string table_null;
        string table_default;
        string table_extra;
        string table_key;
    public:
        SQLTableField(){}
        SQLTableField(vector<string>& aField);
        string GetTableHeader();
        string GetCreateFieldString();
        bool SetFields(vector<string>& fields);
        virtual ~SQLTableField(){}
        string Field() const {return table_field;}
        string Type() const {return table_type;}
        string Attributes() const {return table_attributes;}
        string Null() const {return table_null;}
        string Default() const {return table_default;}
        string Extra() const {return table_extra;}
        string Key()const {return table_key;}
};

SQLTableField::SQLTableField(vector<string>& aField)
{
    if(aField.size() == 7)
    {
        table_field         = aField[0];
        table_type          = aField[1];
        table_attributes    = (aField[2] == "-" ? string("") : aField[2]);
        table_null          = (aField[3] == "No" ? string("NOT nullptr") : string("nullptr"));
        table_default       = (aField[4] == "-" ? string("") : aField[4]);
        table_extra         = (aField[5] == "-" ? string("") : aField[5]);
        table_key           = (aField[6] == "-" ? string("") : aField[6]);
    }
}

string SQLTableField::GetCreateFieldString()
{
    stringstream toCreate;
    toCreate<< table_field                              <<" ";
    toCreate<< table_type                               <<" ";
    toCreate<< table_attributes                         <<" ";
    toCreate<< table_null                               <<" ";
    toCreate<< "DEFAULT '"<<table_default<<"'"          <<" ";
    toCreate<< table_extra                              <<" ";
    return toCreate.str();
}

class SQLTable : MVLINSObject
{
    private:
        string tableName;
        vector<SQLTableField> tableFields;

    public:
        SQLTable();
        virtual ~SQLTable(){}
        SQLTableField& operator()(int i){return tableFields[i];}
        SQLTableField operator()(int i) const {return tableFields[i];}
        bool SetupFromFile(const string& fName);
        int NrOfFields() const {return tableFields.size();}
        vector<SQLTableField> GetFields() const {return tableFields;}
        string TableName() const {return tableName;}
        void SetTableName(const string& name){tableName = name;}

};

SQLTable::SQLTable()
{}


bool SQLTable::SetupFromFile(const string& fName)
{

    fstream inFile;
    inFile.open(fName.c_str());
    if(!inFile)
    {
        cerr<<"Could not open database table description file..\n";
        return false;
    }

    tableFields.clear();
    //Read line by line.. ignore the first line
    string str;
    getline(inFile, str);
    while(getline(inFile, str)) //Actual file reading
    {
        stringstream fullLine(str);
        string record;

        //Parse each line. Records are seperated by tabs
        vector<string> fields;
        while(getline(fullLine, record,'\t'))
        {
            if(record.size())
                fields.push_back(record);
        }

        SQLTableField aField(fields);
        tableFields.push_back(aField);
    }
    return true;
}

#endif
