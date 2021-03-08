CMAKE_MINIMUM_REQUIRED(VERSION 2.6.3 FATAL_ERROR)
PROJECT(DSLExamples)

include_directories(
    ${DSL_ROOT}
    ${DSL_ROOT}/Common
    ${DSL_ROOT}/Math
    ${DSL_ROOT}/Database
    ${DSL_ROOT}/ThirdParties/
    ${DSL_ROOT}/ThirdParties/Poco/Foundation/include/
)

if(INSTALL_CXX_EXAMPLES)
    add_subdirectory("Common")
#    add_subdirectory("Data")
#    add_subdirectory("Math")
#    add_subdirectory("Molecular")
#    add_subdirectory("Graphics")
#    add_subdirectory("SpinDynamics")
#    add_subdirectory("Moleculix")
#    add_subdirectory("vtk")
endif()



