#ifndef dslIPCDataH
#define dslIPCDataH
#include <vector>
#include <string>
#include "dslObject.h"
#include "dslIPCMessageEnums.h"

namespace dsl
{

using std::string;
using std::vector;
class DSL_IPC IPCData : public DSLObject
{
    public:
                                                    IPCData(short id);
                                                    IPCData(const string& data = dsl::gEmptyString, const char& sep = '|');
                                                    IPCData(const IPCData& rhs);
        virtual                                     ~IPCData();

        bool                                        init();
        vector<string>::iterator                    iterator()                         {return (mRecordIterator);}
        void                                        resetIterator()                    {(mRecordIterator) = mRecords.begin();}
        vector<string>::iterator                    begin()                            {return mRecords.begin();}
        vector<string>::iterator                    end()                              {return mRecords.end();}
        void                                        inrementIterator()                 {mRecordIterator++;}
        string                                      getNextRecord();
        string                                      getData() const                    {return mData;}
        int                                         getNumberOfRecords()               {return mRecords.size();}
        virtual bool                                hasData() const;
        virtual bool                                unPack();
        virtual bool                                pack();
        bool                                        isPacked() const;
        void                                        addData(const string& data)        {mData += data;}
        void                                        addRecord(const string& dataRecord){mRecords.push_back(dataRecord);}

    protected:
        bool                                        mIsPacked;
        char                                        mSeparator;         //mSeparator used to seperate records
        string                                      mData;              //ONE IPC message.
        vector<string>                              mRecords;
        mutable vector<string>::iterator            mRecordIterator;
};

}
#endif
