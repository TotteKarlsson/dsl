#ifndef MTKMXQETDATAREADER_H
#define MTKMXQETDATAREADER_H
//---------------------------------------------------------------------------
#include <complex>
#include "dslDataReader.h"

using std::complex;

class mtkMXQETDataReader : public mtkDataReader< complex<double> >
{
    public:
        mtkMXQETDataReader(mtkData< complex<double> > *mtkData)
        : mtkDataReader< complex<double> >(mtkData) {}

        virtual bool Read(const string& fileName, const DATA_FORMAT& format = mtkMXQETFORMAT, const FILE_FORMAT& fType = ffBINARY);
};
#endif
