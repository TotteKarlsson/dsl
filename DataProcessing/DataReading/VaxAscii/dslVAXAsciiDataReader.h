#ifndef MTKVAXASCIIDATAREADER_H
#define MTKVAXASCIIDATAREADER_H
//---------------------------------------------------------------------------
#include <complex>
#include "dslDataReader.h"

using std::complex;

class mtkVaxAsciiDataReader : public mtkDataReader< complex<double> >
{
    public:
        mtkVaxAsciiData(mtkData< complex<double> > *mtkData)
        : mtkDataReader< complex<double> >(mtkData) {}

        virtual bool Read(const string& fileName, const DATA_FORMAT& format = dfUW, const FILE_FORMAT& fType = ffBINARY);
};
#endif
