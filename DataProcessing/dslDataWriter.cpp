
#pragma hdrstop
#include <fstream>
#include <complex>
#include "dslDataWriter.h"

namespace dsl
{


using std::complex;
//---------------------------------------------------------------------------

template class dslDataWriter<double>;
template class dslDataWriter< complex<double> >;


using std::fstream;

//template class dslDataWriter< double >;
//template class dslDataWriter< complex<double> >;


//template <>
//bool MTK_DATA dslDataWriter<double>::dslDouble(const string& fileName, const FILE_FORMAT& type)
//{
//     return false;
//}


//template <class T>
//bool dslDataWriter< T >::dslImaginaryDataSection(fstream& fileS, const FILE_FORMAT& type)
//{
////    if(fileS)
////    {
////        double nr, val;
////        switch(type)
////        {
////              case ffASCII:
////                for(int col = 1; col < mData->CSize() + 1; col++)
////                {
////                      fileS<<"\n"<<mData->GetColAxis()->Element(col);
////                      for(int row = 1; row < mData->RSize() + 1; row++)
////                    {
////                        fileS<<"\t"<< imag(mData->Element(row,col));
////                    }
////                }
////              return true;
////
////              case ffBINARY:
////                for(int col = 1; col < mData->CSize() + 1; col++)
////                {
////                      val = mData->GetColAxis()->Element(col);
////                      fileS.write((char *) &val, sizeof(val));
////                      for(int row = 1; row < mData->RSize() + 1; row++)
////                    {
////                        nr = imag(mData->Element(row,col));
////                        fileS.write((char *) &nr, sizeof(nr));
////                      }
////                }
////            return true;
////        }
////      }
////    return false;
//}

//template <>
//bool dslDataWriter< complex<double> >::dslDataSection(fstream& fileS, const FILE_FORMAT& type)
//{return false;}
//
//template <>
//bool dslDataWriter< double >::dslDataSection(fstream& fileS, const FILE_FORMAT& type)
//{return false;}
//
//template <class T>
//void dslDataWriter< T >::ImagRowsToFile(const string& fileName)
//{
////      fstream outStream;
////      outStream.open(fileName.c_str(),ios::out);
////
////    for(int col=1;col<mData->CSize()+1;col++)
////    {
////        outStream<<mData->GetColAxis()->Element(col)<<"\t";
////         for(int row=1;row<mData->RSize()+1;row++)
////        {
////             outStream<<imag(mData->Element(row,col));
////              if(row<mData->RSize()+1)/*** Don't put a tab after the last element ***/
////            {
////                 outStream<<"\t";
////            }
////          }
////          outStream<<"\n";
////       }
////      outStream.close();
//}
//
//////// OLD     ////////////////////////////////////////////////////////////////////////
//    void VTKAsciiData(int firstRow, const int &lastRow, const char *fileName);
//    void VTKAscii2DData(const char *fileName);
//    void VTKAscii2DDataRow(int Row, const char *fileName);
//    void VTKAscii3DData(const char* fileName);
//    void VTKAscii3DDataBlock(int Block, const char* fileName);
//    void SimpleFormat(int startCol, int EndCol, const char* FileName);
//    void SimpleFormat(const char* FileName);

//template <class T>
//void dslDataWriter<T>::VTKAsciiData(int firstRow, int lastRow, const char* fileName){
//    fstream out;
//    out.open(fileName,ios::out);
//    /*** First the header ***/
//    out<<"# vtk DataFile Version 1.0\n"
//        <<"My data\n"
//        <<"ASCII\n"
//        <<"DATASET POLYDATA\n";
//    /*** Then the points... ***/
//    out<<"POINTS "<<Data->CSize()<<" float\n";
//    for(int col=1;col<Data->CSize()+1;col++){
//        for(int row=firstRow;row<lastRow+1;row+=1){
//            out<<Data->data(row,col)<<" ";
//        }
//        out<<"\n";
//     }
//    /*** Then the connectivity.. max 10 points per poly-line ***/
//
//    out<<"LINES "<<1<<" "<< (Data->CSize()+1)<<" "<<(Data->CSize())<<"\n";
//    int i = 0;
//    do{
//        out<<i<<"\n";
//        i++;
//    }while(i != Data->CSize());
//
//    out.close();
//}
//
//template <class T>
//void dslDataWriter< T >::VTKAscii2DData(const char* fileName){
//    //2d data x = t2Axis and y values in row 1 and z = 0
//
//    //Normalize the axis and the dataset..x axis 0->1 and maxpoint(y) = 1
//    Data->Process->NormalizeData();
//
//    fstream out;
//    out.open(fileName,ios::out);
//    /*** First the header ***/
//    out<<"# vtk DataFile Version 1.0\n"
//        <<"My data\n"
//        <<"ASCII\n"
//        <<"DATASET POLYDATA\n";
//    /*** Then the points... ***/
//    out<<"POINTS "<<Data->CSize()<<" float\n";
//    for(int col=1;col<Data->CSize()+1;col++)
//        out<<double(col)/double(Data->CSize())<<" "<<Data->data(1,col)<<" "<<"0"<<"\n";
//
//    out<<"\n";
//
//    /*** Then the connectivity.. max 10 points per poly-line ***/
//    out<<"LINES "<<1<<" "<< (Data->CSize()+1) <<" "<< (Data->CSize())<<"\n";
//    int i = 0;
//    do{
//        out<<i<<"\n";
//        i++;
//    }while(i != Data->CSize());
//    out.close();
//}
//
//template <class T>
//void dslDataWriter< T >::VTKAscii3DData(const char* fileName){
//  //3d data x,y and z values are used..
//  //Normalize data...max point are 1.
//  Data->Process->NormalizeData();
//  fstream out;
//  out.open(fileName,ios::out);
//  /*** First the header ***/
//  out<<"# vtk DataFile Version 1.0\n"
//      <<"My data\n"
//      <<"ASCII\n"
//      <<"DATASET POLYDATA\n";
//  /*** Then the points... ***/
//  out<<"POINTS "<<Data->CSize()<<" float\n";
//    for(int col=1;col<Data->CSize()+1;col++)
//      out<<Data->data(2,col)<<" "<<Data->data(1,col)<<" "<<Data->data(3,col)<<"\n";
//
//  out<<"\n";
//
//      /*** Then the connectivity.. construct one single poly-line ***/
//      out<<"LINES "<<1<<" "<< (Data->CSize()+1)<<" "<< (Data->CSize())<<"\n";
//      int i = 0;
//    do{
//        out<<i<<"\n";
//        i++;
//      }while(i != Data->CSize());
//
//  out.close();
//}
//
//template <class T>
//void dslDataWriter< T >::VTKAscii3DDataBlock(int BlockNumber, const char* fileName){
//  //3d data x,y and z values are used..
//  //Normalize data...max point are 1.
//  Data->Process->NormalizeData();
//  fstream out;
//  out.open(fileName,ios::out);
//  int FirstRow = (Data->GetRowBlockSize()*(BlockNumber-1)+1);
//  int LastRow = FirstRow+Data->GetRowBlockSize()-1;
//
//  /*** First the header ***/
//  out<<"# vtk DataFile Version 1.0\n"
//      <<"My data\n"
//      <<"ASCII\n"
//      <<"DATASET POLYDATA\n";
//  /*** Then the points... ***/
//  out<<"POINTS "<<Data->CSize()<<" float\n";
//  for(int col=1;col<Data->CSize()+1;col++)
//    out<<Data->data(FirstRow+1,col)<<" "<<Data->data(FirstRow,col)<<" "<<Data->data(FirstRow+2,col)<<"\n";
//  out<<"\n";
//
//  /*** Then the connectivity.. cinstruct one single poly-line ***/
//  out<<"LINES "<<1<<" "<< (Data->CSize()+1)<<" "<< (Data->CSize())<<"\n";
//  int i = 0;
//  do{
//    out<<i<<"\n";
//    i++;
//  }while(i != Data->CSize());
//
//  out.close();
//}

//template<>
//void dslDataWriter<double>::SimpleFormat(const char* FileName)
//{
//    fstream outStream;
//    outStream.open(FileName,ios::out);
//
//    for(int col=1; col<Data->CSize()+1; col++)
//    {
//        for(int row=1;row <Data->RSize()+1;row++)
//        {
//              outStream<<real(Data->data(row,col));
//              outStream<<"\t";
//        }
//        outStream<<"\n";
//    }
//    outStream.close();
//}
//
//template<>
//void dslDataWriter<cpx>::SimpleFormat(const char* FileName)
//{
//    fstream outStream;
//    outStream.open(FileName,ios::out);
//
//    for(int col=1; col<Data->CSize()+1; col++)
//    {
//        for(int row=1;row <Data->RSize()+1;row++)
//        {
//              outStream<<real(Data->data(row,col));
//              outStream<<"\t";
//        }
//        outStream<<"\n";
//    }
//    outStream.close();
//}
//
//template<>
//void dslDataWriter<cpx>::SimpleFormat(int startCol, int EndCol, const char* FileName)
//{
//    fstream outStream;
//    outStream.open(FileName,ios::out);
//
//    for(int col=startCol; col < EndCol + 1; col++)
//    {
//        for(int row=1;row <Data->RSize()+1;row++)
//        {
//              outStream<<real(Data->data(row,col));
//              outStream<<"\t";
//        }
//        outStream<<"\n";
//    }
//    outStream.close();
//}

}
