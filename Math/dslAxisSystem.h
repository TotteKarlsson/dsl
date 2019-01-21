#ifndef dslAxisSystemH
#define dslAxisSystemH
#include "dslMathExporter.h"
#include "dslSubject.h"
#include "dslPoint.h"
#include "dslVector3D.h"
#include "tinyxml2/tinyxml2.h"
#include "dslMathUtils.h"

namespace dsl
{
    using tinyxml2::XMLDocument;
    using tinyxml2::XMLNode;
    class EulerAngleTriplet;
    class Plane;

class DSL_MATH AxisSystem  : public Subject
{
    public:

                                                        AxisSystem(double x = 0, double y = 0, double z = 0);
                                                        AxisSystem(const Point& orig);
                                                        ~AxisSystem();

        void                                            setAxesLabels(const StringList& lbls);
        tinyxml2::XMLElement*                           addToXMLDocument(XMLDocument& doc, XMLNode* docRoot);
        void                                            update();

        Vector3D&                                       X();
        Vector3D&                                       Y();
        Vector3D&                                       Z();

        Vector3D                                        X() const;
        Vector3D                                        Y() const;
        Vector3D                                        Z() const;

        Point                                           getPosition() const;
        Point                                           getOrigin() const;
        void                                            setOrigin(double x, double y, double z);
        void                                            setOrigin(const Point& newo);
        void                                            setPosition(double x, double y, double z);
        void                                            setPosition(const Point& newo);

        //Input in degree
        void                                            rotateX(double angle, const AxisSystem* axes = nullptr);
        void                                            rotateY(double angle, const AxisSystem* axes = nullptr);
        void                                            rotateZ(double angle, const AxisSystem* axes = nullptr);

        void                                            rotateZYZ(const EulerAngleTriplet& ang, const AxisSystem* axes = nullptr);

        void                                            translate(const Point& ang);
        void                                            rotate(const Point& ang);

        void                                            rotateAboutVector(const Vector3D& p2, double angle);

        EulerAngleTriplet                               getEulerAnglesTo(const AxisSystem& sys2) const;
        EulerAngleTriplet                               getEulerAnglesToWorld() const;
        void                                            setAxisLength(double length);
        void                                            setAxisRadius(double thickness);

        void                                            invert();
        void                                            orientXAlongVector(const Vector3D& vec);
        void                                            orientYAlongVector(const Vector3D& vec);
        void                                            orientZAlongVector(const Vector3D& vec);

        void                                            orientXInPlane(const Plane& plane);
        void                                            orientXInPlaneAndZOrthogonal(const Plane& plane);
        void                                            orientXInPlaneAndYOrthogonal(const Plane& plane);

        void                                            orientYInPlane(const Plane& plane);
        void                                            orientYInPlaneAndZOrthogonal(const Plane& plane);
        void                                            orientYInPlaneAndXOrthogonal(const Plane& plane);

        void                                            orientZInPlane(const Plane& plane);
        void                                            orientZInPlaneAndXOrthogonal(const Plane& plane);
        void                                            orientZInPlaneAndYOrthogonal(const Plane& plane);

        void                                            resetOrientation();
        virtual string                                  getTypeName() const;
        StringList                                      getLabels() const;

        virtual void                                    setColor(const Color& clr);
        virtual Color                                   getColor();

    protected:
        StringList                                      mLabels;
        Color                                           mColor;
        Point                                           mOrigin;

        Vector3D                                        mXAxis;
        Vector3D                                        mYAxis;
        Vector3D                                        mZAxis;
};

}
#endif
