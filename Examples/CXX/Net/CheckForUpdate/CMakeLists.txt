cmake_minimum_required(VERSION 2.8)

set(target first_step)
PROJECT(${target})


if(CMAKE_SYSTEM MATCHES "Linux") 
    add_executable(${target} MACOSX_BUNDLE main.cpp)
else()
    add_executable(${target} main.cpp)
endif()
  
link_directories(					
    ${LIBRARY_OUTPUT_PATH}
    ${VTK_LIB_FOLDER}
    ${CMAKE_INSTALL_PREFIX}/lib
    ${THIRDPARTY_INSTALL}/lib
    ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
)

target_link_libraries(${target} 
mtkCommon-static
)
if(CMAKE_SYSTEM MATCHES "Windows") 
    target_link_libraries(${target} 
        iphlpapi
    )
endif()

if(CMAKE_SYSTEM MATCHES "Linux") 
    set (CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
endif()

install(    
    TARGETS ${target} 	
    DESTINATION bin 
    COMPONENT compiled_examples
)



