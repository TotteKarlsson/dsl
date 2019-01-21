#ifndef dslPowderH
#define dslPowderH
#include <string>
#include "dslObject.h"
#include "MoleculeExporter.h"
#include "dslConstants.h"

namespace dsl
{

class EulerAngleSet;
class EulerAngleTriplet;
using std::string;

class MTK_MOLECULE dslPowder : public DSLObject
{
	public:
		                    dslPowder();
		virtual             ~dslPowder();
		EulerAngleSet* GetAngleSet();
		void SetSingleCrystal(const EulerAngleTriplet* angle);
		void SetAngleSet(EulerAngleSet* set);
		void ReadFromFile(const string& fileName);
		void WriteToFile(const string& fileName);
		void GenerateGridOrientations(int nrA, int nrB, int nrC);
		int GetNumberOfAngles();
		EulerAngleTriplet* GetAngle(int index);
		POWDERTYPE GetType();
		string GetFileName();

	private:
		POWDERTYPE type;
		int nrAlfa;
		int nrBeta;
		int nrGamma;
		string angleFileName;
		EulerAngleSet *angleSet;
};

}
#endif
