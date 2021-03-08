cmake_minimum_required(VERSION 3.13)
project(dsl)
SET(DSL_MAJOR_VERSION 0)
SET(DSL_MINOR_VERSION 8)
SET(DSL_BUILD_VERSION 5)
SET(DSL_VERSION "${DSL_MAJOR_VERSION}.${DSL_MINOR_VERSION}.${DSL_BUILD_VERSION}")
set(DSL_ROOT 	${CMAKE_CURRENT_SOURCE_DIR})
set(LIBRARY_POSTFIX  "" CACHE STRING "Appended to library name")

OPTION(INSTALL_CXX_EXAMPLES         "Install DSL CXX Examples"	                ON)
OPTION(INSTALL_PYTHON 			    "Build Python Module"                       OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY 	${PROJECT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY 	${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 	${PROJECT_BINARY_DIR}/bin)

#=== COMPILER SPECIFICS 
if(CMAKE_CXX_COMPILER_ID STREQUAL "Embarcadero" AND CMAKE_BASE_NAME STREQUAL "bcc32")
    message("Using bcc32")
    set(SUPPRESS_WARNINGS   "-w-8128 -w-8057 -w-8012 -w-8004 -w-8070")
#    #Borland hack.. we always need dynamic runtime (-tR) :(       
#    set(CMAKE_C_FLAGS               "${CMAKE_C_FLAGS} -tR")
#    set(CMAKE_CXX_FLAGS             "${CMAKE_CXX_FLAGS} -tR")
#    set(CMAKE_EXE_LINKER_FLAGS      "${CMAKE_EXE_LINKER_FLAGS} -tR")
#    set(CMAKE_MODULE_LINKER_FLAGS   "${CMAKE_MODULE_LINKER_FLAGS} -tR")
#    set(CMAKE_SHARED_LINKER_FLAGS   "${CMAKE_SHARED_LINKER_FLAGS} -tR")

    set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_INCLUDES 0)
    set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_OBJECTS 0)
    include_directories( ${BOOST_ROOT})

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND CMAKE_BASE_NAME STREQUAL "clang++") 
    message("Using bcc32x")
    set(CG_32_BOOST_ROOT ${BOOST_ROOT})
    include_directories( ${BOOST_ROOT}) 
    #link_directories( "C:\\CG\\10.2.3_temp\\lib\\win32c\\release") 

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Embarcadero" AND CMAKE_BASE_NAME STREQUAL "bcc32c") 
    message("Using bcc32c")
    set(CG_32_BOOST_ROOT ${BOOST_ROOT})
    include_directories( ${BOOST_ROOT}) 
    link_directories( "C:\\CG\\10.2.3_temp\\lib\\win32c\\release") 

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message("Using MSVC")
    set(SUPPRESS_WARNINGS   "/wd4221 /wd4018 /wd4996 /wd4251" )
    add_definitions(
        -D_CRT_NONSTDC_NO_DEPRECATE
        -D_CRT_SECURE_NO_WARNINGS
    )

else()
    message("No compiler!!" ${CMAKE_CXX_COMPILER_ID} ${CMAKE_BASE_NAME})
endif()

#Boost root
set(BOOST_ROOT CACHE PATH "Directory containing Boost.")
if("${BOOST_ROOT}" STREQUAL "")
  set(BOOST_ROOT "C:/libs/boost" CACHE PATH "Directory containing Boost headers" FORCE)
endif()
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set (BOOST_MIN_VERSION "1.39.0")
    set (Boost_NO_BOOST_CMAKE ON)
    set( Boost_NO_SYSTEM_PATHS on CACHE BOOL "Do not search system for Boost" )
    FIND_PACKAGE(Boost ${BOOST_MIN_VERSION} REQUIRED COMPONENTS thread)

    message(STATUS "Setting up BOOST")
    message(STATUS " Includes - ${Boost_INCLUDE_DIRS}")
    message(STATUS " Library  - ${Boost_LIBRARY_DIRS}")
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif()  
#if (CMAKE_CXX_COMPILER_ID STREQUAL "bcc32c")
#    set (BOOST_MIN_VERSION "1.39.0")
#    set (Boost_NO_BOOST_CMAKE ON)
#    set( Boost_NO_SYSTEM_PATHS on CACHE BOOL "Do not search system for Boost" )
#    FIND_PACKAGE(Boost ${BOOST_MIN_VERSION} REQUIRED COMPONENTS )
#
#    message(STATUS "Setting up BOOST")
#    message(STATUS " Includes - ${Boost_INCLUDE_DIRS}")
#    message(STATUS " Library  - ${Boost_LIBRARY_DIRS}")
#    include_directories(${Boost_INCLUDE_DIRS})
#    link_directories(${Boost_LIBRARY_DIRS})
#endif()  
# Warning string looks different depending on the compiler..
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SUPPRESS_WARNINGS}")

if(${INSTALL_PYTHON})
    OPTION(INSTALL_PYTHON_EXAMPLES  "Install Python Examples" ON)
    find_package(PythonInterp)
    find_package(PythonLibs)
    message("Python include folder: " ${PYTHON_INCLUDE_DIRS})
    include_directories(
    ${PYTHON_INCLUDE_DIRS}
    )
    add_subdirectory(PythonPlugins)
endif()    
 
#Source Code Folders
add_subdirectory(Foundation)
add_subdirectory(VCL)
#add_subdirectory(Math/mtrand)

#add_subdirectory(Wrappers)
#add_subdirectory(Examples)
add_subdirectory(ThirdParties)
add_subdirectory(redist)

#======================= INSTALL ========================================================
set(RootDest .)

# MS: I don't think these should be used. We should use the ones from the real RootDest, from where they are already installed.
#install (FILES 
#    LICENSE.txt 
#    AUTHORS.txt 
#    VERSION.txt 
#    INSTALL.txt 
#    NOTICE.txt
#    CHANGELOG.txt
#    DESTINATION ${RootDest} 	
#    COMPONENT info
#)
