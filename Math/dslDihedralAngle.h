#ifndef dslDihedralAngleH
#define dslDihedralAngleH
#include <string>
#include <vector>
#include "dslObject.h"
#include "dslMathExporter.h"
//#include "dslPoint.h"
#include "dslVector3D.h"
namespace dsl
{
using std::string;
using std::vector;

//Calculate the dihedral angle from four points
//Make this a class so it can be used for viualization of the angle, using the four poitns
class DSL_MATH DihedralAngle : public DSLObject
{
	public:
		                                    DihedralAngle(const Point& a1, const Point& a2, const Point& a3, const Point& a4);
		                                    ~DihedralAngle();

		double                              calculate();
        vector<Point>                       getPoints();
        Vector3D                            getNormal1();
        Vector3D                            getNormal2();
        double                              mTheAngle;
                                            operator double();//{return calculate();}
    protected:
        vector<Point>                       mPoints;
        Vector3D                            mNormal1;
        Vector3D                            mNormal2;

};

}
#endif
