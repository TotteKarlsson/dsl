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

//Old code.. clean this up..
class DSL_IPC IPCData : public DSLObject
{
    public:
                                                    IPCData(short id);
                                                    IPCData(const string& data = dsl::gEmptyString, const char& sep = '|');
                                                    IPCData(const IPCData& rhs);
        virtual                                     ~IPCData();

        bool                                        init();
        vector<string>::iterator                    iterator();
        void                                        resetIterator();
        vector<string>::iterator                    begin();
        vector<string>::iterator                    end();
        void                                        inrementIterator();
        string                                      getNextRecord();
        string                                      getData() const;
        size_t                                      getNumberOfRecords() const;
        virtual bool                                hasData() const;
        virtual bool                                unPack();
        virtual bool                                pack();
        bool                                        isPacked() const;
        void                                        addData(const string& data);
        void                                        addRecord(const string& dataRecord);

    protected:
        bool                                        mIsPacked;
        char                                        mSeparator;         //mSeparator used to seperate records
        string                                      mData;              //ONE IPC message.
        vector<string>                              mRecords;
        mutable vector<string>::iterator            mRecordIterator;
};

}
#endif
