cmake_minimum_required(VERSION 2.8)
set(target dslPythonPlugins)
find_package(PythonInterp)
find_package(PythonLibs)

include_directories(
    ./../Common
    ./../Plugins
    ${CMAKE_SOURCE_DIR}/ThirdParties/Poco/Foundation/include
    #//${CMAKE_SOURCE_DIR}/ThirdParties/tinyxml2
    ${TP_INCLUDE}
    ${PYTHON_INCLUDE_DIRS}
)

link_directories(
${CMAKE_INSTALL_PREFIX}/lib
${PYTHON_LIB_FOLDER}
)


set(src
dslPythonPlugin
dslPythonInterpreter
dslPythonPluginManager
dslPythonPluginWorker
)

message("DSL Libs: " ${DSL_LIBS})
#===== Shared library
if(${BUILD_SHARED_LIBS})
    add_library(${target} SHARED
    ${src}
    )

    set_property(TARGET ${target}  
        PROPERTY COMPILE_DEFINITIONS 
        EXPORT_PYTHON_PLUGINS
    )

    target_link_libraries(${target} 
        ${DSL_LIBS}
#        ${PYTHON_LIB_FOLDER}/Python3_CG.lib
        ${PYTHON_LIB_FOLDER}/Python37_CG.lib    
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

