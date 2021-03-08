cmake_minimum_required(VERSION 2.8)
set(target dslVCLCommon)

include_directories(
    ./../
    ./../../Common
    ./../../Math
    ./../../ThirdParties/Poco/Foundation/include/
)

message("Build folder is : " ${BUILD})

set(src
dslVCLUtils
dslVCLCommon
dslApplicationInfo
dslLogFileReader
dslTSaveFormToRegistry
)

#===== Shared library
if(${BUILD_SHARED_LIBS})
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Hi${CMAKE_SOURCE_DIR}/pch/dsl_pch.h -Hh=${CMAKE_SOURCE_DIR}/pch/dsl_pch.h -H=${CMAKE_SOURCE_DIR}/pch/dsl_pch.cmake -H")
    if(CMAKE_CXX_COMPILER_ID STREQUAL "Embarcadero" AND CMAKE_BASE_NAME STREQUAL "bcc32" )
    endif()
 
    add_library(${target} SHARED
        ${src}
    )
    target_include_directories (${target} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
    
    if(NOT ${LIBRARY_POSTFIX} STREQUAL "")
        message(${LIBRARY_POSTFIX})
        set_target_properties(${target}  PROPERTIES SUFFIX ${LIBRARY_POSTFIX})
    endif()

    target_compile_definitions(${target} PRIVATE EXPORT_VCLCOMMON)

    if (CMAKE_SYSTEM MATCHES "Windows")
        target_link_libraries(
            ${target} 
                dslFoundation
                tinyxml2
                poco_foundation
                Shell32.lib
                ws2_32
                version
        )
    endif()

    if(${INSTALL_CXX_LIBS})
        install(    
            TARGETS ${target} 
            RUNTIME DESTINATION bin COMPONENT core
            LIBRARY DESTINATION lib COMPONENT core
            ARCHIVE DESTINATION lib COMPONENT core
        )       

        #Headers
        FILE (GLOB vclcommon_headers *.h)

        install(   
            FILES ${vclcommon_headers} 
            DESTINATION include/dsl 
            COMPONENT cxx_headers
        )

        if(CMAKE_CXX_COMPILER_ID STREQUAL "Embarcadero" AND CMAKE_BASE_NAME STREQUAL "bcc32" )
            install(FILES
                ${PROJECT_BINARY_DIR}/bin/${target}.tds
                DESTINATION bin
                COMPONENT debug
            )
        endif()        

    endif()
endif()

