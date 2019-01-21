set(target db_example_1)

include_directories(
${DSL_SOURCE_ROOT}/Common
${DSL_SOURCE_ROOT}/Math
${DSL_SOURCE_ROOT}/DataBase
)

link_directories(
${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
${LIBRARY_OUTPUT_PATH}
)

add_executable(${target} main.cpp)

if(${LINK_EXAMPLES_STATICALLY} STREQUAL "ON")
set(linkType "-static")
add_definitions(
-DPOCO_STATIC
-DDSL_STATIC
)
else()
set(linkType "")
endif()

target_link_libraries (${target} 
Moleculix${linkType}
SQLite-static
)

install(    
    TARGETS ${target} 	
    DESTINATION bin 
    COMPONENT compiled_examples
)

#install(
#FILES ${target}.cbproj main.cpp Readme.txt CMakeLists.txt 		
#DESTINATION Examples/DataBase/${target}	
#COMPONENT examples_source
#)

