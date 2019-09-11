cmake_minimum_required(VERSION 2.8)
set(target dslFoundation)

include_directories(
    ./../
    ./../Common
    ./../Math
    ./../Plugins
    ${CMAKE_SOURCE_DIR}/ThirdParties/Poco/Foundation/include
    ${CMAKE_SOURCE_DIR}/ThirdParties
    ${TP_INCLUDE}
)

message("Link folder:" ${CMAKE_INSTALL_PREFIX}/lib)
link_directories(${CMAKE_BINARY_DIR}/lib)

set(src
../Common/dslBaseProperty
../Common/dslClassProperty
../Common/dslColor
../Common/dslCommand
../Common/dslCommon
../Common/dslCompareStrings
../Common/dslConstants
../Common/dslException
../Common/dslFileSet
../Common/dslFileUtils
../Common/dslGetOptions
../Common/dslIniFile
../Common/dslIniFileProperties
../Common/dslIniKey
../Common/dslIniSection
../Common/dslLogFile
../Common/dslLoggerUtils
../Common/dslLogging
../Common/dslLogLevel
../Common/dslLogOutput
../Common/dslMessageContainer
../Common/dslMessageProcessor
../Common/dslObject
../Common/dslObserver
../Common/dslProject
../Common/dslProjects
../Common/dslProperties
../Common/dslPropertiesContainer
../Common/dslRange
../Common/dslStopWatch
../Common/dslStreamCenteredOutput
../Common/dslStringList
../Common/dslStringUtils
../Common/dslStringBuilder
../Common/dslSubject
../Common/dslThread
../Common/dslTimer
../Common/dslTypeInfo
../Common/dslToggler
../Common/dslUtils
../Common/dslVersion
../Common/dslWin32Utils
../Common/dslXMLUtils

../Plugins/dslPlugin
../Plugins/dslPluginManager
../Plugins/dslPluginMetaData
../Plugins/dslPluginWithEvents

#../IPC/dslIPCData
#../IPC/dslIPCMessage
#../IPC/dslIPCMessageBuilder
#../IPC/dslIPCMessageEnums
#../IPC/dslIPCMessageProcessor
#../IPC/dslIPCReceiver
#../IPC/dslIPCServer
#../IPC/dslSocket
#../IPC/dslSocketClient
#../IPC/dslSocketReceiver
#../IPC/dslSocketServer
#../IPC/dslSocketWorker
#../IPC/dslToggleSocketConnectionThread

../Math/dslDihedralAngle
../Math/dslAxisSystem
../Math/dslEulerAngleTriplet
../Math/dslEulerMatrix
../Math/dslMathUtils
#../Math/#dslMatrix
#../Math/dslNumberBuilder
../Math/dslPoint
../Math/dslPointSet
../Math/dslRandom
../Math/dslVector3D
../Math/mtrand/mtrand

#../DataBase/dslSQLite
#../DataBase/dslSQLiteBuffer
#../DataBase/dslSQLiteQuery
#../DataBase/dslSQLiteTable
#../DataBase/dslSQLiteStatement
#../DataBase/dslSQLiteException
)
if (CMAKE_SYSTEM MATCHES "Windows")
    set(src ${src} )
endif()

#===== Shared library
if(${BUILD_SHARED_LIBS})
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Hi${CMAKE_SOURCE_DIR}/pch/dsl_pch.h -Hh=${CMAKE_SOURCE_DIR}/pch/dsl_pch.h -H=${CMAKE_SOURCE_DIR}/pch/dsl_pch.cmake -H")

    add_library(${target} SHARED
    ${src}
    )
    
    set_target_properties(${target}  PROPERTIES 
        OUTPUT_NAME ${target}${LIBRARY_POSTFIX}
    )
    target_compile_definitions(${target} PRIVATE EXPORT_COMMON EXPORT_PLUGINS EXPORT_IPC EXPORT_MATH EXPORT_DATABASE)
    #link libraries
    if (CMAKE_SYSTEM MATCHES "Linux")
            target_link_libraries(${target} 
                tinyxml2
                poco_foundation
                pthread
                -lrt
    #            sqlite
            )
    endif()  

    if (CMAKE_SYSTEM MATCHES "Windows")
            target_link_libraries(${target} 
            #${CMAKE_INSTALL_PREFIX}/lib/sqlite.lib
            ${CMAKE_INSTALL_PREFIX}/lib/tinyxml2${LIBRARY_POSTFIX}.lib
            ${CMAKE_INSTALL_PREFIX}/lib/poco_foundation${LIBRARY_POSTFIX}.lib
            Shell32.lib
        )
    endif()

    if(${INSTALL_CXX_LIBS})
        install(    
        TARGETS ${target} 
        RUNTIME DESTINATION bin COMPONENT core
        LIBRARY DESTINATION lib COMPONENT core
        ARCHIVE DESTINATION lib COMPONENT core
        )            
    endif()

    #set(pcHeader "${CMAKE_SOURCE_DIR}/pch/dsl_pch.h")
endif() #Shared lib

#===== General Installs
if(${INSTALL_CXX_LIBS})

    FILE (GLOB common_headers ./../Common/*.h)
    FILE (GLOB math_headers ./../Math/*.h)
    FILE (GLOB ipc_headers ./../IPC/*.h)
    FILE (GLOB plugins_headers ./../Plugins/*.h)
    FILE (GLOB db_headers ./../DataBase/*.h)
    install (   
        FILES ${common_headers} ${math_headers} ${ipc_headers} ${db_headers}
        ${plugins_headers}
        DESTINATION include/dsl 
        COMPONENT cxx_headers
    )

    if(${BORLAND})

        install(FILES
            ${PROJECT_BINARY_DIR}/bin/${target}.tds
            DESTINATION bin
            COMPONENT debug
        )
    endif()        

endif()

