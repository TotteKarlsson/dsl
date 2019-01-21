#ifndef EulerAngleTripletH
#define EulerAngleTripletH
#include <fstream>
#include <ostream>
#include "dslObject.h"
#include "dslMathExporter.h"

namespace dsl
{

using std::fstream;
using std::ostream;
using std::string;
class EulerAngleTriplet;

class DSL_MATH EulerAngleTriplet : public DSLObject
{
	public:
                                                EulerAngleTriplet(double a = 0, double b = 0, double g = 0, double w = 1);
                                                EulerAngleTriplet(const EulerAngleTriplet& e);
                                                ~EulerAngleTriplet();

        EulerAngleTriplet&                             operator = (const EulerAngleTriplet& EulerAngleTriplet);

                                                /*** Alpha ***/
        void                                    setAlpha(double Alpha);
        double                                  getAlpha() const ;
        double&                                 getAlphaRef() ;

                                                /*** Beta ***/
        void                                    setBeta(double Beta);
        double                                  getBeta() const ;
        double&                                 getBetaRef() ;

                                                /*** Gamma ***/
        void                                    setGamma(double Gamma);
        double                                  getGamma() const ;
        double&                                 getGammaRef() ;

                                                /*** Weight ***/
        void                                    setWeight(double Weight);
        double                                  getWeight() const ;
        double&                                 getWeightRef() ;

        /*** General ***/
        void                                    set(double X, double Y, double Z);
        void                                    set(double X, double Y, double Z, double weight);
        void                                    set(const EulerAngleTriplet &angle);

        EulerAngleTriplet&                             convertToRadians();
        EulerAngleTriplet&                             convertToDegree();
        void                                    zero();

        DSL_MATH
        friend std::ostream&                    operator<<(std::ostream &stream, const EulerAngleTriplet &out);

	private:
		double                                  mAlpha;
		double                                  mBeta;
		double                                  mGamma;
		double                                  mWeight;
};

}
#endif
