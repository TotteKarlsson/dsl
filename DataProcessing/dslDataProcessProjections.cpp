
#pragma hdrstop

//#include "dslDataProcess.h"




//template <class T>
//void dslDataProcess<T>::GetProjections(){
//         GetRowProjection();
//         GetColProjection();
//};
//
//template <class T>
//void dslDataProcess<T>::GetRowProjection(){
//    //Sum up rows
//    /*** First create the vector to hold the projection ***/
//    int col, row;
//    if(Data->RowProjection == nullptr)
//        Data->RowProjection = new dslVector<T>(Data->GetRowDimSize());
//
//    Data->RowProjection->Zero();
//     for(row = 1; row < Data->GetRowDimSize() + 1; row++)
//        for(col = 1; col < Data->GetColDimSize() + 1; col++)
//         Data->RowProjection->SetElement(row) = Data->RowProjection->GetElement(row)+ Data->data(row,col);
//
//        Data->RowProjection->Normalize();
//};
//
//template <class T>
//void dslDataProcess<T>::GetRowProjection(int start, int end){
//    //Sum up rows
//    /*** First create the vector to hold the projection ***/
//    int col, row;
//    if(Data->RowProjection == nullptr)
//        Data->RowProjection = new dslVector<T>(Data->GetRowDimSize());
//
//    Data->RowProjection->Zero();
//     for(row = 1; row < Data->GetRowDimSize() + 1; row++)
//        for(col = start; col < end + 1; col++)
//         Data->RowProjection->SetElement(row) = Data->RowProjection->GetElement(row)+ Data->data(row,col);
//
//        Data->RowProjection->Normalize();
//};
//
//template <class T>
//void dslDataProcess<T>::GetColProjection(int start, int end){
//    //Sum up cols
//    /*** First create the vector to hold the projection ***/
//    int col, row;
//    if(Data->ColProjection == nullptr)
//        Data->ColProjection = new dslVector<T>(Data->GetColDimSize());
//
//    Data->ColProjection->Zero();
//     for(col = 1; col < Data->GetColDimSize() + 1; col++)
//        for(row = start; row < end + 1; row++)
//         Data->ColProjection->SetElement(col) = Data->ColProjection->GetElement(col) + Data->data(row,col);
//
//        Data->ColProjection->Normalize();
//};

//template <class T>
//void dslDataProcess<T>::GetColProjectionWithIncrement(int start, int Incr){
//    //Sum up cols
//    /*** First create the vector to hold the projection ***/
//    int col, row;
//    if(Data->ColProjection == nullptr)
//        Data->ColProjection = new dslVector<T>(Data->GetColDimSize());
//
//    Data->ColProjection->Zero();
//     for(col = 1; col < Data->GetColDimSize() + 1; col++)
//        for(row = start; row < Data->GetRowDimSize() + 1; row+=Incr)
//         Data->ColProjection->SetElement(col) = Data->ColProjection->GetElement(col) + Data->data(row,col);
//
//        Data->ColProjection->Normalize();
//};

//void dslDataProcess< complex<double> >::GetRowProjection(){
//  //Sum up rows
//  /*** First create the vector to hold the projection ***/
//  int col, row;
//  if(Data->RowProjection == nullptr)
//      Data->RowProjection = new dslVector<T>(Data->GetRowDimSize());
//  Data->RowProjection->Zero();
//
// for(row = 1; row < Data->GetRowDimSize() + 1; row++)
//  for(col = 1; col < Data->GetColDimSize() + 1; col++)
//       Data->RowProjection->SetElement(row) = Data->RowProjection->GetElement(row)+ Data->data(row,col);
//
//  Data->RowProjection->Normalize();
//}

//template <class T>
//void dslDataProcess<T>::GetRowProjection(int Offset, int Increment){
//   int col, row;
//  if(Data->RowProjection == nullptr)
//      Data->RowProjection = new dslVector<T>(Data->GetRowDimSize());
//   Data->RowProjection->Zero();
//
//   for(row = Offset; row < Data->GetRowDimSize() + 1; row+=Increment)
//      for(col = 1; col < Data->GetColDimSize() + 1; col++)
//       Data->RowProjection->SetElement(row) = Data->RowProjection->GetElement(row)+ Data->data(row,col);
//
//  Data->RowProjection->Normalize();
//}
//
//void dslDataProcess< complex<double> >::GetRowProjection(int Offset, int Increment){
//   int col, row;
//  if(Data->RowProjection == nullptr)
//      Data->RowProjection = new dslVector<T>(Data->GetRowDimSize());
//   Data->RowProjection->Zero();
//
//   for(row = Offset; row < Data->GetRowDimSize() + 1; row+=Increment)
//      for(col = 1; col < Data->GetColDimSize() + 1; col++)
//       Data->RowProjection->SetElement(row) = Data->RowProjection->GetElement(row)+ Data->data(row,col);
//
//  Data->RowProjection->Normalize();
//}

//template <class T>
//void dslDataProcess<T>::GetColProjection(){
//        //Sum up element along cols
//        /*** First create the vector to hold the projection ***/
//        int col, row;
//        if(Data->ColProjection == nullptr)
//                Data->ColProjection = new dslVector<T>(Data->GetColDimSize());
//
//        Data->ColProjection->Zero();
//    for(col = 1; col < Data->GetColDimSize() + 1; col++)
//        for(row = 1; row < Data->GetRowDimSize() + 1; row++)
//                 Data->ColProjection->SetElement(col) = Data->ColProjection->GetElement(col)+ Data->data(row,col);
//
//                Data->ColProjection->Normalize();
//};
//

// void dslDataProcess< complex<double> >::GetColProjection(){
//  //Sum up element along cols
//  /*** First create the vector to hold the projection ***
//  int col, row;
//  if(Data->ColProjection == nullptr)
//      Data->ColProjection = new dslVector<T>(Data->GetColDimSize());
//
//  Data->ColProjection->Zero();
//  for(col = 1; col < Data->GetColDimSize() + 1; col++)
//      for(row = 1; row < Data->GetRowDimSize() + 1; row++)
//           Data->ColProjection->SetElement(col) = Data->ColProjection->GetElement(col)+ Data->data(row,col);
//
//      Data->ColProjection->Normalize();
// }


//template <class T>
//void dslDataProcess<T>::GetColProjection(int Offset, int Increment){
//   int col, row;
//
//  if(Data->ColProjection == nullptr)
//      Data->ColProjection = new dslVector<T>(Data->GetColDimSize());
//   Data->ColProjection->Zero();
//
//   for(col = 1; col < Data->GetColDimSize() + 1; col++)
//     for(row = Offset; row < Data->GetRowDimSize() + 1; row+=Increment)
//       Data->ColProjection->SetElement(col) = Data->ColProjection->GetElement(col)+ Data->data(row,col);
//
//  Data->ColProjection->Normalize();
//}
//
//void dslDataProcess< complex<double> >::GetColProjection(int Offset, int Increment){
//   int col, row;
//  if(Data->ColProjection == nullptr)
//      Data->ColProjection = new dslVector<T>(Data->GetColDimSize());
//   Data->ColProjection->Zero();
//
//   for(col = 1; col < Data->GetColDimSize() + 1; col++)
//     for(row = Offset; row < Data->GetRowDimSize() + 1; row+=Increment)
//       Data->ColProjection->SetElement(col) = Data->ColProjection->GetElement(col)+ Data->data(row,col);
//
////    Data->ColProjection->Normalize();
//}
//

