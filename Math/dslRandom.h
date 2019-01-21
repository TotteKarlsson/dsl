#ifndef dslRandomH
#define dslRandomH
#include "dslObject.h"
#include "dslMathExporter.h"
#include "mtrand/mtrand.h"
//---------------------------------------------------------------------------

namespace dsl
{

class DSL_MATH Random : DSLObject
{
	public:
						Random(double min = 0, double max = 1, int seed = 0);
                        Random(const Random& rnd);

		double          NextDouble() const;
		double          NextDouble(double min, double max) const;

	private:
		MTRand          mRand;        //Get a double in [0, 1)
        double          mMin;
        double          mMax;
};

}
#endif
