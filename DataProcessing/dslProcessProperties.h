#ifndef dslProcessPropertiesH
#define dslProcessPropertiesH
#include "DataExporter.h"
#include "dslDataProcessParameter.h"
#include "dslPhasing.h"

namespace dsl
{

class MTK_DATA mtkProcessProperties : public DSLObject
{
    public:
                                        mtkProcessProperties();
                                       ~mtkProcessProperties();
        void                               Read();
        void                            Read(string File);
        void                            Write(string File);
        void                            Write();

        /*** parameters***/
        mtkDataProcessParameter<bool>     FFT;
        mtkDataProcessParameter<int>     ZeroFill;
        mtkDataProcessParameter<int>     LeftShift;
        mtkDataProcessParameter<bool>     DCOffsetCorrection;

        mtkDataProcessParameter<double> EM;
        mtkDataProcessParameter<double> NormalizationFactor;
        string                             ProcFileName;
        mtkPhasing                         Phases;
		
    private:

    //processing of a "single" dimension..
};

}
#endif
