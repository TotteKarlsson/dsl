#pragma hdrstop
#include <complex>
#include <iostream>
//#include "dslLogger.h"
#include "dslMatrix.h"
#include "dslStringUtils.h"
#include "dslUtils.h"
#include "dslVector.h"

namespace dsl
{

//////////////////// ostreams //////////////////////////////////////////////////
ostream& operator<<(ostream &stream, dslVector< double > &out)
{
      stream<<"Vector dimension:"<<out.Size()<<"\n";
      for(int i = out.Start(); i < out.End() + 1;i++)
    {
        stream<<out.Element(i)<<"\n";
    }
      return stream;
}

ostream& operator<<(ostream &stream, dslVector< double > *out)
{
      stream<<"Vector dimension:"<<out->Size()<<"\n";
      for(int i = out->Start(); i < out->End() + 1; i++)
    {
        stream<<out->Element(i)<<"\n";
    }
      return stream;
}

ostream& operator<<(ostream &stream, dslVector< complex<double> > &out)
{
    //allow binary output
      string str = "Vector dimension:";
      str += toString(out.Size());
      str += "\n";
      stream<<&str;
    //  stream<<&out.vec;
      //  for(int i = out.Start(); i < out.End() + 1; i++)
    //    stream<<out.Element(i)<<"\n";
     return stream;
}

//istream& operator>>(istream &stream, dslVector< complex<double> > &out)
//{
//    //allow binary input
//     string str;
//      stream>>str;
//    stream>>&out.vec;
//      return stream;
//}

ostream& operator<<(ostream &stream, dslVector< complex<double> > *out)
{
    //allow binary output
      string str = "Vector dimension:";
      str += toString(out->Size());
      str += "\n";
      stream<<&str;

    //  for(int i = out->Start(); i < out->End() + 1; i++)
    //    stream<<out->Element(i)<<"\n";
      return stream;
}

void swap1(complex<double>  *in, int Size)
{
      /*** Swap the array by taking its right half part (array has to be
        in power of 2) and puts it to the beginning as:
        INPUT ARRAY
        1 2 3 4 5 6 7 8
        OUTPUT ARRAY,
        5 6 7 8 1 2 3 4
       ***/
    complex<double>  temp(0,0);
      for(int i = 1; i < Size/2 + 1; i++)
      {
        temp = in[i];
         in[i] = in[i+Size/2];
         in[i + Size/2] = temp;
      }
}

void swap2(complex<double>  *in, int Size)
{
    /*** Swap the array by "totally" interchanging elements i.e:
              INPUT ARRAY
              1 2 3 4 5 6 7 8
              OUTPUT ARRAY,
              8 7 6 5 4 3 2 1
    ***/
      complex<double>  temp(0,0);
      for(int i = 1; i < Size/2 + 1; i++)
    {
         temp=in[i];
         in[i]=in[Size+1-i];
         in[Size+1-i]=temp;
      }
}

void swap3(complex<double>  *in, int Size)
{
    /*** Swap the array as:
              INPUT ARRAY
              1 2 3 4 5 6 7 8
              OUTPUT ARRAY,
              8 1 2 3 4 5 6 7
    ***/
    complex<double>  *temp = vectorCpx(1,Size);
      temp[1]=in[Size];
      for(int i=1; i<(Size);i++)
    {
        temp[i+1]=in[i];
        in[i]=temp[i];
    }
      in[Size]=temp[Size];
      free_vectorCpx(temp,1,Size);
}

void undo_swap1(complex<double>  *in, int Size)
{
    /*** Swap the array by taking its right half part (array has to be
          in power of 2) and puts it to the beginning as:
          INPUT ARRAY
          1 2 3 4 5 6 7 8
          OUTPUT ARRAY,
          5 6 7 8 1 2 3 4
     ***/
      complex<double>  temp(0,0);
      for(int i = 1; i < Size/2 + 1; i++)
    {
        temp = in[i];
        in[i] = in[i + Size/2];
        in[i + Size/2] = temp;
      }
}

void undo_swap2(complex<double>  *in, int Size)
{
    /*** Swap the array by "totally" interchanging elements i.e:
              INPUT ARRAY
              1 2 3 4 5 6 7 8
              OUTPUT ARRAY,
              8 7 6 5 4 3 2 1
    ***/
      complex<double>  temp(0,0);
      for(int i = 1; i < Size/2 + 1; i++)
    {
        temp = in[i];
        in[i] = in[Size+1-i];
        in[Size + 1-i] = temp;
      }
}

void undo_swap3(complex<double>  *in, int Size)
{
    /*** Swap the array as:
              INPUT ARRAY
              1 2 3 4 5 6 7 8
              OUTPUT ARRAY,
              2 3 4 5 6 7 8 1
    ***/
    complex<double> *temp=vectorCpx(1,Size);

       temp[Size]=in[1];
       for(int i=1; i<(Size);i++)
    {
        temp[i]=in[i+1];
           in[i]=temp[i];
       }
   in[Size]=temp[Size];
   free_vectorCpx(temp,1,Size);
}

#define NR_END 1
complex<double>* vectorCpx(long nl, long nh)
{
    /* allocate a Complex vector with subscript range v[nl..nh]*/
      complex<double>  *v;
      v = (complex<double>  *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof( complex<double> )));
      if (!v)
      {
        //Log(lInfo)<<"Allocation failure in vectorCpx";
        return nullptr;
      }
      return v-nl+NR_END;
}

void free_vectorCpx(complex<double>  *v, long nl, long /*nh*/)
{
    /*free a  complex<double> vector allocated with vectorCpx */
      free((char*) (v+nl-NR_END));
}


}
