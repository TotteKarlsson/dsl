#ifndef dslGaussianPeakH
#define dslGaussianPeakH
#include "dslPeak.h"
//---------------------------------------------------------------------------

namespace dsl
{

class DSL_MATH GaussianPeak : public Peak
{
    public:
                                        GaussianPeak(double centerX = 0, double centerY = 0, double amplitude = 0, double xwidth = 0, double ywidth = 0);
                                       ~GaussianPeak();
        double                          z(double x, double y);
        
};

}
#endif
