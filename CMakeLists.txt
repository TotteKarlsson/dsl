cmake_minimum_required(VERSION 2.8)
project(dsl)

SET(DSL_MAJOR_VERSION 0)
SET(DSL_MINOR_VERSION 8)
SET(DSL_BUILD_VERSION 5)
SET(DSL_VERSION "${DSL_MAJOR_VERSION}.${DSL_MINOR_VERSION}.${DSL_BUILD_VERSION}")
set(DSL_ROOT 	${CMAKE_CURRENT_SOURCE_DIR})

#Options
if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE )
endif()

OPTION(BUILD_SHARED_LIBS 		    "Build Shared Libs"                         ON)
OPTION(BUILD_FOUNDATION 		    "Build Foundation"                          ON)
OPTION(INSTALL_CXX_LIBS 		    "Install CXX libraries and header"          ON)
OPTION(INSTALL_CXX_EXAMPLES         "Install CXX Examples"	                    ON)
OPTION(INSTALL_PYTHON 			    "Build Python Module"                       OFF)

#Boost root
set(BOOST_ROOT  CACHE PATH "Directory containing Boost.")
if("${BOOST_ROOT}" STREQUAL "")
  set(BOOST_ROOT "C:/Borland" CACHE PATH "Directory containing Boost headers" FORCE)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY 	${PROJECT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY 	${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 	${PROJECT_BINARY_DIR}/bin)

#=== COMPILER SPECIFICS 
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Embarcadero" AND ${CMAKE_BASE_NAME} STREQUAL "bcc32" )
    set(SUPPRESS_WARNINGS   "-w-8128 -w-8057 -w-8012 -w-8004 -w-8070" )
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug;Release")
    message("Using bcc32")

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Embarcadero" AND ${CMAKE_BASE_NAME} STREQUAL "bcc32c") 
    message("Using bcc32c")
#    set(SUPPRESS_WARNINGS "-Wunused-value")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(SUPPRESS_WARNINGS   "/wd4221 /wd4018 /wd4996 /wd4251" )
#    set(CMAKE_CXX_FLAGS                "${CMAKE_CXX_FLAGS} /EHsc ")
#    set(CMAKE_CXX_MP_FLAG               ON CACHE BOOL "")
    add_definitions(
    -D_CRT_NONSTDC_NO_DEPRECATE
    -D_CRT_SECURE_NO_WARNINGS
    )
    message("Using MSVC")
else()
    message("No compiler!!" ${CMAKE_CXX_COMPILER_ID} ${CMAKE_BASE_NAME})
endif()

#Warning string looks different depending on the compiler..
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SUPPRESS_WARNINGS}")

set(TP_INCLUDE                     ${CMAKE_INSTALL_PREFIX}/include)

if(${INSTALL_PYTHON})
    OPTION(INSTALL_PYTHON_EXAMPLES  "Install Python Examples"	                 ON)
    find_package(PythonInterp)
    find_package(PythonLibs)
    message("Python include folder: " ${PYTHON_INCLUDE_DIRS})
    include_directories(
    ${PYTHON_INCLUDE_DIRS}
    )
    add_subdirectory(PythonPlugins)
endif()    
 
include_directories(
${PYTHON_INCLUDE_DIRS}
${BOOST_ROOT}
${BOOST_ROOT}/boost/tr1/tr1
)

if(BUILD_FOUNDATION)
    set(DSL_LIBS "dslFoundation" CACHE STRING "Link Libs" FORCE)
else()
    set(DSL_LIBS "dslCommon dslPlugins" CACHE STRING "Link Libs" FORCE)
endif()

message("DSL Libs: " ${DSL_LIBS})

#set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_INCLUDES 0)
#set(CMAKE_CXX_USE_RESPONSE_FILE_FOR_OBJECTS 0)

#Source Code Folders
if(BUILD_FOUNDATION)
    add_subdirectory(Foundation)
    add_subdirectory(Math/mtrand)
else()
    add_subdirectory(Common)
    add_subdirectory(Math)
    add_subdirectory(IPC)
    add_subdirectory(Database)
    add_subdirectory(Plugins)
endif()

#Data Folders
add_subdirectory(Wrappers)
add_subdirectory(Examples)


#======================= INSTALL ========================================================
set(RootDest .)
install (FILES 
    README.txt 
    LICENSE.txt 
    AUTHORS.txt 
    VERSION.txt 
    INSTALL.txt 
    NOTICE.txt
    CHANGELOG.txt
    DESTINATION ${RootDest} 	
    COMPONENT info
   )

