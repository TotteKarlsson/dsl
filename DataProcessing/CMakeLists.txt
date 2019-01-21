cmake_minimum_required(VERSION 2.8)
set(target mtkData)

include_directories(
${MOLECULIX_ROOT}
../Common
../Math
)

set(src 
mtkAxes
mtkData
mtkDataLink
mtkDataOptions
mtkDataProcessProjections
mtkDataProcessProperties
mtkDataProperties
mtkDataSliceInfo
mtkDataWriter
mtkPhasing
mtkProcessProperties
mtkShowDataPart
)

#===== Static library
if(${BUILD_STATIC_LIBS})
add_library(${target}-static STATIC
${src}
)

set_property(TARGET ${target}-static  
PROPERTY COMPILE_DEFINITIONS 
DSL_STATIC
)

    target_link_libraries(${target}-static 
        #poco_foundation-static
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

#===== Shared library
if(${BUILD_SHARED_LIBS})
add_library(${target} SHARED
${src}
)

set_property(TARGET ${target}  
PROPERTY COMPILE_DEFINITIONS 
EXPORT_DATA
)

#link libraries
target_link_libraries(${target} 
mtkCommon
mtkMath
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
        DESTINATION include/mtk 
        COMPONENT cxx_headers
    )
endif()

