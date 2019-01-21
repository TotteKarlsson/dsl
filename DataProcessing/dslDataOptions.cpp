
#pragma hdrstop
#include "dslDataOptions.h"


namespace dsl
{

dslDataOptions::dslDataOptions()
{
      readType = ffASCII;
      writeType = ffASCII;
}

dslDataOptions::dslDataOptions(const dslDataOptions& opt)
{
      readType = opt.readType;
      writeType = opt.writeType;;
}

void dslDataOptions::Set(dslDataOptions* opt)
{
      readType = opt->readType;
     writeType = opt->writeType;;
}

}
