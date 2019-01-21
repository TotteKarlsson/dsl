#pragma hdrstop
#include "dslDataSliceInfo.h"
#include "dslVector.h"

namespace dsl
{

dslDataSliceInfo::dslDataSliceInfo()
{
  sliceNrStart = 1;
  sliceNrEnd   = 1;
  sliceIncrement = 1;
  slices = nullptr;
}

dslDataSliceInfo::~dslDataSliceInfo(){
  delete slices;
}
dslVector<int>* dslDataSliceInfo::GetSlices(){
  if(!slices)
    slices = new dslVector<int>(0);
  return slices;
}

void dslDataSliceInfo::SetNumberOfSlices(int nrOfSlices){
  GetSlices()->Resize(nrOfSlices);
}

//---------------------------------------------------------------------------


}
