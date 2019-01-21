cmake_minimum_required(VERSION 2.8)
set(target dslDataBase)

include_directories(
./../
./../Common
${TP_INCLUDE}
)

set(src
dslSQLite
dslSQLiteBinary
dslSQLiteBuffer
dslSQLiteException
dslSQLiteQuery
dslSQLiteStatement
dslSQLiteTable
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Hu -Hi${CMAKE_SOURCE_DIR}/pch/dsl_pch.h -H=${CMAKE_BINARY_DIR}/dsl.csm")

#===== Static library
if(BUILD_STATIC_LIBS)
add_library(${target}-static STATIC
${src}
)

set_property(TARGET ${target}-static  
PROPERTY COMPILE_DEFINITIONS 
DSL_STATIC
)

target_link_libraries( ${target}-static
dslCommon-static
SQLite-static
)

    if(${INSTALL_CXX_LIBS})
        install(    
        TARGETS ${target}-static
        RUNTIME DESTINATION bin COMPONENT core
        LIBRARY DESTINATION lib COMPONENT core
        ARCHIVE DESTINATION lib COMPONENT core
        )            
    endif()
endif() 

#===== Shared library
if(BUILD_SHARED_LIBS)
add_library(${target} SHARED
${src}
)

set_property(TARGET ${target}  
PROPERTY COMPILE_DEFINITIONS 
         SHARED_DATABASE
         EXPORT_DATABASE
)

#link libraries
target_link_libraries( ${target} 
dslCommon
SQLite
)

    if(${INSTALL_CXX_LIBS})
        install(    
        TARGETS ${target} 
        RUNTIME DESTINATION bin COMPONENT core
        LIBRARY DESTINATION lib COMPONENT core
        ARCHIVE DESTINATION lib COMPONENT core
        )            
    endif()
endif() #Shared lib

#===== General Installs
if(${INSTALL_CXX_LIBS})
    FILE (GLOB headers *.h)
    install (   
        FILES ${headers}			 	
        DESTINATION include/dsl/DataBase 
        COMPONENT cxx_headers
    )
endif()

