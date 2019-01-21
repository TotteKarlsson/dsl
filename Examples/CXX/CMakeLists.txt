CMAKE_MINIMUM_REQUIRED(VERSION 2.6.3 FATAL_ERROR)
PROJECT(DSLExamples)

link_directories(					
    ${CMAKE_INSTALL_PREFIX}/lib
    ${THIRDPARTY_INSTALL}/lib
)

include_directories(
    ${DSL_ROOT}
    ${DSL_ROOT}/Common
    ${DSL_ROOT}/Math
    ${DSL_ROOT}/Database
    ${CMAKE_SOURCE_DIR}/ThirdParties/Poco/Foundation/include
    ${CMAKE_INSTALL_PREFIX}/include
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



