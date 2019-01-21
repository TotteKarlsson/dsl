#ifndef dslCSATensorH
#define dslCSATensorH
#include <iostream>
#include "dslObject.h"
#include "MoleculeExporter.h"
#include "dslConstants.h"
#include "dslEulerAngleTriplet.h"
namespace dsl
{

struct wigner_struc;
class ISTensor;

class Environment;
class Explorer;
class AxisSystem;
using std::string;
using std::ostream;
class Explorer;
enum dslCalcTensorRule {FROMPRINCIPALVALUES = 0, FROMSIGMAVALUES};

class MTK_MOLECULE CSATensor : public DSLObject
{
	public:
		                                        CSATensor(const Point& center = Point(0,0,0));
		virtual                                 ~CSATensor();
		void                                    set(const CSATensor& cs);
		void                                    setup(double larmorfreq);
		void                                    setupInField(double larmorfreq);

		/*** Rotation of the site ***/
		void                                    rotate(const FRAMETRANSFORMATION& frameTransformation, const EulerAngleTriplet &EUL);

        ISTensor*                               getCSAInP();
		ISTensor*                               getCSAInC();
		ISTensor*                               getCSAInR();
		ISTensor*                               getCSAInL();

		//Observe! before calling these, make sure the tensor has been evaluated
		bool                                    evaluateTensor(const dslCalcTensorRule& rule = FROMPRINCIPALVALUES);
        double                                  getXX() const {return mXX;}
        double                                  getYY() const {return mYY;}
        double                                  getZZ() const {return mZZ;}
        double                                  getSigmaIso() const {return mSigmaIso;}
        double                                  getSigmaAniso()const {return mSigmaAniso;}
        double                                  getAsymmetry() const {return mAsymmetryParameter;}

        double                                  getOmegaAniso() const {return mOmegaAniso;}
        double                                  getOmegaIso() const {return mOmegaIso;}

        void                                    setXX(double val);
        void                                    setYY(double val);
        void                                    setZZ(double val);
        void                                    setSigmaIso(double val);
        void                                    setSigmaAniso(double val);
        void                                    setAssParameter(double val);

        void                                    setOmegaIso(double val);
        void                                    setOmegaAniso(double val);

        EulerAngleTriplet                              getAnglesPToC() const {return mPToC;}
        EulerAngleTriplet                              getAnglesPToR(){return mPToR;}
        CSATensor*                              getCSA(){return this;}
        int                                     getUseAssy(){return mUseAssymetryParameters;}

        void                                    setEnvironment(Environment *env);
        Environment*                            getEnvironment(){return mEnvironment;}
        bool                                    read(const string &File, const string &label);
        void                                    out(char* text);
        void                                    saveToFile(char* File);
        void                                    appendParametersToFile(char* File);
        AxisSystem*                             getCSAAxes();
        friend ostream&                         operator<<(ostream &stream, const CSATensor *out);
        void                                    useExplorer(Explorer* e);
        Explorer*                               getExplorer();

	protected:
		AxisSystem*                             mCSAAxes;

    private:
		Environment*                            mEnvironment;
		Point                                   mPosition;

		ISTensor*                               mInP; // Tensors in different frames
		ISTensor*                               mInC;
		ISTensor*                               mInR;
		ISTensor*                               mInL;

		EulerAngleTriplet                              mPToC;
		EulerAngleTriplet                              mPToR;
		int                                     mUseAssymetryParameters;
		double                                  mXX;
        double                                  mYY;
        double                                  mZZ;
		double                                  mSigmaIso;
        double                                  mSigmaAniso;
        double                                  mAsymmetryParameter;
		double                                  mOmegaIso;
        double                                  mOmegaAniso; //Hertz
		wigner_struc*                           mWignerStruc;
		void                                    orderShieldingParameters(double* x, double* y, double* z);
		void                                    setupCSATensorInPas();

};

}
#endif
