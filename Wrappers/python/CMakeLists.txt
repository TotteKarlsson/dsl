cmake_minimum_required(VERSION 2.8)
project(dsl)

if (WIN32)
set(SWIG_EXECUTABLE "C:/swigwin/swig.exe")
endif()

find_package(SWIG REQUIRED)
include(UseSWIG)

find_package(PythonInterp)
find_package(PythonLibs)

get_filename_component(PYTHON_LIB_FOLDER ${PYTHON_LIBRARIES} DIRECTORY CACHE)
message("Python lib folder: "       ${PYTHON_LIB_FOLDER})
message("Python include folder: "   ${PYTHON_INCLUDE_DIRS})
message("Python libraries: "        ${PYTHON_LIBRARIES})
message("DSL Libraries: "           ${DSL_LIBS})

set(PyModule "dsl")
include_directories(
    .
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${DSL_ROOT}/Common
    ${DSL_ROOT}/Plugins
    ${DSL_ROOT}/PythonPlugins
    ${TP_INCLUDE}
    ${PYTHON_INCLUDE_PATH}
)

link_directories(
${CMAKE_INSTALL_PREFIX}/lib
${CMAKE_BINARY_DIR}/lib
${PYTHON_LIB_FOLDER}
)

set(CMAKE_MODULE_LINKER_FLAGS ${CMAKE_CURRENT_SOURCE_DIR}/${PyModule}.def)

set_source_files_properties(${PyModule}.i PROPERTIES CPLUSPLUS ON)
set_source_files_properties(${PyModule}.i PROPERTIES SWIG_FLAGS "-threads")

SWIG_ADD_LIBRARY(${PyModule}
    TYPE MODULE 
    LANGUAGE python 
    SOURCES ${PyModule}.i
    )
    
SWIG_LINK_LIBRARIES (${PyModule}
 #   ${DSL_LIBS}
     dslFoundation
     dslPythonPlugins
#    ${PYTHON_LIB_FOLDER}/Python3_CG.lib    
    ${PYTHON_LIB_FOLDER}/Python37_CG.lib    
)

# INSTALL PYTHON BINDINGS
# Get the python site packages directory by invoking python
execute_process(COMMAND python -c "import site; print(site.getsitepackages()[0])" OUTPUT_VARIABLE PYTHON_SITE_PACKAGES OUTPUT_STRIP_TRAILING_WHITESPACE)
message("PYTHON_SITE_PACKAGES = ${PYTHON_SITE_PACKAGES}")

SET(SWIG_RUNTIME ${CMAKE_CURRENT_BINARY_DIR}/dsl_swigpyrun.h)
execute_process(COMMAND ${SWIG_EXECUTABLE} -python -external-runtime ${SWIG_RUNTIME})

install(
    TARGETS _${PyModule}
    DESTINATION ${PYTHON_SITE_PACKAGES})

install(
    FILES         ${PyModule}.i ${SWIG_RUNTIME}
    DESTINATION   include/dsl
)

install(
    FILES         ${CMAKE_CURRENT_BINARY_DIR}/${PyModule}.py 
                  ${CMAKE_BINARY_DIR}/lib/_${PyModule}.tds
    DESTINATION   ${PYTHON_SITE_PACKAGES}
)
