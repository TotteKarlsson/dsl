cmake_minimum_required(VERSION 2.8)
set(target dslCommon)

include_directories(
    ./../
    ${TP_INCLUDE}
)

link_directories(${CMAKE_BINARY_DIR}/lib)

set(src
dslBaseProperty
dslClassProperty
dslColor
dslCommand
dslCommon
dslCompareStrings
dslConstants
dslException
dslFileSet
dslFileUtils
dslGetOptions
dslIniFile
dslIniFileProperties
dslIniKey
dslIniSection
dslLogFile
dslLoggerUtils
dslLogging
dslLogLevel
dslLogOutput
dslMessageContainer
dslMessageProcessor
dslObject
dslObserver
dslProject
dslProjects
dslProperties
dslPropertiesContainer
dslRange
dslStopWatch
dslStreamCenteredOutput
dslStringList
dslStringUtils
dslStringBuilder
dslSubject
dslThread
dslTimer
dslTypeInfo
dslUtils
dslVersion
dslWin32Utils
dslXMLUtils
)

#===== Shared library
if(${BUILD_SHARED_LIBS})
    add_library(${target} SHARED
    ${src}
    )
    
    set_property(TARGET ${target}  
        PROPERTY COMPILE_DEFINITIONS 
        EXPORT_COMMON
    )

    #link libraries
    target_link_libraries(${target} 
        ${CMAKE_INSTALL_PREFIX}/lib/tinyxml2.lib
        ${CMAKE_INSTALL_PREFIX}/lib/POCO_FOUNDATION.LIB
    )

    if(${INSTALL_CXX_LIBS})
        install(    
        TARGETS ${target} 
        RUNTIME DESTINATION bin COMPONENT core
        LIBRARY DESTINATION lib COMPONENT core
        ARCHIVE DESTINATION lib COMPONENT core
        )            
    endif()

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -H -Hi${CMAKE_SOURCE_DIR}/pch/dsl_pch.h -H=${CMAKE_BINARY_DIR}/dsl.csm")
endif() #Shared lib

#===== Static library
if(${BUILD_STATIC_LIBS})
    add_library(${target}-static STATIC
        ${src} 
    )

    set_property(TARGET ${target}-static  
        PROPERTY COMPILE_DEFINITIONS 
        DSL_STATIC
        POCO_STATIC
    )

    target_link_libraries(${target}-static 
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


#===== General Installs
if(${INSTALL_CXX_LIBS})
    FILE (GLOB headers *.h)
    install (   
        FILES ${headers} 	 		 	
        DESTINATION include/dsl 
        COMPONENT cxx_headers
    )

    install(FILES
        ${PROJECT_BINARY_DIR}/bin/${target}.tds
        DESTINATION bin
        COMPONENT debug
    )

endif()

