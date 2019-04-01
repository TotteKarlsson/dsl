cmake_minimum_required(VERSION 2.8)

set(target first_step)
PROJECT(${target})


if(CMAKE_SYSTEM MATCHES "Linux") 
    add_executable(${target} MACOSX_BUNDLE main.cpp)
else()
    add_executable(${target} main.cpp)
endif()
  
if (CMAKE_SYSTEM MATCHES "Linux")

target_link_libraries(${target} 
    dslFoundation
    tinyxml2
    poco_foundation
    pthread
    -lrt
)
elseif(CMAKE_SYSTEM MATCHES "Windows")
    target_link_libraries(${target} 
    dslFoundation
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



