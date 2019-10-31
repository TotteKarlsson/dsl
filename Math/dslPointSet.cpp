#pragma hdrstop
#include <iostream>
#include <fstream>
#include "dslPointSet.h"

namespace dsl
{

PointSet::PointSet(const PointSet &In)
{
    setNumberOfPoints(In.count());
    for(unsigned int index = 0; index < mPointSet.size(); index++)
    {
        Point aPoint = In[index];
        setPoint(index, aPoint);
    }
}

PointSet::~PointSet()
{
    clear();
}

PointSet& PointSet::operator=(const PointSet& rhs)
{
    if(&rhs == this)
    {
        return *this;
    }

    mPointSet = rhs.mPointSet;
    return (*this);
}

void PointSet::clear()
{
    mPointSet.clear();
}

Point& PointSet::operator[](unsigned int i)
{
    return (mPointSet.at(i));
}

const Point& PointSet::operator[](unsigned int i) const
{
    return (mPointSet.at(i));
}

PointSet::PointSet(int NrOfPoints)
{
    mPointSet.resize(NrOfPoints);
}

void PointSet::setPoint(int index, const Point& ptn)
{
    mPointSet.at(index).set(ptn);
}

const Point& PointSet::getPoint(int index) const
{
    return mPointSet.at(index);
}

Point& PointSet::getPoint(int index)
{
    return mPointSet.at(index);
}

void PointSet::setPoint(int index, double X, double Y, double Z)
{
    mPointSet.at(index).setX(X);
    mPointSet.at(index).setY(Y);
    mPointSet.at(index).setZ(Z);
}

void PointSet::insertNextPoint(double X, double Y, double Z)
{
    Point pt(X,Y,Z);
    mPointSet.push_back(pt);
}

void PointSet::insertNextPoint(const Point& point)
{
    mPointSet.push_back(point);
}

void PointSet::setNumberOfPoints(unsigned int nroftriplets)
{
    mPointSet.resize(nroftriplets);
}

size_t PointSet::count() const
{
    return mPointSet.size();
}

size_t PointSet::size() const
{
    return count();
}


void PointSet::getPointSetFromFile(string& /*FileName*/)
{
//   fstream InpFile;
//   InpFile.open(FileName.c_str(),ios::in);
//   int NrOfPoints;
//   string temp = "Number of Points =";
//   GetParameterInFile(FileName, temp, NrOfPoints);
//   SetNumberOfPoints(NrOfPoints);
//   double X,Y,Z;
//   char Trash[100];
//   InpFile.getline(Trash,100);
//
//   for(int i = 0; i < NrOfPoints; i++){
//    InpFile>>X;
//    InpFile>>Y;
//    InpFile>>Z;
//    setPoint(i,X,Y,Z);
//   }
//   InpFile.close();
}

void PointSet::addPointSetFromFile(string& /*FileName*/)
{
//   int NrOfPoints;
//   double X,Y,Z;
//   char Trash[100];
//   string temp = "Number of Points =";
//   GetParameterInFile(FileName, temp, NrOfPoints);
//   fstream InpFile;
//   InpFile.open(FileName.c_str(),ios::in);
//   InpFile.getline(Trash,100);
//
//   for(int i = 1; i < NrOfPoints+1; i++){
//          InpFile>>X;
//          InpFile>>Y;
//          InpFile>>Z;
//          InsertNextPoint(X,Y,Z);
//   }
//   InpFile.close();
}

void PointSet::writePointSetToFile(string& FileName)
{
    fstream fs;
    fs.open(FileName.c_str(),ios::out);
    fs<<"Number of Points = "<<mPointSet.size()<<"\n";

    for(unsigned int i = 0; i < mPointSet.size(); i++)
    {
        fs<<mPointSet.at(i).x()<<" " <<mPointSet.at(i).y()<<" "
         <<mPointSet.at(i).z()<<"\n";
    }

   fs.close();
}

string toString(const PointSet& ps)
{
    return gEmptyString;
}

}
