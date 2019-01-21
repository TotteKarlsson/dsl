#ifndef MTKFELIXDATAREADER_H
#define MTKFELIXDATAREADER_H
//---------------------------------------------------------------------------
#include <complex>
#include "dslDataReader.h"

using std::complex;

class mtkFelixDataReader : public mtkDataReader< complex<double> >
{
    public:
        mtkFelixDataReader(mtkData< complex<double> > *mtkData)
        : mtkDataReader< complex<double> >(mtkData) {}

        virtual bool Read(const string& fileName, const DATA_FORMAT& format = dfSimpson, const FILE_FORMAT& fType = ffBINARY);
};
#endif
