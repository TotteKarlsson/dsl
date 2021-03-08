cmake_minimum_required(VERSION 2.8)

set(target timer)
PROJECT(${target})

 add_executable(${target} main.cpp)
  
target_link_libraries(${target} 
dslFoundation
poco_foundation
)

install(    
    TARGETS ${target} 	
    DESTINATION bin 
    COMPONENT compiled_examples
)



