#pragma hdrstop
#include "dslDataLink.h"

namespace dsl
{
dslDataLink::dslDataLink()
:
DblData(nullptr),
CpxData(nullptr),
PtSetData(nullptr),
MoleculeData(nullptr),
mDataType(dtUnKnown)
{
}

bool dslDataLink::isPopulated()
{
    return mDataType == dtUnKnown ? false : true;
}

void dslDataLink::SetInput(PointSet *InputData)
{
    mDataType     = dtPointSetData;
    PtSetData    = InputData;
}

void dslDataLink::SetInput(dslData<double> *InputData)
{
    mDataType = dtDoubleData;
    DblData  = InputData;
}

void dslDataLink::SetInput(dslData<complex<double> > *InputData)
{
    mDataType = dtComplexData;
    CpxData = InputData;
}

void dslDataLink::SetInput(MolecularAssembly *InputData)
{
    mDataType = dtMolecule;
    MoleculeData = InputData;
}

dslData<double>* dslDataLink::GetDblData()
{
    return DblData;
}

}
