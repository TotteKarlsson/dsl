#pragma hdrstop
#include <cmath>
#include "dslPoint.h"
#include "dslMatrix.h"
#include "dslEulerMatrix.h"
#include "dslMathUtils.h"

using namespace std;

namespace dsl
{

Point::Point(const Point& point)
{
    mX = point.x();
    mY = point.y();
    mZ = point.z();
    mIsMoved = false;
}

Point::Point(const vector<double>& p)
{
    if(p.size() == 3)
    {
        mX = p[0];
        mY = p[1];
        mZ = p[2];
    }
    mIsMoved = false;
}

string Point::getTypeName() const
{
    return "point";
}

Point::Point(double x, double y, double z)
:
mIsMoved(false),
mX(x),
mY(y),
mZ(z)
{}

Point::~Point()
{}

Point& Point::operator=(const Point& point)
{
    mX = point.x();
    mY = point.y();
    mZ = point.z();
    return *this;
}

void Point::addToPoint(const Point& point)
{
    mX = mX + point.mX;
    mY = mY + point.mY;
    mZ = mZ + point.mZ;
}

void Point::addToPoint(double x, double y, double z)
{
    mX = mX + x;
    mY = mY + y;
    mZ = mZ + z;
}

void Point::set(const Point& point)
{
    mX = point.mX;
    mY = point.mY;
    mZ = point.mZ;
}

void Point::set(double x, double y, double z)
{
    mX = x;
    mY = y;
    mZ = z;
}

void Point::zero()
{
    mX = mY = mZ = 0;
}

Point operator/(const Point& point, double div)
{
    Point t;
    t.setX( point.x() / div);
    t.setY( point.y() / div);
    t.setZ( point.z() / div);
    return t;

}
Point operator*(const dslMatrix<double> &mat, const Point& point)
{
    Point temp;
    temp.setX( mat[1][1]*point.x()  + mat[1][2]*point.y() + mat[1][3]*point.z());
    temp.setY( mat[2][1]*point.x()  + mat[2][2]*point.y() + mat[2][3]*point.z());
    temp.setZ( mat[3][1]*point.x()  + mat[3][2]*point.y() + mat[3][3]*point.z());
    return temp;
}

const Point operator*(const Point& ptn, double num)
{
    Point temp;
    temp.setX(ptn.x() * num);
    temp.setY(ptn.y() * num);
    temp.setZ(ptn.z() * num);
    return temp;
}

const Point operator*(double num, const Point& point)
{
    Point temp;
    temp.setX(point.x() * num);
    temp.setY(point.y() * num);
    temp.setZ(point.z() * num);
    return temp;
}

void Point::normalize()
{
    double length = getLength();
    if(length)
    {
        mX = mX / length;
        mY = mY / length;
        mZ = mZ / length;
    }
}

//To be deprecated
double Point::getLength() const
{
    return sqrt(mX*mX + mY*mY + mZ*mZ);
}

double Point::distanceFromOrigin() const
{
   return sqrt(mX*mX + mY*mY + mZ*mZ);
}

double Point::distanceTo(const Point& pt2) const
{
    //  double dist;
    Point point;
    point = pt2 - *this;
    return point.getLength();
}

bool Point::isAtOrigin()
{
    return ( mX == mY && mY == mZ && mZ == 0.) ? true : false;
}

const Point Point::operator+(const Point &point) const
{
    return Point(mX + point.x(), mY + point.y(), mZ + point.z());
}

Point Point::operator-(const Point &point) const
{
    return Point(mX - point.x(), mY - point.y(), mZ - point.z());
}

void Point::rotateX(double ang)
{
    double angle = toRadians(ang);
    set(mX,
        cos(angle)*mY - sin(angle)*mZ,
        sin(angle)*mY + cos(angle)*mZ);
}

void Point::rotateY(double ang)
{
    double angle = toRadians(ang);
    set(cos(angle)*mX + sin(angle)*mZ,
        mY,
        -sin(angle)*mX + cos(angle)*mZ);
}

void Point::rotateZ(double ang)
{
    double angle = toRadians(ang);
    set(cos(angle)*mX  -  sin(angle)*mY,
        sin(angle)*mX  +  cos(angle)*mY,
        mZ);
}

void Point::rotate(double angle, const Point& P2)
{
    //Rotate this by angle about point2
    double Fi, Theta;
    EulerMatrix eMat;

    //Get EulerAngles
    P2.getEulerAngles(Fi,Theta);
    eMat.SetMatrices(Fi,Theta);

    //Transform "this" vector to the system of P2
    set(eMat.GetTMatrix() * (*this));

    //Rotate this around mZ with angle
    rotateZ(angle);

    //transform back
    set(eMat.GetINVTMatrix() * (*this));
}

void Point::getEulerAngles(double& Fi, double& Theta) const
{
    if(mX == 0)
    {
        Fi = gPiBy2;
    }

    if(mY == 0)
    {
        if(mX <= 0)
        {
            Fi = gPiBy2;
        }
        else
        {
            Fi = -gPiBy2;
        }
    }
    else
    {
        Fi = -atan2(mX,mY);
    }

    if(mZ == 0)
    {
        Theta = -gPiBy2;
	}
	else
	{
		Theta = -acos(mZ/getLength());
	}
}

double& Point::operator[](int index)
{
	if(index == 0)
	{
		return mX;
	}
	if(index == 1)
	{
		return mY;
	}
	if(index == 2)
	{
		return mZ;
	}
	else
	{
		throw("Out of bounds in point!");
	}
}

double Point::operator[](int index) const
{
	if(index == 0)
	{
		return mX;
	}
	if(index == 1)
	{
		return mY;
	}
	if(index == 2)
	{
		return mZ;
	}
	else
	{
		throw("Out of bounds in point!");
	}
}

double& Point::xRef()
{
	return mX;
}

double& Point::yRef()
{
	return mY;
}

double& Point::zRef()
{
    return mZ;
}

double Point::x() const
{
    return mX;
}

double Point::y() const
{
    return mY;
}

double Point::z() const
{
    return mZ;
}

void Point::setX(double x)
{
    mX = x;
}

void Point::setY(double y)
{
    mY = y;
}

void Point::setZ(double z)
{
    mZ = z;
}

void Point::setUnMoved()
{
    mIsMoved = false;
}

void Point::setMoved()
{
    mIsMoved = true;
}

bool Point::isMoved()
{
    return mIsMoved;
}

string Point::asString(const char& delimiter) const
{
    return toString(*this);
}

XMLElement* Point::addToXMLDocument(XMLDocument& doc, XMLNode* docRoot)
{
//    //Create XML for saving to file
    XMLElement* pointNode  = doc.NewElement(toLowerCase(getTypeName()).c_str());
//    XMLNode*    rootNode = doc.InsertFirstChild(pointNode);
//
//    //Attributes
//    //    pointNode->SetAttribute("id", getID().toString().c_str());
//
//    //Elements
//    XMLElement* elem = doc.NewElement("x");
//    pointNode->InsertFirstChild(elem);
//        elem->SetText(toString(x()).c_str());
//    pointNode->InsertEndChild(elem);
//
//    elem = doc.NewElement("y");
//    pointNode->InsertFirstChild(elem);
//        elem->SetText(toString(x()).c_str());
//    pointNode->InsertEndChild(elem);
//
//    elem = doc.NewElement("z");
//    pointNode->InsertFirstChild(elem);
//        elem->SetText(toString(x()).c_str());
//    pointNode->InsertEndChild(elem);
//
//    pointNode->InsertEndChild(rootNode);
//    docRoot->InsertEndChild(pointNode);
    return pointNode;
}

ostream& operator<<(ostream& stream, const Point& ptn)
{
    stream<<toString(ptn);
    return stream;
}

double getDistance(const Point& p1, const Point& p2)
{
    Point p(p2-p1);
    return sqrt(p.x() * p.x() + p.y() * p.y() + p.z() * p.z());
}

//Not a member function..
string toString(const Point& ptn, const char delimiter)
{
    stringstream ss;
    ss << "(" << ptn.x() << delimiter << ptn.y() << delimiter << ptn.z() << ")";
    return ss.str();
}

}
