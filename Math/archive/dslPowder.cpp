
#pragma hdrstop
#include "dslEulerAngleTriplet.h"
#include "dslEulerAngleSet.h"

#include "dslPowder.h"
#include "dslStringUtils.h"


namespace dsl
{

dslPowder::dslPowder(){
  angleSet = new EulerAngleSet;
//  angleSet->InsertAngle(EulerAngleTriplet(0,0,0));
  type = singleXtal;
}

dslPowder::~dslPowder(){

}

int dslPowder::GetNumberOfAngles(){
    return 0;// angleSet->GetNumberOfAngles();
}

EulerAngleTriplet* dslPowder::GetAngle(int index){
    return nullptr;// angleSet->GetAngle(index);
}

POWDERTYPE dslPowder::GetType()
{
  return type;
}

EulerAngleSet* dslPowder::GetAngleSet(){
  if(!angleSet)
    angleSet = new EulerAngleSet;
  return angleSet;
}

void dslPowder::SetAngleSet(EulerAngleSet* set){
  angleSet = set;
  type = unknownType;
}

void dslPowder::SetSingleCrystal(const EulerAngleTriplet* angle){
//  GetAngleSet()->InsertAngle(angle);
  type = singleXtal;
}

void dslPowder::ReadFromFile(const string& fileName){
  type = orientationsFromFile;

  angleFileName = getFileName(fileName);
//  GetAngleSet()->GetAngleSetFromFile(angleFileName.c_str());
}

void dslPowder::WriteToFile(const string& /*fileName*/)
{

}

void dslPowder::GenerateGridOrientations(int nrA, int nrB, int nrG){
  nrAlfa = nrA;
  nrBeta = nrB;
  nrGamma = nrG;
//  GetAngleSet()->GenerateSteppedAngles(nrAlfa, nrBeta, nrGamma);
  type = gridOrientations;
}
string dslPowder::GetFileName(){return angleFileName;}
}
