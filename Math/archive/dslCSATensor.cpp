#pragma hdrstop
#include <cmath>
#include "dslMathUtils.h"
#include "dslPoint.h"
#include "dslAxisSystem.h"
#include "dslCSATensor.h"
#include "dslEulerAngleTriplet.h"
#include "dslISTensor.h"
#include "dslUtils.h"
#include "dslWigner.h"

namespace dsl
{

CSATensor::CSATensor(const Point& center)
:
mPosition(center)
{

    mXX = mYY = mZZ = 0;
    mSigmaIso = mSigmaAniso = mAsymmetryParameter = 0;
    mOmegaAniso = 0;
    mOmegaIso = 0;
    mEnvironment = nullptr;
    mCSAAxes    = new AxisSystem(mPosition.x(), mPosition.y(), mPosition.z());
    mInP         = new ISTensor;
    mInC         = new ISTensor;
    mInR         = new ISTensor;
    mInL         = new ISTensor;
    mWignerStruc = new wigner_struc;
    mUseAssymetryParameters    = 0;
}

CSATensor::~CSATensor()
{
    delete mInP;
    delete mCSAAxes;
    delete mInC;
    delete mInR;
    delete mInL;
    delete mWignerStruc;
}

void CSATensor::set(const CSATensor& cs)
{
  mAsymmetryParameter  = cs.getAsymmetry();
  mOmegaAniso = cs.getOmegaAniso();
  mOmegaIso   = cs.getOmegaIso();
  mPToC.set(cs.getAnglesPToC());
}


void CSATensor::setXX(double val)
{
  mXX = val;
}

void CSATensor::setYY(double val)
{
  mYY = val;
}

void CSATensor::setZZ(double val)
{
  mZZ = val;
}

void CSATensor::setAssParameter(double val)
{
  mAsymmetryParameter = val;
}

void CSATensor::setOmegaAniso(double val)
{
  mOmegaAniso = val;
}

void CSATensor::setOmegaIso(double val)
{
  mOmegaIso = val;
}

ISTensor* CSATensor::getCSAInP()
{
  if(!mInP)
    mInP = new ISTensor;
  return mInP;
}

ISTensor* CSATensor::getCSAInC()
{
  if(!mInC)
    mInC = new ISTensor;
  return mInC;
}

ISTensor* CSATensor::getCSAInR()
{
  if(!mInR)
    mInR = new ISTensor;
  return mInR;
}

ISTensor* CSATensor::getCSAInL()
{
  if(!mInL)
    mInL = new ISTensor;
  return mInL;
}

AxisSystem* CSATensor::getCSAAxes()
{
  if(!mCSAAxes)
  {
    mCSAAxes = new AxisSystem;
  }

//  if(explorer)
//    mCSAAxes->UseExplorer(explorer);
  return mCSAAxes;
}

void CSATensor::setEnvironment(Environment *env)
{
    mEnvironment = env;
}

void CSATensor::setup(double LF)
{
  /*** Hertz in input file, convert to rad/sec ***/
  setupInField(LF);

    /*** Rotate to crystal frame ***/
  //RotateFromPASToCrystalFrame();
  mPToC.convertToRadians();
  mInC->setTensor(mInP->rotate(mPToC));
  mCSAAxes->rotateZYZ(mPToC);
}

void CSATensor::setupInField(double larmorFreq)
{
  if(mUseAssymetryParameters)
  {
    mSigmaIso = 1./3. *(mXX+mYY+mZZ);
    mSigmaAniso = mZZ - mSigmaIso;
    if((mZZ-mSigmaIso) != 0)
      mAsymmetryParameter = (mYY-mXX)/(mZZ-mSigmaIso);

    double LF = larmorFreq / (2.*gPi);
    mOmegaAniso = -LF * mSigmaAniso * 1.e-6 ;
    mOmegaIso   = -LF * mSigmaIso * 1.e-6;
  }

    /*** Hertz in input file, convert to rad/sec ***/
    //  mOmegaIso   *= 2.0*gPi;
    //  mOmegaAniso *= 2.0*gPi;

    /*** Setup CSA in PAS Frame ***/
    setupCSATensorInPas();
}

void CSATensor::setupCSATensorInPas()
{
  /*** Setup CSA tensor in PAS frame ***/
  //double aniso = mOmegaAniso*2.0*gPi;

  mInP->Element(-2) = -(1./sqrt(6.0))*mOmegaAniso*(mAsymmetryParameter);
  mInP->Element(-1) = 0.;
  mInP->Element(0)  = mOmegaAniso;
  mInP->Element(1)  = 0.;
  mInP->Element(2)  = -(1./sqrt(6.0))*mOmegaAniso*(mAsymmetryParameter);
}

//void CSATensor::rotate(const FRAMETRANSFORMATION& frameTransformation, const EulerAngleTriplet *angle)
//{
//  switch(frameTransformation)
//  {
//    case PASToCrystal:     mInC->setTensor(mInP->rotate(angle));    break;
//    case PASToRotor:       mInR->setTensor(mInP->rotate(angle));    break;
//    case PASToLab:         mInL->setTensor(mInP->rotate(angle));    break;
//    case CrystalToRotor:   mInR->setTensor(mInC->rotate(angle));    break;
//    case CrystalToLab:     mInL->setTensor(mInC->rotate(angle));    break;
//    case RotorToLab:       mInL->setTensor(mInR->rotate(angle));    break;
//    default:
//            throw("Frame transformation not defined!!..");
//    break;
//  }
//  mCSAAxes->RotateZYZ(angle);
//}
//
void CSATensor::rotate(const FRAMETRANSFORMATION& frameTransformation, const EulerAngleTriplet &angle)
{
  switch(frameTransformation)
  {
    case PASToCrystal:    mInC->setTensor(mInP->rotate(angle));    break;
    case PASToRotor:      mInR->setTensor(mInP->rotate(angle));    break;
    case PASToLab:        mInL->setTensor(mInP->rotate(angle));    break;
    case CrystalToRotor:  mInR->setTensor(mInC->rotate(angle));    break;
    case CrystalToLab:    mInL->setTensor(mInC->rotate(angle));    break;
    case RotorToLab:      mInL->setTensor(mInR->rotate(angle));    break;
    default:
      throw("Frame transformation not defined!!..");
    break;
  }
  mCSAAxes->rotateZYZ(angle);
}

ostream& operator<<(ostream &stream, const CSATensor *out)
{
  stream
//        <<"Use assy = "           <<out->GetUseAssy()<<"\n"
//        <<"mXX = "<<out->GetXX()<<"\n"
//        <<"mYY = "<<out->GetYY()<<"\n"
//        <<"mZZ = "<<out->GetZZ()<<"\n"
        <<"Asymmetry = "<<out->getAsymmetry()<<"\n"
        <<"Omega Iso = "<<out->getOmegaIso()<<"\n"
        <<"Omega Aniso = "<<out->getOmegaAniso()<<"\n"
        <<"PC = " <<out->getAnglesPToC().getAlfa()
        <<","     <<out->getAnglesPToC().getBeta()
        <<","     <<out->getAnglesPToC().getGamma()<<"\n";
  return stream;
}

bool CSATensor::read(const string& /*File*/, const string& label)
{
  string section = "Label = " + label;
  string Parameter;
/*    if(dslFileContainsSection(File, section)){
//      Parameter = "mXX =";
//      if(!GetParameterInFile(File,  section , Parameter ,        mXX))
//        return false;
//      Parameter = "mYY =";
//      if(!GetParameterInFile(File,  section , Parameter ,        mYY))
//         return false;
//      Parameter = "mZZ =";
//      if(!GetParameterInFile(File,  section , Parameter ,        mZZ))
//         return false;
      Parameter =  "Asymmetry =";
      if(!GetParameterInFile(File,  section , Parameter,   mAsymmetryParameter))
         return false;
      Parameter =  "Omega Iso =";
      if(!GetParameterInFile(File,  section , Parameter,   mOmegaIso))
         return false;
      Parameter =  "Omega Aniso =";
      if(!GetParameterInFile(File,  section , Parameter,   mOmegaAniso))
         return false;
      if(!GetParameterInFile(File,  section , "PC =", PToC))
       return false;
      return true;
    }
    else           */
      return false;
}



}
