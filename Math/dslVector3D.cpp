#pragma hdrstop
#include <cmath>
#include "dslVector3D.h"
#include "dslMatrix.h"
#include "dslEulerMatrix.h"
#include "dslMathUtils.h"

namespace dsl
{

using namespace std;

//---------------------------------------------------------------------------
Vector3D::Vector3D(double x, double y, double z)
:
Subject("Vector3D"),
mTip(x,y,z),
mColor(255,255,0)
{}

Vector3D::Vector3D(const Point& tip, const Point& origin)
:
mTip(tip)
{
    mPosition = origin;
}

Vector3D::Vector3D(const Vector3D& vec)
{
    mPosition = vec.getPosition();
    mTip  = vec.getTip();
}

Vector3D::operator Point()
{
    return getTip();
}

Vector3D& Vector3D::operator=(const Vector3D& rhs)
{
    if(&rhs == this)
    {
        return *this;
    }

    mTip = rhs.getTip();
    mPosition = rhs.getPosition();
    return *this;
}

Vector3D::~Vector3D()
{
    notifyObservers(SubjectEvent::SubjectBeingDestroyed);
}

Point& Vector3D::getTip()
{
    return mTip;
}

Point Vector3D::getTip() const
{
    return mTip;
}

void Vector3D::setTip(const Point& ptn)
{
    mTip = ptn;
    notifyObservers(SubjectEvent::UpdateCoreData);
}

void Vector3D::setTip(double x, double y, double z)
{
    mTip = Point(x, y, z);
    notifyObservers(SubjectEvent::UpdateCoreData);
}

void Vector3D::set(const Point& ptn)
{
    set(ptn.x(), ptn.y(), ptn. z());
}

void Vector3D::set(double x, double y, double z)
{
    mTip.setX(x);
    mTip.setY(y);
    mTip.setZ(z);
    notifyObservers(SubjectEvent::UpdateCoreData);
}

void Vector3D::setX(double x)
{
    mTip.setX(x);
    notifyObservers(SubjectEvent::UpdateCoreData);
}

void Vector3D::setY(double y)
{
    mTip.setY(y);
    notifyObservers(SubjectEvent::UpdateCoreData);
}

void Vector3D::setZ(double z)
{
    mTip.setZ(z);
    notifyObservers(SubjectEvent::UpdateCoreData);
}

void Vector3D::setMagnitude(double m)
{
    normalize();
    (*this) = (*this) * m;
    notifyObservers(SubjectEvent::UpdateCoreData);
}

double Vector3D::getMagnitude() const
{
    return mTip.getLength();
}

double Vector3D::operator[](int index)
{
    if(index >=0 && index < 3)
    {
        return mTip[index];
    }

    throw("Bad Index..");
}
Vector3D Vector3D::operator*(double s)
{
    Vector3D newVec(x() * s, y() * s, z() * s);
    newVec.mPosition = mPosition;
    return newVec;
}

Vector3D Vector3D::operator/(double s)
{
    Vector3D newVec(x() / s, y() / s, z() / s);
    return newVec;
}

Vector3D Vector3D::operator+(const Vector3D &v) const
{
    return Vector3D(this->x() + v.x(), this->y() + v.y(), this->z() + v.z());
}

Vector3D Vector3D::operator-(const Vector3D &v) const
{
    return Vector3D(this->x() - v.x(), this->y() - v.y(), this->z() - v.z());
}

//Friend
Vector3D operator*(const double& s, const Vector3D& v)
{
    Vector3D temp(v*s);
    return temp;
}

Vector3D operator*(const dslMatrix<double> &mat, const Vector3D& v)
{
    Vector3D temp;
    temp.setX( mat[1][1]*v.x()  + mat[1][2]*v.y() + mat[1][3]*v.z());
    temp.setY( mat[2][1]*v.x()  + mat[2][2]*v.y() + mat[2][3]*v.z());
    temp.setZ( mat[3][1]*v.x()  + mat[3][2]*v.y() + mat[3][3]*v.z());
    return temp;
}

void Vector3D::orientAlong(const Vector3D& vec)
{
    //Orient this vector along vec..
    Vector3D RotAboutVec (this->VP(vec));

    double angle = toDegree(this->getAngleTo(vec));
    this->rotate(angle, RotAboutVec);
}

void Vector3D::orientAntiParallellTo(const Vector3D& vec)
{}

/*** The vector product ***/
Vector3D Vector3D::VP(const Vector3D& v2) const
{
    Vector3D result;
    result.setX(y() * v2.z() - z() * v2.y());
    result.setY(z() * v2.x() - x() * v2.z());
    result.setZ(x() * v2.y() - y() * v2.x());
    return result;
}

//Translating a vector does nothing.. however,
//if we are to visualize the vector, translate its 'position'
void Vector3D::translate(const Point& pt)
{
    mPosition = mPosition + pt;
    notifyObservers(SubjectEvent::UpdateCoreData);
}

void Vector3D::setPosition(double x, double y, double z)
{
    mPosition.set(x,y,z);
    notifyObservers(SubjectEvent::UpdateCoreData);
}

void Vector3D::setPosition(const Point& p)
{
    setPosition(p.x(), p.y(), p.z());
}

void Vector3D::rotateX(double ang)
{
    double angle = toRadians(ang);
    mTip.set(x(), cos(angle)*y() - sin(angle)*z(), sin(angle)*y() + cos(angle)*z());
    notifyObservers(SubjectEvent::UpdateCoreData);
}

void Vector3D::rotateY(double ang)
{
    double angle = toRadians(ang);
    mTip.set(cos(angle)*x() + sin(angle)*z(), y(), -sin(angle)*x() + cos(angle)*z());
    notifyObservers(SubjectEvent::UpdateCoreData);
}

void Vector3D::rotateZ(double ang)
{
    double angle = toRadians(ang);
    mTip.set(cos(angle)*x()  -  sin(angle)*y(),  sin(angle)*x()  +  cos(angle)*y(), z());
    notifyObservers(SubjectEvent::UpdateCoreData);
}

void Vector3D::rotate(double angle, const Vector3D& v2)
{
    this->mSuspendObserverUpdates = true;
    //Rotate this by angle about point2
    EulerMatrix eMatrix;
    double Fi, Theta;

    //Get EulerAngles
    v2.Euler(Fi,Theta);
    eMatrix.SetMatrices(Fi,Theta);

    //Transform the this vector to the system of v2
    Vector3D temp = eMatrix.GetTMatrix() * (*this);
    set(temp.x(), temp.y(), temp.z());

    //Rotate this around mZ with angle
    rotateZ(angle);

    //transform back
    temp = eMatrix.GetINVTMatrix() * (*this);
    set(temp.x(), temp.y(), temp.z());

    this->mSuspendObserverUpdates = false;
    notifyObservers(SubjectEvent::UpdateCoreData);
}

void Vector3D::Euler(double& Fi, double& Theta) const
{
    if(x() == 0)
    {
        Fi = gPiBy2;
    }

    if(y() == 0)
    {
        if(x() < 0)
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
        Fi = -atan2(x(), y());
    }

    if(z() == 0)
    {
        Theta = -gPiBy2;
    }
    else
    {
        Theta = -acos(z()/getMagnitude());
    }
}

ostream& operator<<(ostream &stream, Vector3D &out)
{
    stream<< out.getTip();
    return stream;
}

Vector3D Vector3D::getUnitVector() const
{
    double m = getMagnitude();
    if(m)
    {
        Vector3D temp(mTip.x()/m, mTip.y()/m, mTip.z()/m);
        return temp;
    }
    throw("Bad vector!");
}

double Vector3D::x() const
{
    return mTip.x();
}

double Vector3D::y() const
{
    return mTip.y();
}

double Vector3D::z() const
{
    return mTip.z();
}

double Vector3D::SP(const Vector3D& vec2) const
{
    //Scalar product
    Point p1 = getTip();
    Point p2 = vec2.getTip();
    return p1.x() * p2.x() + p1.y() * p2.y() + p1.z() * p2.z();
}

double Vector3D::getAngleTo(const Vector3D& v2) const
{
    double denomi = getMagnitude() * v2.getMagnitude();
    if(!denomi)
    {
        return 0;
    }

    //angle = atan2(norm(cross(a,b)),dot(a,b));
    double dotP = this->SP(v2);
    Vector3D xP = this->VP(v2);
    double normXP = xP.getMagnitude();
    double angle = atan2(normXP, dotP);
    return angle;


//    double test = this->SP(v2)/denomi;
//    if(test >= 0)
//    {
//        if(fabs(test - 1) > 0.000000001 )
//        {
//            double val = this->SP(v2)/(getMagnitude() * v2.getMagnitude());
//            return acos(val);
//        }
//    }
//    else
//    {
//        if(fabs(test + 1) > 0.000000001)
//        {
//            return acos(this->SP(v2)/(getMagnitude()*v2.getMagnitude()));
//        }
//        else
//        {
//
//        }
//    }
//    return 0;
}

//This does not seem right??
Vector3D Vector3D::getOrthogonalVector() const
{
    //Returna an orthogonal vector to this vector, if this vector is not zero
    if(isZero())
    {
        return Vector3D(0,0,0);
    }
    else
    {
        Vector3D temp(*this);
        Vector3D result(this->VP(temp));
        result.normalize();
        return result;
    }
}

void Vector3D::normalize()
{
    double length = getMagnitude();
    if(length)
    {
        setX(x() / length);
        setY(y() / length);
        setZ(z() / length);
    }
}

bool Vector3D::isZero() const
{
    Vector3D temp(*this);
    temp.roundOff();

    return ( temp.x() == temp.y() && temp.y() == temp.z() && temp.z() == 0.) ? true : false;
}

void Vector3D::roundOff()
{
    if(fabs(x()) < 1.e-10)
    {
       setX(0);
    }

    if(fabs(y()) < 1.e-10)
    {
       setY(0);
    }

    if(fabs(z()) < 1.e-10)
    {
       setZ(0);
    }
}

void Vector3D::setShaftRadius(double radius)
{
//    getVector3DView()->setShaftRadius(radius);
}

void Vector3D::setShaftResolution(int nrOfSides)
{
//    getVector3DView()->setShaftResolution(nrOfSides);
}

Vector3D operator*(const Vector3D& vec, double num)
{
    Vector3D temp;
    temp.set(vec.x() * num, vec.y() * num, vec.z() * num);
    return temp;
}

void Vector3D::setColor(const Color& clr)
{
    mColor = clr;
    notifyObservers(SubjectEvent::UpdateColor);
}

Color Vector3D::getColor()
{
    return mColor;
}

Point Vector3D::getPosition() const
{
    return mPosition;
}

}
