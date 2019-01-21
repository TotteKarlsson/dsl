cmake_minimum_required(VERSION 2.8)
set(target dslMath)

include_directories(
.
./..
${DSL_ROOT}/Common
${DSL_ROOT}/Math
${TP_INCLUDE}
)

set(src
#dslDihedralAngle
dslAxisSystem
dslEulerAngleTriplet
dslEulerMatrix
dslMathUtils
#dslMatrix
dslNumberBuilder
dslPoint
dslPointSet
dslRandom
dslVector3D
mtrand/mtrand
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Hu -Hi${CMAKE_SOURCE_DIR}/pch/dsl_pch.h -H=${CMAKE_SOURCE_DIR}/dsl.csm")


add_subdirectory(mtrand)

#===== Shared library
if(${BUILD_SHARED_LIBS})
    add_library(${target} SHARED
    ${src}
    )

    set_property(TARGET ${target}  
    PROPERTY COMPILE_DEFINITIONS 
             SHARED_MATH
             EXPORT_MATH
    )

    #link libraries
    target_link_libraries( ${target} 
    dslCommon
    #SQLite-static
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

