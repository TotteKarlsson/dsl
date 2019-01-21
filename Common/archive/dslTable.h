#ifndef dslTableH
#define dslTableH
#include <string>
#include <vector>
#include "dslCommonExporter.h"
#include "dslObject.h"
#include "dslTableRow.h"
//---------------------------------------------------------------------------

namespace dsl
{

class DSL_COMMON Table : DSLObject
{
    public:
                                                Table();
                                                Table(const string& sString);
                                                Table(const string& sString, const string& sDelim);
                                                Table(const string& fName, const string& iniSection, const string& sDelim);
                                                Table(const  Table& other);
                                                Table& operator = (const Table& other);
        TableRow  				                GetCurrentRow() const;
        TableRow  				                GetEntry(int n) const;
        TableRow& 				                GetEntry(int n);
        TableRow& 				                operator [] (int n);
        TableRow  				                operator [] (int n) const;
        double                                  GetCurrentEntryValue() const;
        void                                    ResetTablePointer() ;
        void                                    SetTablePointer(int nIndex);
        void                                    IncrementTablePointer(int nStep = 1);
        void                                    DecrementTablePointer(int nStep = 1);
        void                                    operator++(int nNonsense);
        void                                    operator++();
        void                                    operator--(int nNonsense);
        void                                    operator--();
        void                                    SetTableText(const string& sString, const string& sDelim);
        void                                    SetTableText(const string& sString);
        void                                    SetDelimitor(const string& sString);
        void                                    ParseText();
        int                                     GetRowCount() const;
        int                                     GetRowEntryCount() const;

	protected:
        void                                    InsertRow(const string& _Row);

    private:
        int                                     mTablePointer;
        string                                  mDelims;
        vector<TableRow>     	                mTheTable;
};

}
#endif
