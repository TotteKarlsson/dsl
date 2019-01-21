
#pragma hdrstop

//#include <cmath>
//#include <ostream>
//#include "dslUtils.h"
//#include "dslMatrix.h"
//
//using namespace std;
//
//
////template<>
////const dslMatrix< double > dslMatrix< double >::GetAdjoint() const {
////  dslMatrix< double > TempMat;
////  TempMat = GetTranspose();
////  for(int Rows = 1 ; Rows < mRowSize + 1; Rows++)
////    for(int Cols = 1; Cols < mColSize + 1; Cols++)
////      ;//TempMat(Rows,Cols) = conj(TempMat(Rows,Cols));
////  return TempMat;
////}
//
//
//////////////////// double scalar, double matrix /////////////////////////////
//const dslMatrix<double> operator*(double scalar, const dslMatrix<double>& Rmat)
//{
//
//  dslMatrix<double> temp(Rmat.mRowSize, Rmat.mColSize);
//  for(int row = 1; row < Rmat.mRowSize + 1; row++)
//    for(int col = 1; col < Rmat.mColSize + 1; col++)
//      temp.mMatrix[row][col] = scalar*Rmat.mMatrix[row][col];
//
//  return temp;
//}
//
//const dslMatrix<double> operator*(const dslMatrix<double>& Rmat, double scalar)
//{
//  dslMatrix<double> temp(Rmat.mRowSize,Rmat.mColSize);
//  for(int row = 1; row < Rmat.mRowSize + 1; row++)
//    for(int col = 1; col < Rmat.mColSize + 1; col++)
//      temp.mMatrix[row][col] = Rmat.mMatrix[row][col]*scalar;
//
//  return temp;
//}
//
//////////////////// complex scalar, complex matrix /////////////////////////////
////template< std::complex<double> >
//const dslMatrix< std::complex<double> > operator*(const complex<double>& scalar, const dslMatrix< complex<double> >& Rmat)
//{
//  dslMatrix< complex<double> > temp(Rmat.mRowSize,Rmat.mColSize);
//  for(int row = 1; row < Rmat.mRowSize + 1; row++)
//    for(int col = 1; col <Rmat.mColSize + 1; col++)
//      temp.mMatrix[row][col] = Rmat.mMatrix[row][col]*scalar;
//
//  return temp;
//}
//
//const dslMatrix< complex<double> > operator*(const dslMatrix< complex<double> >& Rmat, const complex<double>& scalar)
//{
//  dslMatrix< complex<double> > temp(Rmat.mRowSize,Rmat.mColSize);
//  for(int row = 1; row < Rmat.mRowSize + 1; row++)
//    for(int col = 1; col < Rmat.mColSize + 1; col++)
//      temp.mMatrix[row][col] = Rmat.mMatrix[row][col]*scalar;
//
//  return temp;
//}
//
///////////////////// double scalar,complex matrix ///////////////////////////////
//const dslMatrix< complex<double> > operator*(double scalar, const dslMatrix< complex<double> >& Rmat)
//{
//  dslMatrix< complex<double> > temp(Rmat.GetRowSize(), Rmat.GetColSize());
//  for(int row = 1; row < Rmat.GetRowSize() + 1; row++)
//    for(int col = 1; col < Rmat.GetColSize() + 1; col++)
//      temp(row,col) = Rmat(row,col)*scalar;
//
//  return temp;
//}
//
//const dslMatrix< complex<double> > operator*(const dslMatrix< complex<double> >& Rmat, double scalar)
//{
//  dslMatrix< complex<double> > temp(Rmat.GetRowSize(), Rmat.GetColSize());
//  for(int row = 1; row < Rmat.GetRowSize() + 1; row++)
//    for(int col = 1; col < Rmat.GetColSize() + 1; col++)
//      temp(row,col) = Rmat(row,col)*scalar;
//
//  return temp;
//}
//
//dslVector<double> operator*(const dslMatrix<double> &Mat, const dslVector<double> &rightVec)
//{
//  dslVector<double> temp(rightVec.Start(), rightVec.End());
//  temp.Zero();
//  /*** Check dimensions ...***/
//  for(int row = 1; row < Mat.GetRowSize() + 1; row++)
//    for(int col = 1; col < Mat.GetColSize() + 1; col++)
//      temp[row] = Mat[row][col]*rightVec.Element(col) + temp[row];
//
// return temp;
//}
//
//dslVector< complex<double> > operator*(const dslMatrix<complex<double> > &Mat, const dslVector<complex<double> > &rightVec){
//
//  dslVector<complex<double> > temp(rightVec.Start(), rightVec.End());
//  temp.Zero();
//  for(int row = 1; row < Mat.GetRowSize() + 1; row++)
//   for(int col = 1; col < Mat.GetColSize() + 1; col++)
//     temp[row] = Mat[row][col]*rightVec.Element(col) + temp[row];
//
//  return temp;
//}
//
//
//// template<>
//// const dslMatrix< complex<double> > dslMatrix< complex<double> >::DP(const dslMatrix< complex<double> > &B){
////
////  dslMatrix<  complex<double>  > C(mRowSize*B.mRowSize,mColSize*B.mColSize);
////      for(int pos1 = 0, row = 1;  row < mRowSize + 1; row++, pos1 += B.mRowSize)
////          for(int pos2 = 0, col = 1; col < mColSize + 1; col++, pos2 += B.mColSize)
////              for(int rowB = 1;  rowB < B.mRowSize + 1; rowB++)
////                  for(int colB = 1; colB < B.mColSize + 1; colB++)
////                          C(pos1 + rowB,pos2 + colB) = mat[row][col]*B(rowB,colB);
////      return C;
//// }
////
////
//
//
/////////////////////////////// ostreams ////////////////////////////////////////////////////////
//ostream &operator<<(ostream &stream, const dslMatrix< double > &out)
//{
//    stream<<"\nMatrix :"<<out.GetRowSize()<<" x "<<out.GetColSize()<<"\n";
//    for(int row = 1; row < out.GetRowSize() + 1; row++)
//    {
//        for(int col = 1; col < out.GetColSize() + 1; col++)
//        {
//            stream<<out(row,col)<<"\t";
//        }
//        stream<<"\n";
//    }
//    return stream;
//}
//
//ostream &operator<<(ostream &stream, const dslMatrix< complex<double> > &out)
//{
//    stream<<"Matrix :"<<out.GetRowSize()<<" x "<<out.GetColSize()<<"\n";
//    for(int row = 1; row < out.GetRowSize() + 1; row++)
//    {
//        for(int col = 1; col < out.GetColSize() + 1; col++)
//        {
//          stream<<out(row,col)<<"\t";
//        }
//        stream<<"\n";
//    }
//    return stream;
//}
//
////CB6
////extern "C" {
////#include ".\..\dslCSource\Meschach\matrix2.h"
////#include ".\..\dslCSource\Meschach\zmatrix2.h" //This is Meschach complex matrix functions
//
////};
////
////void                                  dslMatrixToMesch(MAT *MCopy);
////void                                  dslMatrixToMesch(ZMAT *MCopy);
////
////template <class T>
////void dslExport DblMeschTodslMatrix(MAT *meschIn, dslMatrix<T>& dslOut);
////
////template <class T>
////void dslExport CpxMeschTodslMatrix(ZMAT *meschIn, dslMatrix<T>& dslOut);
////
//
///****************** EigenSystem Functions for dslMatrix<double> ******************************/
////#define SIGN(a,b) ((b) >= 0.0 ? fabs(a) : -fabs(a))
////template<>
////void dslMatrix<double>::GetEigenSystem(dslMatrix< complex<double> > &DiagonalMat, dslMatrix< complex<double> > &Eigenvectors){
/////*
////A function that takes the input Matrix, and
////returns one matrix (complex) containing eigenvectors (in columns)
////and one complex matrix with the eigenvalues on the diagonal
////*/
////
////  complex<double>  I(0,1);
////  MAT *inMATRIX, *T, *X_re, *X_im;
////  VEC *evals_re,*evals_im;
////
////  inMATRIX = m_get(rSize,cSize);// Allocate a Mesch matrix
////
////  /*** Copy "class" double matrix to the Mesch (double) matrix ***/
////  dslMatrixToMesch(inMATRIX);
////
////  /* Here starts the diagonalizing function  */
////  T = m_copy(inMATRIX,MDSL_NULL);
////
////  evals_re = v_get(inMATRIX->m);//Vectors with same dimension as the
////  evals_im = v_get(inMATRIX->m);//Input matrix
////
////  X_re = m_get(inMATRIX->m,inMATRIX->n);
////  X_im = m_get(inMATRIX->m,inMATRIX->n);
////
////  /* Compute Shur form: A=Q.T.Q^T */
////  schur(T,inMATRIX);
////
////  /* Now we can extract eigenvalues fom the schur form */
////  schur_evals(T,evals_re,evals_im);
////
////  /* and eigenvectors */
////  schur_vecs(T,inMATRIX,X_re,X_im);
////
////  /* Put the re and Im parts together in a complex matrices */
////
////  for(int i = 0; i < rSize; i++)
////    DiagonalMat(i+1,i+1)= evals_re->ve[i]+ I*evals_im->ve[i];
////
////  // Then the eigenvector matrix
////  for(int col = 0; col < cSize; col++)
////    for(int row = 0; row < rSize; row++)
////      Eigenvectors(col+1,row+1)= X_re->me[col][row] + I*X_im->me[col][row];
////
////  /* Free space */
////  M_FREE(inMATRIX);
////  M_FREE(T);
////  M_FREE(X_re);
////  M_FREE(X_im);
////  V_FREE(evals_re);
////  V_FREE(evals_im);
////}
////
////template<>
////void dslMatrix<double>::GetInverse(dslMatrix<double> &InvMat){
////    /* The "Class" matrix that are going to be inverted is not affected by
////        this routine. Instead the inverted matrix is put into InvMat */
////
////  MAT *in, *out;
////  // Set up in and out
////  in = m_get(rSize,cSize);// Allocate a Mesch matrix
////  out = m_get(rSize,cSize);// Allocate a Mesch matrix
////
////  // Copy our matrix to Mesch matrix in
////  dslMatrixToMesch(in);
////
////  //Take Inverse of Mesch matrix
////  out = m_inverse(in,out);
////
////  //Copy the inverted matrix (out) matrix to InvMat
////  DblMeschTodslMatrix(out,InvMat);
////
////  /* Free space */
////  M_FREE(in);
////  M_FREE(out);
////}
////
////template<>
////dslMatrix<double> dslMatrix<double>::GetInverse(){
////    /* The "Class" matrix that are going to be inverted is not affected by
////        this routine. Instead the inverted matrix is put into InvMat */
////  dslMatrix<double> temp(rSize,cSize);
////  MAT *in, *out;
////  // Set up in and out
////  in = m_get(rSize,cSize);// Allocate a Mesch matrix
////  out = m_get(rSize,cSize);// Allocate a Mesch matrix
////
////  // Copy our matrix to Mesch matrix in
////  dslMatrixToMesch(in);
////
////  //Take Inverse of Mesch matrix
////  out = m_inverse(in,out);
////
////  //Copy the inverted matrix (out) matrix to InvMat
////  DblMeschTodslMatrix(out,temp);
////
////  /* Free space */
////  M_FREE(in);
////  M_FREE(out);
////  return temp;
////}
////
////#ifndef BCB6
////template<>
////#endif
////void dslMatrix<double>::GetEigenValues(dslVector<double> &Evec){
////  /*** This function works only on a real symmetric matrix.
////      It returns the eigenvalues in the vector Evec.
////      Uses Numerical Recipies eigensystem functions described at
////      page 474 and 480, where those routines have been optimized for
////      returning only eigenvalues..
////  ***/
////
////  dslVector<double> temp(1,Evec.Size()); // this is the "e"-vector used
////                                      //in the following functions
////
////  if(rSize != cSize)
////    LogMessage("Matrix is not a square marix in dslMatrix<double>::GetEigenValues...", dslLogger::Error);
////  if(Evec.Size() != cSize)
////    Evec.Resize(cSize);
////
////  eigval_tred2(mMatrix,Size(),Evec(),temp());
////  eigval_tqli(Evec(), temp(), Size());
////}
////
/////************ EigenSystem Utility Functions for dslMatrix<double> ******************************/
////#ifndef BCB6
////template<>
////#endif
////void dslMatrix<double>::eigval_tred2(double **a, int n, double d[], double e[]){
////  /*** House holder reduction of a real, symmetric matrix a[1..n][1..n].
////    Adapted from NR page 474. Changed to double version and changed to
////    find only the eigenvalues of the matrix a. Works togheter with
////    eigval_tqli.
////
////    INPUT: a is the matrix supposed to be reduced to tridiagonal form.
////              d is a double vector n long.
////              e is a double vector n long.
////
////    OUTPUT: a doesn't contain any useful information since this is
////               the modified version of tred2 which purpose is to find only
////               the eigenvalues of a.
////               d[1..n] returns the diagonal elements of the tridiagonal matrix.
////               e[1..n] the off diagonal elements, with e[1] =0.
////  ***/
////
////  int l,k,j,i;
////  double scale,hh,h,g,f;
////
////  for (i=n;i>=2;i--) {
////    l=i-1;
////    h=scale=0.0;
////    if (l > 1) {
////      for (k=1;k<=l;k++)
////        scale += fabs(a[i][k]);
////      if (scale == 0.0)
////        e[i]=a[i][l];
////      else{
////        for (k=1;k<=l;k++) {
////          a[i][k] /= scale;
////          h += a[i][k]*a[i][k];
////        }
////        f=a[i][l];
////        g=(f >= 0.0 ? -sqrt(h) : sqrt(h));
////        e[i]=scale*g;
////        h -= f*g;
////        a[i][l]=f-g;
////        f=0.0;
////        for (j=1;j<=l;j++) {
////          a[j][i]=a[i][j]/h;
////          g=0.0;
////          for (k=1;k<=j;k++)
////            g += a[j][k]*a[i][k];
////          for (k=j+1;k<=l;k++)
////            g += a[k][j]*a[i][k];
////          e[j]=g/h;
////          f += e[j]*a[i][j];
////        }
////        hh=f/(h+h);
////        for (j=1;j<=l;j++) {
////          f=a[i][j];
////          e[j]=g=e[j]-hh*f;
////          for (k=1;k<=j;k++)
////            a[j][k] -= (f*e[k]+g*a[i][k]);
////        }
////      }
////    }else
////      e[i]=a[i][l];
////    d[i]=h;
////  }
////  /* Contents of this loop can be omitted (has been done!!) if eigenvectors not
////          wanted (i.e only eigenvalues) except for statement d[i]=a[i][i]; */
////  for (i = 1; i <= n; i++){
////    d[i]=a[i][i];
////  }
////}
///*** ==================== ***/
//
////#ifndef BCB6
////template<>
////#endif
////void dslMatrix<double>::eigval_tqli(double d[], double e[], int n){
///*** QL algorithm with implicit shifts. to determine the eigenvalues (and eigenvectors) of a real,
//      symmetric, tridiagonal matrix, or of a real, symmetric matrix previsosly reduced by tred2.
//
//  INPUTS:   d[1..n] is the vector that contains the diagonal elements of the tridiagonal matrix.
//                e[1..n] inputs the subdiagonal elements of the tridiagonal matrix, with e[1] arbitrary.
//
//  OUTPUT:   e is destroyed
//                d[1..n] contains the eigenvalues.
//
//    This routine here is the modified version of the tqli function in NR page 480.
//    It's modified to only return the eigenvalues (no eigen vectors) and are supposed to work
//    togheter with eigval_tred2, i.e the d and e vector are output from eigval_tred2.
//    Therefore the matrix z is not needed.
//
//***/
////  int m,l,iter,i;
////  double s,r,p,g,f,dd,c,b;
////
////  for (i=2;i<=n;i++) e[i-1]=e[i];
////  e[n]=0.0;
////  for (l = 1;l <=n;l++) {
////      iter=0;
////      do {
////          for (m=l;m<=n-1;m++) {
////              dd=fabs(d[m])+fabs(d[m+1]);
////              if ((float)(fabs(e[m])+dd) == dd) break;
////          }
////          if (m != l) {
////              if (iter++ == 30)
////                  LogMessage("Too many iterations in tqli", dslLogger::Error);
////              g=(d[l+1]-d[l])/(2.0*e[l]);
////              r=dpythag(g,1.0);
////              g=d[m]-d[l]+e[l]/(g+SIGN(r,g));
////              s=c=1.0;
////              p=0.0;
////              for (i=m-1;i>=l;i--) {
////                  f=s*e[i];
////                  b=c*e[i];
////                  e[i+1]=(r=dpythag(f,g));
////                  if (r == 0.0) {
////                      d[i+1] -= p;
////                      e[m]=0.0;
////                      break;
////                  }
////                  s=f/r;
////                  c=g/r;
////                  g=d[i+1]-p;
////                  r=(d[i]-g)*s+2.0*c*b;
////                  d[i+1]=g+(p=s*r);
////                  g=c*r-b;
////              }
////              if (r == 0.0 && i >= l) continue;
////              d[l] -= p;
////              e[l]=g;
////              e[m]=0.0;
////          }
////      } while (m != l);
////  }
////}
//
//
///****************** EigenSystem Functions for dslMatrix< complex<double> > ******************************/
////template<>
////void dslMatrix< complex<double> >::GetEigenSystem(dslMatrix< complex<double> > &DiagonalMat, dslMatrix< complex<double> > &Eigenvectors){
/////***
////Here we have to compute the  complex<double>  shur factorisation
////A function that takes the input Matrix, and
////returns one matrix ( complex<double> ) containing eigenvectors (in columns)
////and one complex<double>  matrix with the eigenvalues on the diagonal
////Does only work for a  complex<double>  matrix where the imaginary part is zero !!!
////For a  complex<double>  one we have to use the  complex<double>  shur-Form
////***/
////  complex<double>  I(0,1);
////
////
/////***
////Allocate memory for temporary matrices. If one is going to
////diagonalize the matrix heavily (many times) the function DiagonalizeHeavily
////should be executed. That one allocates (deallocates) the temporary matrices just once..
////***/
////  MAT *inMATRIX;
////  MAT *T, *X_re, *X_im;
////  VEC *evals_re,*evals_im;
////  inMATRIX = m_get(rSize,cSize);// Allocate a Mesch matrix
////
////  /*** Copy "class"  complex<double>  matrix to the Mesch (double) matrix ***/
////  dslMatrixToMesch(inMATRIX);
////
////  /* Here starts the diagonalizing function  */
////  T = m_copy(inMATRIX,MDSL_NULL);
////
////  evals_re = v_get(inMATRIX->m);//Vectors with same dimension as the
////  evals_im = v_get(inMATRIX->m);//Input matrix
////
////  X_re = m_get(inMATRIX->m,inMATRIX->n);
////  X_im = m_get(inMATRIX->m,inMATRIX->n);
////
////  /* Compute Shur form: A=Q.T.Q^T */
////  schur(T,inMATRIX);
////
////  /* Now we can extract eigenvalues fom the schur form */
////  schur_evals(T,evals_re,evals_im);
////
////  /* and eigenvectors */
////  schur_vecs(T,inMATRIX,X_re,X_im);
////
////  /* Put the re and Im parts together in a  complex<double>  matrices */
////
////  // First the eigenvalue vector, put them on the diagonal on "DiagonalMat"
////  // Check size on matrices
////  if(DiagonalMat.GetRowSize() != rSize)
////    DiagonalMat.ReSize(rSize, cSize);
////  else if(DiagonalMat.GetColSize() != cSize)
////    DiagonalMat.ReSize(rSize, cSize);
////
////  if(Eigenvectors.GetRowSize() != rSize)
////    Eigenvectors.ReSize(rSize, cSize);
////  else if(Eigenvectors.GetColSize() != cSize)
////    Eigenvectors.ReSize(rSize, cSize);
////
////
////  for(int i=0;i<rSize;i++)
////    DiagonalMat(i+1,i+1)= evals_re->ve[i]+ I*evals_im->ve[i];
////
////
////  // Then the eigenvector matrix
////  for(int col=0; col <cSize; col++)
////    for(int row=0; row<rSize; row++)
////      Eigenvectors(col+1,row+1)= X_re->me[col][row]+I*X_im->me[col][row];
////
////  /* Free allocated space */
////  M_FREE(inMATRIX);
////  M_FREE(T);
////  M_FREE(X_re);
////  M_FREE(X_im);
////  V_FREE(evals_re);
////  V_FREE(evals_im);
////}
////
////template<>
////void dslMatrix< complex<double> >::GetInverse(dslMatrix< complex<double> > &InvMat){
/////*
////The "Class" matrix that are going to be inverted is not affected by
////this routine. Instead the inverted matrix is put into InvMat
////*/
////
////  ZMAT *in, *out;
////  // Set up in and out
////  in = zm_get(rSize,cSize);// Allocate a Mesch matrix
////  out = zm_get(rSize,cSize);// Allocate a Mesch matrix
////
////  // Copy our matrix to Mesch matrix in
////  dslMatrixToMesch(in);
////
////  //Take Inverse of Mesch matrix
////  out = zm_inverse(in,out);
////
////  //Copy the inverted matrix (out) matrix to InvMat
////  CpxMeschTodslMatrix(out,InvMat);
////
////  /* Free space */
////  ZM_FREE(in);
////  ZM_FREE(out);
////}
////
////template<>
////dslMatrix< complex<double> > dslMatrix< complex<double> >::GetInverse(){
/////*
////The "Class" matrix that are going to be inverted is not affected by
////this routine. Instead the inverted matrix is put into InvMat
////*/
////  dslMatrix< complex<double> > temp(rSize,cSize);
////  ZMAT *in, *out;
////  // Set up in and out
////  in = zm_get(rSize,cSize);// Allocate a Mesch matrix
////  out = zm_get(rSize,cSize);// Allocate a Mesch matrix
////
////  // Copy our matrix to Mesch matrix in
////  dslMatrixToMesch(in);
////
////  //Take Inverse of Mesch matrix
////  out = zm_inverse(in,out);
////
////  //Copy the inverted matrix (out) matrix to InvMat
////  CpxMeschTodslMatrix(out,temp);
////
////  /* Free space */
////  ZM_FREE(in);
////  ZM_FREE(out);
////  return temp;
////}
////
///****************** End of EigenSystem Functions  ******************************/
//
///************** Utility Functions ****************************/
////CB6
////template<>
////void dslMatrix<double>::dslMatrixToMesch(MAT *MCopy){
////  for(int row = 1; row < rSize + 1; row++)
////    for(int col = 1; col < cSize + 1; col++)
////      MCopy->me[row-1][col-1] = mat[row][col];//Mesch uses 0,0 as first element
////}
////
////template<>
////void dslMatrix< complex<double> >::dslMatrixToMesch(MAT *MCopy){
////  int row, col;
////  for(row = 1; row < rSize + 1; row++)
////    for(col = 1; col < cSize + 1; col++)
////      MCopy->me[row-1][col-1] = real(mat[row][col]);
////}
////
////template<>
////void dslMatrix< complex<double> >::dslMatrixToMesch(ZMAT *ZMCopy){
////  int row, col;
////  for(row = 1; row < rSize + 1; row++)
////    for(col = 1; col < cSize + 1; col++){
////      ZMCopy->me[row-1][col-1].re = real(mat[row][col]);
////      ZMCopy->me[row-1][col-1].im = imag(mat[row][col]);
////    }
////}
////
/////************** External Utility Functions ****************************/
////template<>
////void DblMeschTodslMatrix(MAT *M, dslMatrix<double> &TCopy){
////  for(int row = 1; row < TCopy.GetRowSize() + 1; row++)
////    for(int col = 1; col < TCopy.GetColSize() + 1; col++)
////      TCopy[row][col] = M->me[row-1][col-1];
////}
////
////template<>
////void CpxMeschTodslMatrix(ZMAT *M, dslMatrix< complex<double> > &TCopy){
////  complex<double>  I(0,1);
////  for(int row = 1; row < TCopy.GetRowSize() + 1; row++)
////    for(int col = 1; col < TCopy.GetColSize() + 1; col++)
////      TCopy[row][col] = M->me[row-1][col-1].re + I*M->me[row-1][col-1].im ;
////}
//
//
