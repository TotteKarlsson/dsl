#ifndef dslCellParametersH
#define dslCellParametersH
#include "dslMatrix.h"
#include "dslObject.h"
#include "dslMathExporter.h"

namespace dsl
{

class DSL_MATH CellParameters : public DSLObject
{
	public:
		                                    CellParameters(double aAxes = 1, double bAxes = 1, double cAxes = 1, double betaAngle = 90);
		void                                set_abcBeta(double aAxes, double bAxes, double cAxes, double beta);
		dslMatrix<double>                   getTranformationMatrix() const;

	private:
		double a;
		double b;
		double c;
		double beta;
};

}
#endif
