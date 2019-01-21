#ifndef dslDirectDipolarCouplingTensorH
#define dslDirectDipolarCouplingTensorH
#include <string>
#include "dslObject.h"
#include "dslEulerAngleTriplet.h"
namespace dsl
{

using namespace std;
struct wigner_struc;
class ISTensor;
class AxisSystem;
class Bond;

class MTK_MOLECULE DirectDipolarCouplingTensor : public DSLObject
{
	public:
		                                            DirectDipolarCouplingTensor();
                                                    DirectDipolarCouplingTensor(Bond* parentBond);

		virtual                                     ~DirectDipolarCouplingTensor();
		void                                        getInput(string& compoundFile, string& compound, string& CplNr);
		void                                        setup();
		void                                        setupInPASFrame(double CplConstant);

		//Tensor rotations
		void                                        rotate(const FRAMETRANSFORMATION& frameTransformation, const EulerAngleTriplet &EUL);
//		void                                        rotate(const FRAMETRANSFORMATION& frameTransformation, const EulerAngleTriplet *EUL);
		void                                        rotateFromPASToCrystalFrame();
		void                                        rotateFromPASToCrystalFrame(double a, double b, double g);
		void                                        rotateFromPASToCrystalFrame(const EulerAngleTriplet& EUL);

		void                                        rotateFromPASToMoleculeFrame(double a,double b,double g);
		void                                        rotateFromPASToMoleculeFrame(const EulerAngleTriplet& EUL);
  		void                                        rotateFromPASToRotorFrame(const EulerAngleTriplet& EUL);
  		void                                        rotateFromPASToLabFrame(const EulerAngleTriplet& EUL);

		void                                        rotateFromCrystalToRotorFrame(const EulerAngleTriplet& EUL);
		void                                        rotateFromCrystalToLabFrame(const EulerAngleTriplet& EUL);

		void                                        rotateFromMoleculeToRotorFrame(const EulerAngleTriplet& EUL);
		void                                        rotateFromRotorToLabFrame(const EulerAngleTriplet& Angle);

		double&                                     getCouplingConstant();
		void                                        setCouplingConstant(double newCpl);
		double                                      mIsoElement;

		ISTensor*                                   getCplInP();
		ISTensor*                                   getCplInC();
		ISTensor*                                   getCplInR();
		ISTensor*                                   getCplInL();

		EulerAngleTriplet                                  getAnglesPToC(){return mPToC;}
		void                                        setEulerAnglesPToC(const EulerAngleTriplet& angle);
		DirectDipolarCouplingTensor*             getDDCpl(){return this;}
		AxisSystem*                                 getAxes();

		friend ostream& operator<<(ostream &stream, DirectDipolarCouplingTensor& out);

	protected:
		AxisSystem*                                 mAxes;
		double                                      mDDCpl;

		ISTensor*                                   mInP;
        ISTensor*                                   mInC;
        ISTensor*                                   mInR;
        ISTensor*                                   mInL;
		EulerAngleTriplet                                  mPToC;
		wigner_struc*                               mWignerStruc;
		void                                        SetupInPASFrame();
};

typedef DirectDipolarCouplingTensor dslDDTensor;

}
#endif
