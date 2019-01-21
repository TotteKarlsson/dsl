#ifndef MTKSIMPSONATAREADER_H
#define MTKSIMPSONDATAREADER_H
//---------------------------------------------------------------------------
#include <complex>
#include "DataExporter.h"
#include "dslDataReader.h"

using std::complex;

class MTK_DATA mtkSimpsonDataReader : public mtkDataReader< complex<double> >
{
    public:
        mtkSimpsonDataReader(mtkData< complex<double> > *mtkData)
        : mtkDataReader< complex<double> >(mtkData) {}

        virtual bool Read(const string& fileName, const DATA_FORMAT& format = dfSimpson, const FILE_FORMAT& fType = ffBINARY);
};
#endif
