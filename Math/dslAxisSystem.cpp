#pragma hdrstop
#include <cmath>
#include "dslMathUtils.h"
#include "dslAxisSystem.h"
#include "dslEulerAngleTriplet.h"
//include "dslPlane.h"
#include "dslUtils.h"
#include "dslColor.h"

namespace dsl
{

using namespace tinyxml2;
using namespace std;

AxisSystem::AxisSystem(double x, double y, double z)
:
mOrigin(x, y, z),
mXAxis(1, 0, 0),
mYAxis(0, 1, 0),
mZAxis(0, 0, 1),
mColor(Blue)
{
    mLabels.reSize(3);
    mLabels[0] = "x";
    mLabels[1] = "y";
    mLabels[2] = "z";
    mXAxis.setPosition(mOrigin);
    mYAxis.setPosition(mOrigin);
	mZAxis.setPosition(mOrigin);

	mXAxis.setColor(Red);
	mYAxis.setColor(Green);
	mZAxis.setColor(Blue);
}

AxisSystem::AxisSystem(const Point& origin)
:
mOrigin(origin),
mXAxis(origin.x() + 1, origin.y(), origin.z()),
mYAxis(origin.x(), origin.y() + 1, origin.z()),
mZAxis(origin.x(), origin.y(), origin.z() + 1),
mColor(Blue)
{
	mLabels.reSize(3);
	mLabels[0] = "x";
	mLabels[1] = "y";
	mLabels[2] = "z";
	mXAxis.setPosition(mOrigin);
	mYAxis.setPosition(mOrigin);
	mZAxis.setPosition(mOrigin);

	mXAxis.setColor(Red);
	mYAxis.setColor(Green);
	mZAxis.setColor(Blue);
}

AxisSystem::~AxisSystem()
{
	if(hasObservers())
	{
		notifyObservers(SubjectEvent::SubjectBeingDestroyed);
    }
}

void AxisSystem::setAxesLabels(const StringList& lbls)
{
    if(lbls.size() != 3)
    {
        return;
    }
    mLabels = lbls;
}

void AxisSystem::setColor(const Color& clr)
{
    mColor = clr;
    notifyObservers(SubjectEvent::UpdateColor);
}

Color AxisSystem::getColor()
{
    return mColor;
}

StringList AxisSystem::getLabels() const
{
    return mLabels;
}

XMLElement* AxisSystem::addToXMLDocument(XMLDocument& doc, XMLNode* docRoot)
{
    //Create XML for saving to file
    tinyxml2::XMLElement* root  = doc.NewElement("AxisSystem");
    tinyxml2::XMLNode* rootNode = doc.InsertFirstChild(root);

//    root->SetAttribute("visible", this->isVisible());
//    root->SetAttribute("high-lighted", this->isHighLigthed());
    //Insert origin

    //Save Camera position, FocalPoint, ViewUp & ViewAngle
    XMLElement* elem = doc.NewElement("origin");
    elem->SetAttribute("x", mOrigin.x());
    elem->SetAttribute("y", mOrigin.y());
    elem->SetAttribute("z", mOrigin.z());
    rootNode->InsertEndChild(elem);

    //XAxis position
    elem = doc.NewElement("x-axis");
    elem->SetAttribute("x", mXAxis.getTip().x());
    elem->SetAttribute("y", mXAxis.getTip().y());
    elem->SetAttribute("z", mXAxis.getTip().z());
    rootNode->InsertEndChild(elem);

    elem = doc.NewElement("y-axis");
    elem->SetAttribute("x", mYAxis.getTip().x());
    elem->SetAttribute("y", mYAxis.getTip().y());
    elem->SetAttribute("z", mYAxis.getTip().z());
    rootNode->InsertEndChild(elem);

    elem = doc.NewElement("z-axis");
    elem->SetAttribute("x", mZAxis.getTip().x());
    elem->SetAttribute("y", mZAxis.getTip().y());
    elem->SetAttribute("z", mZAxis.getTip().z());
    rootNode->InsertEndChild(elem);

    docRoot->InsertEndChild(root);
    return root;
}

Point AxisSystem::getPosition() const
{
    return mOrigin;
}

Point AxisSystem::getOrigin() const
{
    return mOrigin;
}

Vector3D AxisSystem::X() const
{
    return mXAxis;
}

Vector3D AxisSystem::Y() const
{
    return mYAxis;
}

Vector3D AxisSystem::Z() const
{
    return mZAxis;
}

Vector3D& AxisSystem::X()
{
    return mXAxis;
}

Vector3D& AxisSystem::Y()
{
    return mYAxis;
}

Vector3D& AxisSystem::Z()
{
    return mZAxis;
}

string AxisSystem::getTypeName() const
{
    return "axisSystem";
}

void AxisSystem::setPosition(double x, double y, double z)
{
    setOrigin(Point(x,y,z));
}

void AxisSystem::setPosition(const Point& o)
{
    setOrigin(o);
}

void AxisSystem::setOrigin(double x, double y, double z)
{
    Point nc(x,y,z);
    setOrigin(nc);
}

void AxisSystem::setOrigin(const Point& newOrigin)
{
    Point translate;
    translate.set(newOrigin - mOrigin);

    mOrigin.set(newOrigin);

    mXAxis.setPosition(mOrigin);
    mYAxis.setPosition(mOrigin);
    mZAxis.setPosition(mOrigin);

    notifyObservers(SubjectEvent::UpdatePosition);
}

void AxisSystem::rotate(const Point& xyz)
{
    if(xyz.x())
    {
        rotateX(xyz.x());
    }

    if(xyz.y())
    {
        rotateY(xyz.y());
    }

    if(xyz.z())
    {
        rotateZ(xyz.z());
    }
}

void AxisSystem::translate(const Point& xyz)
{
	setOrigin(this->getOrigin() + xyz);
}

void AxisSystem::rotateX(double angle, const AxisSystem* axes)
{
	if(axes != this)
	{
		Vector3D axis(1, 0, 0);

		//Rotate the system about world origin
		mXAxis.rotate(angle, axis);
		mYAxis.rotate(angle, axis);
		mZAxis.rotate(angle, axis);
		mOrigin.rotateX(angle);

		mXAxis.setPosition(mOrigin);
		mYAxis.setPosition(mOrigin);
		mZAxis.setPosition(mOrigin);
	}
	else
	{
		mYAxis.rotateX(angle);
		mZAxis.rotateX(angle);
	}
}

void AxisSystem::rotateY(double angle, const AxisSystem* axes)
{
	if(axes != this)
	{
		Vector3D axis(0,1,0);

		//Rotate the system about world origin
		mXAxis.rotate(angle, axis);
		mYAxis.rotate(angle, axis);
		mZAxis.rotate(angle, axis);
		mOrigin.rotateY(angle);

		mXAxis.setPosition(mOrigin);
		mYAxis.setPosition(mOrigin);
		mZAxis.setPosition(mOrigin);
	}
	else
	{
		mZAxis.rotateY(angle);
		mXAxis.rotateY(angle);
	}
}

void AxisSystem::rotateZ(double angle, const AxisSystem* axes)
{
	if(axes != this)
	{
		Vector3D axis(0,0,1);
		//Rotate the system about world origin
		mXAxis.rotate(angle, axis);
		mYAxis.rotate(angle, axis);
		mZAxis.rotate(angle, axis);
		mOrigin.rotateZ(angle);

		mXAxis.setPosition(mOrigin);
		mYAxis.setPosition(mOrigin);
		mZAxis.setPosition(mOrigin);
	}
	else
	{
		mXAxis.rotateZ(angle);
		mYAxis.rotateZ(angle);
	}
}

void AxisSystem::rotateZYZ(const EulerAngleTriplet& e, const AxisSystem* axes)
{
	//This routine execute a rotation about the z with angle a, new y (angle b) and finally new z (angle g)
	//of self
	rotateZ(e.getAlpha());
	rotateY(e.getBeta());
	rotateZ(e.getGamma());
}

void AxisSystem::rotateAboutVector(const Vector3D& p2, double angle)
{
    mOrigin.rotate(angle, p2.getTip());
    mXAxis.setPosition(mOrigin);
    mYAxis.setPosition(mOrigin);
    mZAxis.setPosition(mOrigin);

    mXAxis.rotate(angle,p2);
    mYAxis.rotate(angle,p2);
    mZAxis.rotate(angle,p2);
}

EulerAngleTriplet AxisSystem::getEulerAnglesToWorld() const
{
    AxisSystem world;
    return getEulerAnglesTo(world);
}

EulerAngleTriplet AxisSystem::getEulerAnglesTo(const AxisSystem& sys2) const
{
    AxisSystem temp(*this);
//    Point originalOrigin(temp.getOrigin());


    temp.setOrigin(0,0,0);
    AxisSystem s2(sys2);
    s2.setOrigin(0,0,0);

    double alpha,beta,gamma;
    double zZAngle = temp.mZAxis.getAngleTo(s2.mZAxis);

    //First check if Z axes are colinear
    //If they are, set gamma == 0 and beta 0, or Pi and calculate alpha
    if(checkForZero(zZAngle) || checkForZero(zZAngle, gPi))
    {
        double zz = s2.Z().SP(temp.Z());
        int n = (1 + sign(zz))/2;
        int sign = (int) -pow(-1.0,n);
        double argy = sign * s2.X().SP(temp.Y());
        double argx = sign * s2.X().SP(temp.X());

        alpha = atan2(argy,argx);

        //beta is equal to PI if z axes are anti parallell, otherwise 0
        beta = checkForZero(zZAngle, gPi) ? gPi : 0;
        gamma = 0;
    }
    else
    {
        //calculate alpha
        double argy = -(s2.Z().SP(temp.Y()));
        double argx = -(s2.Z().SP(temp.X()));
        alpha =  atan2(argy, argx);

        //calculate beta
        double cosa = cos(alpha);
        if(checkForZero(cosa))
        {
            beta =  atan2(s2.Z().SP(temp.Y())/sin(alpha),s2.Z().SP(temp.Z()) );
        }
        else
        {
            beta =  atan2(s2.Z().SP(temp.X())/cosa, s2.Z().SP(temp.Z()) );
        }

        //calculate gamma
        double argy2 = -(s2.Y().SP(temp.Z()));
        double argx2 = s2.X().SP(temp.Z());
        gamma = atan2(argy2,argx2);

    }

//    this->setOrigin(originalOrigin);
    alpha   = normalizeAngle(alpha);
    beta    = normalizeAngle(beta);
    gamma   = normalizeAngle(gamma);

    return EulerAngleTriplet(alpha, beta, gamma).convertToDegree();
}

void AxisSystem::orientXAlongVector(const Vector3D& vec)
{
//    Point Origin(this->getOrigin());
//
//    setOrigin(0,0,0);
//    if(vec.getAngleTo(mXAxis) != 0)
//    {
//        rotateAboutVector( mXAxis.VP(vec), toDegree(vec.getAngleTo(X()) ));
//    }
//    setOrigin(Origin);
}

void AxisSystem::orientYAlongVector(const Vector3D& vec)
{
//    Point Origo(this->getOrigin());
//    setOrigin(0,0,0);
//    if(vec.getAngleTo(Y()) != 0)
//    {
//        rotateAboutVector(mYAxis.VP(vec), toDegree(vec.getAngleTo(Y()) ));
//    }
//    setOrigin(Origo);
}

void AxisSystem::orientZAlongVector(const Vector3D& vec)
{
    Point Origo(this->getOrigin());
    this->setOrigin(0,0,0);

    if(vec.getAngleTo(Z()) != 0)
    {
        rotateAboutVector(mZAxis.VP(vec), toDegree(vec.getAngleTo(Z()) ));
    }
    setOrigin(Origo);
}

void AxisSystem::orientZInPlane(const Plane& plane)
{
//    Point Origin(this->getOrigin());
//    this->setOrigin(0,0,0);
//
//    if(plane.getVectorInPlane().getAngleTo( Z() ) != 0)
//    {
//        rotateAboutVector( mZAxis.VP(plane.getVectorInPlane()), toDegree(plane.getVectorInPlane().getAngleTo(Z()) ));
//    }
//
//    setOrigin(Origin);
}

void AxisSystem::orientXInPlane(const Plane& plane)
{
//    Point Origin (this->getOrigin());
//    this->setOrigin(0,0,0);
//    if(plane.getVectorInPlane().getAngleTo( X() ) != 0)
//    {
//        rotateAboutVector(mXAxis.VP(plane.getVectorInPlane()), toDegree(plane.getVectorInPlane().getAngleTo(X()) ));//This rotate only around Z
//    }
//    setOrigin(Origin);
}

void AxisSystem::orientZInPlaneAndXOrthogonal(const Plane& plane)
{
//
//    Point Origin(this->getOrigin());
//    this->setOrigin(0,0,0);
//
//    //Orient the Z axis in the plane....
//    if(plane.getVectorInPlane().getAngleTo( Z() ) != 0)
//    {
//        rotateAboutVector(mZAxis.VP(plane.getVectorInPlane()), toDegree(plane.getVectorInPlane().getAngleTo(Z()) ));
//    }
//
//    //Make X Orthogonal to this plane....
//    if(plane.getNormal().getAngleTo( Y() ) != 0)
//    {
//        rotateAboutZ(toDegree(plane.getNormal().getAngleTo(Y()) ));
//    }
//    setOrigin(Origin);
}

void AxisSystem::orientZInPlaneAndYOrthogonal(const Plane& plane)
{
//    Point Origin(this->getOrigin());
//    this->setOrigin(0,0,0);
//
//    //Orient the Z axis in the plane....
//    if(plane.getVectorInPlane().getAngleTo( Z() ) != 0)
//    {
//        rotateAboutVector(mZAxis.VP(plane.getVectorInPlane()), toDegree(plane.getVectorInPlane().getAngleTo(Z()) ));
//    }
//
//    //Make Y Orthogonal to this plane....
//    if(plane.getNormal().getAngleTo( X() ) != 0)
//    {
//        rotateAboutZ(toDegree(plane.getNormal().getAngleTo(X()) ));
//    }
//    setOrigin(Origin);
}

void AxisSystem::invert()
{
//    //Axes by axes
//    Point Origin(this->getOrigin());
//    this->setOrigin(0,0,0);
//    mXAxis.setX(-X().x());    mXAxis.setY(-X().y());    mXAxis.setZ(-X().z());
//    mYAxis.setX(-Y().x());    mYAxis.setY(-Y().y());    mYAxis.setZ(-Y().z());
//    mZAxis.setX(-Z().x());    mZAxis.setY(-Z().y());    mZAxis.setZ(-Z().z());
//    setOrigin(Origin);
}

void AxisSystem::resetOrientation()
{
    //Axes by axes
    Point Origin(this->getOrigin());
    this->setOrigin(0,0,0);
    mXAxis.setX(1);    mXAxis.setY(0);    mXAxis.setZ(0);
    mYAxis.setX(0);    mYAxis.setY(1);    mYAxis.setZ(0);
    mZAxis.setX(0);    mZAxis.setY(0);    mZAxis.setZ(1);
    setOrigin(Origin);

    notifyObservers(SubjectEvent::UpdateCoreData);
}

void AxisSystem::setAxisLength(double length)
{
    /*Do not change orientation, only the actual length of each individual vector*/
    if(length)
    {
        Point CurrOrigin(mOrigin);

        //Translate to mOrigin
        setOrigin(0,0,0);

        double xFactor = length/X().getMagnitude();

        mXAxis.setTip(xFactor * X().x(), xFactor * X().y(), xFactor * X().z());
        mYAxis.setTip(xFactor * Y().x(), xFactor * Y().y(), xFactor * Y().z());
        mZAxis.setTip(xFactor * Z().x(), xFactor * Z().y(), xFactor * Z().z());
        setOrigin(CurrOrigin);
    }
    notifyObservers(SubjectEvent::UpdateCoreData);
}

void AxisSystem::setAxisRadius(double radius)
{
    /*Do not change orientation, only the actual radius of each individual axes*/
    if(radius > 0)
    {
//        mAxisView.setAxesRadius(radius);
//        update();
    }
}

}
