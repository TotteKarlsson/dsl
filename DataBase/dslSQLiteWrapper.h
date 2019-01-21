#ifndef dslSQLiteWrapperH
#define dslSQLiteWrapperH
#include <sstream>
#include <map>
#include "Poco/File.h"
#include "dslSQLite.h"
#include "dslStringList.h"
#include "dslConstants.h"
//---------------------------------------------------------------------------

namespace dsl
{

using std::string;
using std::map;
using std::stringstream;
using dsl::SQLite;
using dsl::StringList;

class DSL_DB SQLiteWrapper
{
    public:
                                    SQLiteWrapper(const string& dbFile = "");
                                   ~SQLiteWrapper();
        bool                        open(const string& dbFileName);
        bool                        isOpen();
        bool                        close();
        virtual string              getInfo();
        virtual bool                create(const string& dbFileName) = 0;

    protected:
        SQLite                      mDB;
        Poco::File                  mDBFile;
		stringstream                mSS;
        map<int, string>            mTables;

};
}
#endif
