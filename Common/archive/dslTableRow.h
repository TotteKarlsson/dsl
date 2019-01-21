#ifndef dslTableRowH
#define dslTableRowH
#include <string>
#include <vector>
#include "dslObject.h"
//---------------------------------------------------------------------------

namespace dsl
{

class DSL_COMMON TableRow : DSLObject
{
    public:
                                                    TableRow();
                                                    TableRow(const string& sString);
                                                    TableRow(const string& sString, const string& sDelim);
                                                    TableRow(const string& fName, const string& iniSection, const string& sDelim);
                                                    TableRow(const  TableRow& other);

        TableRow&                                   operator = (const TableRow& other);

        string                                      GetCurrentEntry() const;
        string                                      GetEntry(int n) const;
        string&                                     GetEntry(int n);

        string&                                     operator [] (int n);
        string                                      operator [] (int n) const;
        void                                        operator++(int nNonsense);
        void                                        operator++();
        void                                        operator--(int nNonsense);
        void                                        operator--();

        void                                        ResetTablePointer() ;
        void                                        SetTablePointer(int nIndex);
        void                                        IncrementTablePointer(int nStep = 1);
        void                                        DecrementTablePointer(int nStep = 1);

        void                                        SetTableText(const string& sString, const string& sDelim);
        void                                        SetTableText(const string& sString) ;
        void                                        SetDelimitor(const string& sString);
        void                                        ParseText();
        string                                      GetRow();
        int                                         GetEntryCount() const;
        int                                         GetCurrentRowPosition() const;

    protected:
        string                                      mEntryText;
        string                                      mDelims;
        int                                         mTablePointer;
        int                                         mEntryCount;
        int                                         CountEntries();
        vector<string>                              mTableRow;
        bool                                        IsDelimiter(char c);

};

}
#endif
