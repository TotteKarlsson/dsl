cmake_minimum_required(VERSION 2.8)

set(target first_step)
PROJECT(${target})

add_executable(${target} main.cpp)
target_link_libraries(${target} 
dslFoundation
)

install(    
    TARGETS ${target} 	
    DESTINATION bin 
    COMPONENT compiled_examples
)



