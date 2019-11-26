cmake_minimum_required(VERSION 2.8)
set(target sqlite)

include_directories(
./../
)

set(src
sqlite3.c
)

#===== Shared library
if(${BUILD_SHARED_LIBS})
    add_library(${target} SHARED
    ${src}
    )

    if(WIN32)
        set_target_properties(${target}  PROPERTIES
        COMPILE_DEFINITIONS "SQLITE_API=__declspec(dllexport)"
        OUTPUT_NAME ${target}${LIBRARY_POSTFIX}
        )
    endif()            

    install(    
    TARGETS ${target}
    RUNTIME DESTINATION bin COMPONENT core
    LIBRARY DESTINATION lib COMPONENT core
    ARCHIVE DESTINATION lib COMPONENT core
    )            
endif()

###===== Static library
#if(${BUILD_STATIC_LIBS})
#    add_library(${target}-static STATIC
#    ${src}
#    )
#
#    set_property(TARGET ${target}-static  
#    PROPERTY COMPILE_DEFINITIONS 
#    )
#
#    install(    
#    TARGETS ${target}-static
#    RUNTIME DESTINATION bin COMPONENT core
#    LIBRARY DESTINATION lib COMPONENT core
#    ARCHIVE DESTINATION lib COMPONENT core
#    )            
#endif()

#MESSAGE("ATTN: SQLITE is not built as a shared library")

#if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
#install(FILES ${CMAKE_BINARY_DIR}/bin/${target}.tds DESTINATION bin)
#endif()

#===== General Installs
FILE (GLOB headers *.h)
install (  
FILES ${headers}			 	
DESTINATION include/sqlite 
COMPONENT cxx_headers
)


