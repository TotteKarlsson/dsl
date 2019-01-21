cmake_minimum_required(VERSION 2.8)
set(target dslPlugins)

include_directories(
    ./../Common
    ${TP_INCLUDE}
    ${PYTHON_INCLUDE_DIRS}
)

link_directories(
#${CMAKE_INSTALL_PREFIX}/lib
)

set(src
dslPlugin
dslPluginManager
dslPluginMetaData
dslPluginWithEvents
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Hu -Hi${CMAKE_SOURCE_DIR}/pch/dsl_pch.h -H=${CMAKE_BINARY_DIR}/dsl.csm")

#===== Shared library
if(${BUILD_SHARED_LIBS})
    add_library(${target} SHARED
    ${src}
    )

    set_property(TARGET ${target}  
        PROPERTY COMPILE_DEFINITIONS 
        EXPORT_PLUGINS
    )

    target_link_libraries(${target} 
        dslCommon
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
        DESTINATION include/dsl 
        COMPONENT cxx_headers
    )

    install(FILES
        ${PROJECT_BINARY_DIR}/bin/${target}.tds
        DESTINATION bin
        COMPONENT debug
    )


endif()

