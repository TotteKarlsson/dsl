#ifndef dslPointH
#define dslPointH
#include <ostream>
#include <vector>
#include <sstream>
#include "dslObject.h"
#include "dslMathExporter.h"
#include "dslProperty.h"
#include "dslXMLUtils.h"

namespace dsl
{

using std::vector;
using std::string;
using std::stringstream;

class Point;
string DSL_MATH toString(const Point& ptn, const char delimiter = ',');
template <class T>
class  dslMatrix;

//Macro when we need x,y and z() to be passed
#define ptn3DMacro(ptn) ptn.x(), ptn.y(), ptn.z()
#define pointExpandMacro(ptn) ptn.x(), ptn.y(), ptn.z()

//Refactoring: Create a vector class (Vector3D), that has 'two' points, origin and tip.
//Move pure vector related operations to that class out of the point class
//Current point class can be thought of as a vector with origin 0,0,0
class DSL_MATH Point : public DSLObject
{
    public:
                                                    Point(double x = 0, double y = 0, double z = 0);
                                                    Point(const Point& point);
                                                    Point(const vector<double>& point);
                                                    ~Point();

        Point&                                      operator=(const Point& point);

        const Point                                 operator+(const Point& point) const;
        Point                                       operator-(const Point& point) const;
        DSL_MATH friend Point                       operator/(const Point& point, double);
        DSL_MATH friend Point                       operator*(const dslMatrix<double> &mat, const Point& point);

		double             		                    operator[](int index) const;
		double&		                                operator[](int index);

        bool                                        isAtOrigin();
        double                                      distanceFromOrigin() const;

        //To be deprecated
        double                                      getLength() const;

        double                                      distanceTo(const Point& point) const;
        void                                        normalize();

        //Euler stuff
        void                                        rotateX(double angle);
        void                                        rotateY(double angle);
        void                                        rotateZ(double angle);

        void                                        rotate(double angle, const Point& Point2);
        void                                        getEulerAngles(double& Fi, double& Theta) const;

        double&                                     xRef();
        double&                                     yRef();
        double&                                     zRef();

        double                                      x() const ;
        double                                      y() const ;
        double                                      z() const ;

        void                                        orientAlong(const Point& vec);

        void                                        addToPoint(double x, double y, double z);
        void                                        addToPoint(const Point& point);

        void                                        set(double x, double y, double z);
        void                                        set(const Point& point);

        void                                        setX(double x);
        void                                        setY(double y);
        void                                        setZ(double z);
        void                                        zero();
        void                                        setUnMoved();
        void                                        setMoved();
        bool                                        isMoved();

        virtual string                              asString(const char& delimiter) const;
        DSL_MATH friend ostream&                    operator<<(ostream &stream, const Point &out);
        XMLElement*                                 addToXMLDocument(XMLDocument& doc, XMLNode* docRoot);
        virtual string                              getTypeName() const;
//DSL_MATH Point operator*(const Point& point, double num);

    private:
        bool                                        mIsMoved;
        double                                      mX;
        double                                      mY;
        double                                      mZ;
};

DSL_MATH const Point operator*(const Point& ptn, double num);
DSL_MATH const Point operator*(double num, const Point& ptn);
DSL_MATH double getDistance(const Point& p1, const Point& p2);

template<> inline
bool Property<Point>::write(IniFile* iniFile, const string& section)
{
    return false;
}

template<> inline
bool Property<Point>::read(IniFile* iniFile, const string& section)
{
    return false;
}

template<> inline
bool Property<Point>::assignValueFromString(const string& v)
{
    return false;
}

template<> inline
string Property<Point>::getTypeName() const
{
    return "point";
}

template<>
inline string getTypeAsString<Point>(const Point& obj)
{
    return "point";
}


}
#endif
