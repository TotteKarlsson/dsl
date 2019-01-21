cmake_minimum_required(VERSION 2.8)

set(target timer)
PROJECT(${target})

if(CMAKE_SYSTEM MATCHES "Linux") 
    add_executable(${target} MACOSX_BUNDLE main.cpp)
else()
    add_executable(${target} main.cpp)
endif()
  
target_link_libraries(${target} 
dslFoundation
)

if(CMAKE_SYSTEM MATCHES "Linux") 
    set (CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
endif()

install(    
    TARGETS ${target} 	
    DESTINATION bin 
    COMPONENT compiled_examples
)



