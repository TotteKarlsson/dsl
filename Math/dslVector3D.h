#ifndef dslVector3DH
#define dslVector3DH
#include "dslMathExporter.h"
#include "dslSubject.h"
#include "dslPoint.h"
#include "dslColor.h"
//---------------------------------------------------------------------------
namespace dsl
{

#define doubleStarToXYZMacro(ptn) ptn[0], ptn[1], ptn[2]

class DSL_MATH Vector3D : public Subject
{
    public:
                                                    Vector3D(double x = 0, double y = 0, double z = 1);
                                                    Vector3D(const Point& tip, const Point& origin = Point(0,0,0));
                                                    Vector3D(const Vector3D& cpy);
                                                    ~Vector3D();
        Vector3D&                                   operator=(const Vector3D& rhs);
        Point&                                      getTip();
        Point                                       getTip() const;

                                                    operator Point();

        void                                        setTip(const Point& ptn);
        void                                        setTip(double x, double y, double z);

        bool                                        isUnitVector() const;
        Vector3D                                    getUnitVector() const;

                                                    //Operations
        Vector3D                                    operator*(double scalar);
        Vector3D                                    operator/(double scalar);
        Vector3D                                    operator+(const Vector3D& point) const;
        Vector3D                                    operator-(const Vector3D& point) const;
        double                                      operator[](int index);

        DSL_MATH friend Vector3D                    operator*(const double &s, const Vector3D& point);
        DSL_MATH friend Vector3D                    operator*(const dslMatrix<double> &mat, const Vector3D& point);

        double                                      getAngleTo(const Vector3D& vec2) const;
        void                                        orientAlong(const Vector3D& vec);
        void                                        orientAntiParallellTo(const Vector3D& vec);

                                                    //Scalar product
        double                                      SP(const Vector3D& vec) const;

                                                    //Vector product
        Vector3D                                    VP(const Vector3D& vec) const;

        double                                      getMagnitude() const;
        void                                        setMagnitude(double magn);

  		void                                        setPosition(double x, double y, double z);
		void                                        setPosition(const Point& p1);

        void                                        translate(const Point& pt);

        //Euler stuff
        void                                        rotateX(double angle);
        void                                        rotateY(double angle);
        void                                        rotateZ(double angle);
        void                                        rotate(double angle, const Vector3D& v2);

                                                    //Get Euler angles
        void                                        Euler(double& Fi, double& Theta) const;
        Vector3D                                    getOrthogonalVector() const;

        void                                        set(const Point& ptn);
        void                                        set(double x, double y, double z);

        void                                        setX(double x);
        void                                        setY(double y);
        void                                        setZ(double z);

                                                    //These functions returns the x component of the 'unit' vector, that is
                                                    //the x component in a frame where origin = 0,0,0
        double                                      x() const;
        double                                      y() const;
        double                                      z() const;

        DSL_MATH
        friend ostream&                             operator<<(ostream &stream, Vector3D &out);
        void                                        roundOff();
        bool                                        isZero() const;
        void                                        normalize();

        //Properties related to visual properties of a vecotr
        void                                        setShaftRadius(double radius);
        void                                        setShaftResolution(int nrOfSides);

        virtual void                                setColor(const Color& clr);
        virtual Color                               getColor();
        Point                                       getPosition() const;

    protected:
        Point                                       mTip;

                                                    //Position is the origin in world coordinates, if we are to render the vector in 3D for example
        Point                                       mPosition;
        Color                                       mColor;

};

DSL_MATH Vector3D operator*(const Vector3D& vec, double);

}
#endif
