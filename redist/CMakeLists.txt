cmake_minimum_required(VERSION 2.8)
if(CMAKE_CXX_COMPILER_ID STREQUAL "Embarcadero" AND CMAKE_BASE_NAME STREQUAL "bcc32" )
    set(BOOST_THREAD_DLL "boost_thread-bcb-mt-1_39")
    set(BOOST_THREAD_D_DLL "boost_thread-bcb-mt-d-1_39")
    message("Configuring file: " ${BOOST_THREAD_DLL})
    message("Configuring file: " ${BOOST_THREAD_D_DLL})
    configure_file(${BOOST_THREAD_DLL} ${BOOST_THREAD_DLL}.dll COPYONLY)
    configure_file(${BOOST_THREAD_D_DLL} ${BOOST_THREAD_D_DLL}.dll COPYONLY)

    install (FILES 
                    ${CMAKE_CURRENT_BINARY_DIR}/${BOOST_THREAD_DLL}.dll
                    ${CMAKE_CURRENT_BINARY_DIR}/${BOOST_THREAD_D_DLL}.dll
                    DESTINATION bin 
                    )

endif()        


