CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
project(poco_sqliteconnector_src)

# Option that allows users to build static and/or shared libraries
# ----------------------------------------------------------------
set(target poco_sqlite_connector) 

set(poco_include_folder 
    ${CMAKE_CURRENT_SOURCE_FOLDER}../include
     )

set(sources 
sqlite3.c    
Binder.cpp
Connector.cpp
Extractor.cpp
SessionImpl.cpp
SQLiteException.cpp
SQLiteStatementImpl.cpp
sqlite3.c
Utility.cpp
)

if(${BORLAND})
add_definitions(
             -w-8012                     #Comparing signed /unsigned
             -w-8057                     #Parameter never used
             -w-8004                     #'var' is assigned a value that is never used
             -w-8123                     #Path not found
             -w-8066                     #Unreachable code
             -w-8104                     #Local static with constructor...
             -w-8008                     #Condition is always false..
             -w-8022           
        )
add_definitions( -D_WIN32)
add_definitions( -D_THREADSAFE)
add_definitions( -D_NOTCL)
endif()

#if(CMAKE_SYSTEM MATCHES "Windows")
# 
# add_definitions( -DPOCO_OS_FAMILY_WINDOWS)
# set(SYSLIBS iphlpapi gdi32 odbc32)
# 
# if (CMAKE_C_COMPILER_ID MATCHES "MSVC")
#        message(STATUS "XXX: MS Visual Compiler detected")
# endif (CMAKE_C_COMPILER_ID MATCHES "MSVC")
#
#endif(CMAKE_SYSTEM MATCHES "Windows")
#
#if (CMAKE_SYSTEM MATCHES "Linux")
#  add_definitions( -DPOCO_OS_FAMILY_UNIX )
#  # Standard 'must be' defines
#  add_definitions( -D_XOPEN_SOURCE=500 -D_REENTRANT -D_THREAD_SAFE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64)
#  set(SYSLIBS  pthread dl rt)
#endif(CMAKE_SYSTEM MATCHES "Linux")

if(${MSVC})
#set(....
endif()

include_directories(
${poco_include_folder}
${CMAKE_CURRENT_SOURCE_FOLDER}../../include
${MYSQL_C_HEADER_FOLDER} 
#${CMAKE_SOURCE_DIR}/mysql-c/include
${CMAKE_CURRENT_SOURCE_FOLDER}../../../foundation/include
)

if(BUILD_SHARED_LIBS)
    add_library(${target} SHARED ${sources})
    set_property(TARGET ${target}  
                 PROPERTY  COMPILE_DEFINITIONS 
                 SQLite_EXPORTS
                 POCO_DLL
                 Data_EXPORTS
                 ) 
    
    target_link_libraries(${target} poco_foundation poco_data)

    install(TARGETS ${target} 
        RUNTIME DESTINATION bin 
        LIBRARY DESTINATION lib 
        ARCHIVE DESTINATION lib)
endif()


if(BUILD_STATIC_LIBS)
    add_library(${target}-static STATIC ${sources})
    set_property(TARGET ${target}-static  
                 PROPERTY  COMPILE_DEFINITIONS 
                           POCO_STATIC
                           PCRE_STATIC
                 ) 

    if(WIN32)
    set_property(TARGET ${target}-static  
                 PROPERTY  COMPILE_DEFINITIONS 
                           WIN32
                 ) 

    endif()

    install(TARGETS ${target}-static 
        LIBRARY DESTINATION lib 
        ARCHIVE DESTINATION lib)
endif()

#INSTALLING ======================
FILE (GLOB headers ${CMAKE_CURRENT_SOURCE_FOLDER}../include/Poco/Data/SQLite/*.h)

#Install required files
install(FILES ${headers} 
    DESTINATION include/Poco/Data/SQLite
)

