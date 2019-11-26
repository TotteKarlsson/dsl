cmake_minimum_required(VERSION 2.8)
set(target mkjson)

include_directories(
./../
)

set(src
mkjson
)

#===== Shared library
if(${BUILD_SHARED_LIBS})
    add_library(${target} SHARED
    ${src}
    )

    if(WIN32)
        set_property(TARGET ${target}  
                        PROPERTY COMPILE_DEFINITIONS 
                        EXPORT_MKJSON
        )
    endif()            

    install(    
    TARGETS ${target}
    RUNTIME DESTINATION bin COMPONENT core
    LIBRARY DESTINATION lib COMPONENT core
    ARCHIVE DESTINATION lib COMPONENT core
    )            
endif()

#===== General Installs
FILE (GLOB headers *.h)
install (  
FILES ${headers}			 	
DESTINATION include/mkjson 
COMPONENT cxx_headers
)


