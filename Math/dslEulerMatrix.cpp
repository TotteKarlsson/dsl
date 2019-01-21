#pragma hdrstop
#include <cmath>
#include "dslMatrix.h"
#include "dslEulerMatrix.h"

using namespace std;

namespace dsl
{

EulerMatrix::EulerMatrix()
{
    TMatrix.Create(3,3);
    INVTMatrix.Create(3,3);
}

EulerMatrix::~EulerMatrix()
{}

void EulerMatrix::SetMatrices(double fi, double theta)
{
    double sfi = sin(fi);
    double steta = sin(theta);
    double cfi  = cos(fi);
    double cteta  = cos(theta);

    TMatrix(1,1) = cfi;           TMatrix(1,2) = sfi;           TMatrix(1,3) = 0;
    TMatrix(2,1) = -cteta*sfi;    TMatrix(2,2) = cteta*cfi;     TMatrix(2,3) = steta;
    TMatrix(3,1) = steta*sfi;     TMatrix(3,2) = -steta*cfi;    TMatrix(3,3) = cteta;

    INVTMatrix(1,1) = cfi;        INVTMatrix(1,2) = -cteta*sfi; INVTMatrix(1,3) = steta*sfi;
    INVTMatrix(2,1) = sfi;        INVTMatrix(2,2) = cteta*cfi;  INVTMatrix(2,3) = -steta*cfi;
    INVTMatrix(3,1) = 0;          INVTMatrix(3,2) = steta;      INVTMatrix(3,3) = cteta;
}

dslMatrix<double>& EulerMatrix::GetTMatrix()
{
    return TMatrix;
}

dslMatrix<double>& EulerMatrix::GetINVTMatrix()
{
    return INVTMatrix;
}

}
