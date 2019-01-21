cmake_minimum_required(VERSION 2.8)
set(target dslIPC)

include_directories(
.
./..
${DSL_ROOT}/Common
${BOOST_ROOT}
${TP_INCLUDE}
)

set(src
dslIPCData.cpp
dslIPCMessage.cpp
dslIPCMessageBuilder.cpp
dslIPCMessageEnums.cpp
dslIPCMessageProcessor.cpp
dslIPCReceiver.cpp
dslIPCServer.cpp
dslSocket.cpp
dslSocketClient.cpp
dslSocketReceiver.cpp
dslSocketServer.cpp
dslSocketWorker.cpp
dslToggleSocketConnectionThread.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -H -Hi${CMAKE_SOURCE_DIR}/pch/dsl_pch.h -H=${CMAKE_BINARY_DIR}/dsl.csm")

#===== Shared library
if(${BUILD_SHARED_LIBS})
    add_library(${target} SHARED
    ${src}
    )

    set_property(TARGET ${target}  
    PROPERTY COMPILE_DEFINITIONS 
            EXPORT_IPC
    )

    #link libraries
    target_link_libraries(${target}
        dslCommon
        #poco_foundation
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

#===== Static library
if(${BUILD_STATIC_LIBS})
    add_library(${target}-static STATIC
    ${src}
    )

    set_property(TARGET ${target}-static  
        PROPERTY COMPILE_DEFINITIONS 
        STATIC_IPC
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

