#include "Python.h"
#include "..\Lib\site-packages\numpy\core\include\numpy\arrayobject.h"
#include "pythonUtils.h"
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

int main(int argc, char* argv[])
{
    Py_Initialize();
    import_array();

    // Build the 2D array in C++
    const int SIZE = 3;
    int dims[] = {SIZE, SIZE};
    const int ND = 2;
    double(*c_array)[SIZE] = { new double[SIZE][SIZE] };

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            c_array[i][j] = i + j;
        }
    }

    // Convert it to a NumPy array.
    PyObject *pArray = PyArray_SimpleNewFromData(ND, dims, NPY_DOUBLE, reinterpret_cast<void*>(c_array));

    // import mymodule
    const char *module_name = "Test";
    PyObject *pName = PyUnicode_FromString(module_name);
    PyObject *pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    ////////////////// FIRST FUNCTION, PASS a  C array, get a Numpy Array back
    // import function
    const char *func_name = "f1";
    PyObject *pFunc = PyObject_GetAttrString(pModule, func_name);
    PyObject *pReturn = PyObject_CallFunctionObjArgs(pFunc, pArray, NULL);
    PyArrayObject *np_ret = reinterpret_cast<PyArrayObject*>(pReturn);

    // Convert back to C++ array and print.
    int len = PyArray_SHAPE(np_ret)[0];
    double* c_out;
    c_out = reinterpret_cast<double*>(PyArray_DATA(np_ret));
    std::cout << "Printing output array - C++" << std::endl;
    for (int i = 0; i < len; i++)
    {
        std::cout << c_out[i] << ' ';
    }
    std::cout << std::endl << std::endl;

    ////////////////// SECOND FUNCTION, NO ARGUMENT, just get a Numpy Array back
    // import function without arguments
    const char *func_name2 = "f2";
    PyObject *pFunc2 = PyObject_GetAttrString(pModule, func_name2);
    PyObject *pReturn2 = PyObject_CallFunctionObjArgs(pFunc2, NULL);
    PyArrayObject *np_ret2 = reinterpret_cast<PyArrayObject*>(pReturn2);

    // convert back to C++ array and print
    int len2 = PyArray_SHAPE(np_ret2)[0];
    double* c_out2 = reinterpret_cast<double*>(PyArray_DATA(np_ret2));
    std::cout << "Printing output array 2 - C++" << std::endl;
    for (int i = 0; i < len2; i++){
        std::cout << c_out2[i] << ' ';
    }

    std::cout << std::endl << std::endl;

    Py_Finalize();
    return 0;
}

#pragma comment(lib, "Python3_CG.lib")


