#ifndef dslDataLinkH
#define dslDataLinkH
#include <complex>
#include "dslObject.h"
#include "DataExporter.h"

namespace dsl
{

template <class T>
class mtkData;
class PointSet;
class MolecularAssembly;

using std::complex;

class MTK_DATA mtkDataLink : public DSLObject
{
    public:
        enum {  dtDoubleData, dtComplexData, dtPointSetData, dtMolecule, dtUnKnown}
                                        mDataType;

                                        mtkDataLink();
        virtual void                    SetInput(mtkData<double> *InputData);
        virtual void                    SetInput(mtkData< complex<double> > *InputData);
        virtual void                    SetInput(PointSet *InputData);
        virtual void                    SetInput(MolecularAssembly *InputData);

        mtkData<double>*                GetDblData();
        mtkData<complex<double> >*      GetCpxData();
        PointSet*                       GetPtSetData();
        MolecularAssembly*              GetMoleculeData();
        bool                            isPopulated();

    protected:
        mtkData< double >*              DblData;
        mtkData< complex< double> >*    CpxData;
        PointSet*                       PtSetData;
        MolecularAssembly*              MoleculeData;
};

}
#endif
