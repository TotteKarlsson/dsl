#pragma hdrstop
#include "pythonUtils.h"
#include "..\Lib\site-packages\numpy\core\include\numpy\arrayobject.h"
//---------------------------------------------------------------------------
void output_result( PyObject* rslt )
{
   if( !rslt )
   {
      printf("output_result: argument must be a valid pointer\n");
      return;
   }

   // output scalar result
   if( PyFloat_Check(rslt) )
   {
      printf( "result: %f\n", PyFloat_AsDouble(rslt) );
   }

   if( PyArray_Check(rslt) )
   {
      PyArrayObject* obj = PyArray_GETCONTIGUOUS( (PyArrayObject*) rslt );
      int ndims = obj->nd;
      int* dims = obj->dimensions; 			// not copying data
      double* data = (double*) obj->data; 	// not copying data
      int i, j, k = 0;

      // output vector result
      if( ndims == 1 )
      {
         for( i=0; i<dims[0]; i++ )
         {
            printf( "element: %i  value: %f\n", i, data[k++] );
         }
         printf("\n");
      }

      // output matrix reult
      else if( ndims == 2 )
      {
         for( i=0; i<dims[0]; i++ )
         {
            for( j=0; j<dims[1]; j++ )
            {
               printf( "%f  ", data[k++] );
            }
            printf( "\n" );
         }
      }

      // output N-D result
      else
      {
         for( i=0; i<ndims; i++ )
         {
            for( j=0; j<dims[i]; j++ )
            {
               printf( "dimension: %i  element: %i  value: %f\n", i, j, data[k++] );
            }
         }
      }

      // clean
      Py_XDECREF(obj);
   }
}

void handle_error( PyObject* fe )
{
    // get exception info
    PyObject *type, *value, *traceback;
    PyErr_Fetch( &type, &value, &traceback );
    PyErr_NormalizeException( &type, &value, &traceback );

    // create a argument for "format exception"
    PyObject* args = PyTuple_New(3);
    PyTuple_SetItem( args, 0, type );
    PyTuple_SetItem( args, 1, value );
    PyTuple_SetItem( args, 2, traceback );

    // get a list of string describing what went wrong
    PyObject* output = PyObject_CallObject( fe, args );

    // print error message
    int i, n = PyList_Size( output );
    for( i=0; i<n; i++ )
    {
    	printf( "%s", PyBytes_AsString( PyList_GetItem( output, i ) ) );
    }

    // clean up
    Py_XDECREF( args );
    Py_XDECREF( output );
}


