#ifndef MTKUWREADER_H
#define MTKUWREADER_H
//---------------------------------------------------------------------------
#include <complex>
#include "dslDataReader.h"

using std::complex;

class mtkUWReader : public mtkDataReader< complex<double> >
{
    public:
        mtkUWReader(mtkData< complex<double> > *mtkData)
        : mtkDataReader< complex<double> >(mtkData) {}

        virtual bool Read(const string& fileName, const DATA_FORMAT& format = dfUW, const FILE_FORMAT& fType = ffBINARY);
};
#endif
