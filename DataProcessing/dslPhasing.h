#ifndef dslPhasingH
#define dslPhasingH
#include "dslObject.h"
#include "DataExporter.h"

namespace dsl
{

class MTK_DATA mtkPhasing : public DSLObject
{
  public:
                                mtkPhasing();
    double                         GetZeroOrderPhase() const {return mZeroOrderPhase;}
    double                         GetFirstOrderPhase() const {return mFirstOrderPhase;}
    double                         GetFirstOrderPhaseOffset() const {return mFirstOrderPhaseOffset;}
    void                        SetZeroOrderPhase(double phase0){mZeroOrderPhase = phase0;}
    void                        SetFirstOrderPhase(double phase1){mFirstOrderPhase = phase1;}
    void                        SetFirstOrderPhaseOffset(double val){mFirstOrderPhaseOffset = val;}
    void                        Reset();
	
  private:
    double                     mZeroOrderPhase;
    double                     mFirstOrderPhase;
    double                     mFirstOrderPhaseOffset;
};

}
#endif
