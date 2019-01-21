#pragma hdrstop
#include "dslDataProcessProperties.h"
#include "dslProcessProperties.h"

namespace dsl
{

dslDataProcessProperties::dslDataProcessProperties()
{
    mRowDimProc = new dslProcessProperties;
      mColDimProc    = new dslProcessProperties;
}

dslDataProcessProperties::~dslDataProcessProperties()
{
      delete mRowDimProc;
      delete mColDimProc;
}


}
