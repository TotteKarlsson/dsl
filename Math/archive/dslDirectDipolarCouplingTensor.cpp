
#pragma hdrstop
#include <fstream>
#include "dslMathUtils.h"
#include "dslPoint.h"
#include "dslAtom.h"
#include "dslAxisSystem.h"
#include "dslBond.h"
#include "dslDirectDipolarCouplingTensor.h"
#include "dslEulerAngleTriplet.h"
#include "dslISTensor.h"
#include "dslUtils.h"


namespace dsl
{

DirectDipolarCouplingTensor::DirectDipolarCouplingTensor()
{
    /*** Default constructor ***/
    mDDCpl = 0;
    mAxes = new AxisSystem;
    mAxes->X().set(.2,0,0);
    mAxes->Y().set(0,0.2,0);
    mInP  = new ISTensor;
    mInC  = new ISTensor;
    mInR  = new ISTensor;
    mInL  = new ISTensor;
    mWignerStruc = nullptr;
}

DirectDipolarCouplingTensor::DirectDipolarCouplingTensor(Bond* parentBond)
{
    /*** Default constructor ***/
    mDDCpl = 0;
    mAxes = new AxisSystem;
    mAxes->X().set(.2,0,0);
    mAxes->Y().set(0,0.2,0);

    Point origin(parentBond->getAtom1()->getCenter().plus(parentBond->getAtom2()->getCenter()));
    mAxes->setOrigin(origin.x()/2,origin.y()/2,origin.z()/2);
    mAxes->orientZAlongVector(*parentBond->getBondVector());

    mInP  = new ISTensor;
    mInC  = new ISTensor;
    mInR  = new ISTensor;
    mInL  = new ISTensor;
    mWignerStruc = nullptr;
//    explorer = parentBond->getExplorer();
}

DirectDipolarCouplingTensor::~DirectDipolarCouplingTensor()
{
    /*** Default destructor ***/
    delete mAxes;
    delete mInP;
    delete mInC;
    delete mInR;
    delete mInL;
}

ISTensor* DirectDipolarCouplingTensor::getCplInP()
{
  return mInP;
}

ISTensor* DirectDipolarCouplingTensor::getCplInC()
{
  return mInC;
}

ISTensor* DirectDipolarCouplingTensor::getCplInR()
{
  return mInR;
}

ISTensor* DirectDipolarCouplingTensor::getCplInL()
{
  return mInL;
}

AxisSystem* DirectDipolarCouplingTensor::getAxes()
{
  if(!mAxes)
    mAxes = new AxisSystem;
//
//  if(explorer)
//    mAxes->UseExplorer(explorer);

  return mAxes;
}

double& DirectDipolarCouplingTensor::getCouplingConstant()
{
  return mDDCpl;
}

void DirectDipolarCouplingTensor::setEulerAnglesPToC(const EulerAngleTriplet& angle)
{
  mPToC.set(angle);
}

void DirectDipolarCouplingTensor::setCouplingConstant(double newmDDCpl)
{
  mDDCpl = newmDDCpl/(gTwoPi);//that is, mDDCpl is in Hz
}

void DirectDipolarCouplingTensor::getInput(string& /*File*/, string& /*Sample*/, string& /*CplNr*/)
{

  //GetParameterInFile(File, Sample, CplNr , "dd coupling =", mDDCpl);
  //GetParameterInFile(File, Sample, CplNr , "PC = ", mPToC);
  setup();
  rotateFromPASToCrystalFrame();
}

void DirectDipolarCouplingTensor::setup()
{
//  mDDCpl*=(2*gPi);
  /*** Setup DD in PAS Frame ***/
//  setupInPASFrame();
}

//void DirectDipolarCouplingTensor::setupInPASFrame()
//{
//  /*** Setup DD tensor in PAS frame ***/
//  mInP->Element(-2) = (0,0);
//  mInP->Element(-1)= (0,0);
//  mInP->Element(0) = sqrt(6.0)*mDDCpl*(2.0*gPi);
//  mInP->Element(1)  = 0.;
//  mInP->Element(2)  = 0.;
//}

void DirectDipolarCouplingTensor::setupInPASFrame(double CplConstant)
{
  //  CplConstant/=(2*gPi); //Check this!!!!!!!!!!!
  /*** Setup DD tensor in PAS frame ***/
  mInP->Element(-2) = 0.;
  mInP->Element(-1) = 0.;
  mInP->Element(0)  = sqrt(6.0)*CplConstant;
//  mInP->Element(0)  = CplConstant;
  mInP->Element(1)  = 0.;
  mInP->Element(2)  = 0.;
}

//void DirectDipolarCouplingTensor::rotate(const FRAMETRANSFORMATION& frameTransformation, const EulerAngleTriplet *angle)
//{
//
//  switch(frameTransformation){
//    case PASToCrystal:
//      mInC->setTensor(mInP->rotate(angle));
//    break;
//
//    case PASToRotor:
//      mInC->setTensor(mInP->rotate(angle));
//    break;
//
//    case PASToLab:
//      mInL->setTensor(mInP->rotate(angle));
//    break;
//
//    case CrystalToRotor:
//      mInR->setTensor(mInC->rotate(angle));
//    break;
//
//    case CrystalToLab:
//      mInL->setTensor(mInC->rotate(angle));
//    break;
//
//    case RotorToLab:
//      mInL->setTensor(mInR->rotate(angle));
//    break;
//
//    default:
//      throw("Frame transformation not defined!!..");
//    break;
//  }
//}

void DirectDipolarCouplingTensor::rotate(const FRAMETRANSFORMATION& frameTransformation, const EulerAngleTriplet &angle){

  switch(frameTransformation)
  {
    case PASToCrystal:
      mInC->setTensor(mInP->rotate(angle));
    break;

    case PASToRotor:
      mInC->setTensor(mInP->rotate(angle));
    break;

    case CrystalToRotor:
      mInR->setTensor(mInC->rotate(angle));
    break;

    default:
      throw("Frame transformation not defined!!..");
    break;
  }
}

void DirectDipolarCouplingTensor::rotateFromPASToCrystalFrame()
{
    mInC->getTensor() = mInP->rotate(mPToC);
}

void DirectDipolarCouplingTensor::rotateFromPASToCrystalFrame(const EulerAngleTriplet& EUL){
  mInC->getTensor() = mInP->rotate(EUL);
}

void DirectDipolarCouplingTensor::rotateFromPASToCrystalFrame(double a, double b, double g){

  mInC->getTensor() = mInP->rotate(a,b,g);
}

void DirectDipolarCouplingTensor::rotateFromPASToMoleculeFrame(const EulerAngleTriplet& EUL){
  mInC->getTensor() = mInP->rotate(EUL);
}

void DirectDipolarCouplingTensor::rotateFromPASToRotorFrame(const EulerAngleTriplet& EUL){
  mInR->getTensor() = mInP->rotate(EUL);
}

void DirectDipolarCouplingTensor::rotateFromPASToLabFrame(const EulerAngleTriplet& EUL){
  mInL->getTensor() = mInP->rotate(EUL);
}

void DirectDipolarCouplingTensor::rotateFromPASToMoleculeFrame(double a, double b, double g){
  mInC->getTensor() = mInP->rotate(a,b,g);
}

void DirectDipolarCouplingTensor::rotateFromCrystalToRotorFrame(const EulerAngleTriplet& EUL){
  mInR->getTensor() = mInC->rotate(EUL);
}

void DirectDipolarCouplingTensor::rotateFromCrystalToLabFrame(const EulerAngleTriplet& EUL){
  mInL->getTensor() = mInC->rotate(EUL);
}

void DirectDipolarCouplingTensor::rotateFromMoleculeToRotorFrame(const EulerAngleTriplet& EUL){
  mInR->getTensor() = mInC->rotate(EUL);
}

void DirectDipolarCouplingTensor::rotateFromRotorToLabFrame(const EulerAngleTriplet& EUL){
  mInL->getTensor() = mInR->rotate(EUL);
}

ostream &operator<<(ostream &stream, DirectDipolarCouplingTensor& out)
{
  stream<<"DD-Coupling = \t"<<out.getCouplingConstant()/(2.0*gPi)<<" Hz\n";
  stream<<"PC = " <<out.getAnglesPToC().getAlfa()
        <<","     <<out.getAnglesPToC().getBeta()
        <<","     <<out.getAnglesPToC().getGamma()<<"\n";
  return stream;
}



}
