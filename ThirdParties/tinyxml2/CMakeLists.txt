cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
cmake_policy(VERSION 2.6)
set(target tinyxml2)

project(tinyxml2)
set(GENERIC_LIB_VERSION "6.2.0")
set(GENERIC_LIB_SOVERSION "6")

################################
# Add definitions

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DTINYXML2_DEBUG")

################################
# Add targets
# By Default shared libray is being built
# To build static libs also - Do cmake . -DBUILD_STATIC_LIBS:BOOL=ON
# User can choose not to build shared library by using cmake -DBUILD_SHARED_LIBS:BOOL=OFF
# To build only static libs use cmake . -DBUILD_SHARED_LIBS:BOOL=OFF -DBUILD_STATIC_LIBS:BOOL=ON
# To build the tests, use cmake . -DBUILD_TESTS:BOOL=ON
# To disable the building of the tests, use cmake . -DBUILD_TESTS:BOOL=OFF
option(BUILD_SHARED_LIBS "build as shared library" ON)
option(BUILD_STATIC_LIBS "build as static library" OFF)
option(BUILD_TESTS "build xmltest (deprecated: Use BUILD_TESTING)" OFF)


if(BUILD_SHARED_LIBS)
    add_library(tinyxml2 SHARED tinyxml2.cpp tinyxml2.h)

    set_target_properties(tinyxml2 PROPERTIES
        COMPILE_DEFINITIONS "TINYXML2_EXPORT"
        VERSION "${GENERIC_LIB_VERSION}"
        SOVERSION "${GENERIC_LIB_SOVERSION}"
        OUTPUT_NAME ${target}${LIBRARY_POSTFIX}
        )


    if(MSVC)
      target_compile_definitions(tinyxml2 PUBLIC -D_CRT_SECURE_NO_WARNINGS)
    endif(MSVC)

    install(TARGETS ${target}
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib
            )
endif()

if(BUILD_STATIC_LIBS)
    add_library(tinyxml2_static STATIC tinyxml2.cpp tinyxml2.h)
    set_target_properties(tinyxml2_static PROPERTIES
            VERSION "${GENERIC_LIB_VERSION}"
            SOVERSION "${GENERIC_LIB_SOVERSION}")

    target_include_directories(tinyxml2_static PUBLIC 
                          $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
                          $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>)

    if(MSVC)
      target_compile_definitions(tinyxml2_static PUBLIC -D_CRT_SECURE_NO_WARNINGS)
    endif(MSVC)
    install(TARGETS ${target}_static
            RUNTIME DESTINATION  bin
            LIBRARY DESTINATION  lib
            ARCHIVE DESTINATION  lib 
            )
endif()

if(BUILD_STATIC_LIBS OR BUILD_SHARED_LIBS)
    install(FILES tinyxml2.h DESTINATION include/tinyxml2)
endif()

