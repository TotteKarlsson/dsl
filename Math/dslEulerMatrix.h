#ifndef dslEulerH
#define dslEulerH
#include "dslMatrix.h"
#include "dslObject.h"
#include "dslMathExporter.h"

namespace dsl
{

class DSL_MATH EulerMatrix : public DSLObject
{
    public:
                                            EulerMatrix();
                                            ~EulerMatrix();
        void                                SetMatrices(double fi, double theta);
        dslMatrix<double>&                  GetTMatrix();;
        dslMatrix<double>&                  GetINVTMatrix();;

    private:
        dslMatrix<double>                   TMatrix;
        dslMatrix<double>                   INVTMatrix;
};

}
#endif
