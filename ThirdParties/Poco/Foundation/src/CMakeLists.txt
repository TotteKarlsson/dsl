CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
project(poco_foundation_src)

# Option that allows users to build static and/or shared libraries
# ----------------------------------------------------------------
set(target poco_foundation) 

set(poco_include_folder ${CMAKE_CURRENT_SOURCE_FOLDER}../include)
include_directories( ${poco_include_folder})

set(sources 
ASCIIEncoding
Ascii
AtomicCounter
AbstractObserver
ActiveDispatcher
ArchiveStrategy
AsyncChannel
Base64Decoder
Base64Encoder
BinaryReader
BinaryWriter
Bugcheck
ByteOrder
Channel
Checksum
Condition
Configurable
ConsoleChannel
CountingStream
DateTime
DateTimeFormat
DateTimeFormatter
DateTimeParser
Debugger
DeflatingStream
DigestEngine
DigestStream
DirectoryIterator
Environment
ErrorHandler
Event
EventArgs
Exception
FPEnvironment
File
#FIFOBufferStream
FileChannel
FileStream
FileStreamFactory
Format
Formatter
FormattingChannel
Glob
Hash
HashStatistic
HexBinaryDecoder
HexBinaryEncoder
#InflatingStream
Latin1Encoding
Latin2Encoding
Latin9Encoding
LineEndingConverter
LocalDateTime
LogFile
LogStream
Logger
LoggingFactory
LoggingRegistry
MD4Engine
MD5Engine
Manifest
MemoryPool
MemoryStream
Message
Mutex
NamedEvent
NamedMutex
NestedDiagnosticContext
Notification
NotificationCenter
NotificationQueue
TimedNotificationQueue
PriorityNotificationQueue
NullChannel
NullStream
NumberFormatter
NumberParser
Path
PatternFormatter
Pipe
PipeImpl
PipeStream
Process
PurgeStrategy
RWLock
Random
RandomStream
RefCountedObject
RegularExpression
RotateStrategy
Runnable
SHA1Engine
Semaphore
SharedLibrary
SharedMemory
SignalHandler
SimpleFileChannel
SplitterChannel
Stopwatch
StreamChannel
StreamConverter
StreamCopier
StreamTokenizer
String
StringTokenizer
SynchronizedObject
#SyslogChannel
Task
TaskManager
TaskNotification
TeeStream
TemporaryFile
TextConverter
TextEncoding
TextIterator
TextBufferIterator
Thread
ThreadTarget
ThreadLocal
ThreadPool
Timer
Timespan
Timestamp
Timezone
Token
URI
URIStreamFactory
URIStreamOpener
Unicode
UnicodeConverter
UTF8Encoding
UTF16Encoding
UTF32Encoding
Windows1250Encoding
Windows1251Encoding
Windows1252Encoding
#WindowsConsoleChannel
#EventLogChannel
TextEncoding
Environment
UUID
UUIDGenerator
Void
deflate
zutil
adler32
crc32
trees
pcre_chartables.c
pcre_compile.c
pcre_exec.c
pcre_fullinfo.c
pcre_globals.c
pcre_maketables.c
pcre_newline.c
pcre_ord2utf8.c
pcre_study.c
pcre_tables.c
pcre_try_flipped.c
pcre_ucd.c
pcre_valid_utf8.c
pcre_xclass.c
Var
VarHolder
NumericString
bignum-dtoa.cc
fixed-dtoa.cc
fast-dtoa.cc
bignum.cc
cached-powers.cc
diy-fp.cc
strtod.cc
)

if (CMAKE_SYSTEM MATCHES "Windows")
    set(sources ${sources} 
    WindowsConsoleChannel
    EventLogChannel
    )
endif()

if (CMAKE_SYSTEM MATCHES "Linux")
    set(sources ${sources} SyslogChannel )
endif()

if(${BORLAND})
add_definitions(
             -w-8012                     #Comparing signed /unsigned
             -w-8057                     #Parameter never used
             -w-8004                     #'var' is assigned a value that is never used
             -w-8123                     #Path not found
             -w-8066                     #Unreachable code
             -w-8104                     #Local static with constructor...
             -w-8008                     #Condition is always false..
             -w-8022 
        )
add_definitions( -D_WIN32)
add_definitions( -D_THREADSAFE)
add_definitions( -D_NOTCL)
endif()

#if(CMAKE_SYSTEM MATCHES "Windows")
# add_definitions( -DPOCO_OS_FAMILY_WINDOWS)
# set(SYSLIBS iphlpapi gdi32 odbc32)
# 
# if (CMAKE_C_COMPILER_ID MATCHES "MSVC")
#        message(STATUS "XXX: MS Visual Compiler detected")
# endif (CMAKE_C_COMPILER_ID MATCHES "MSVC")
#
#endif(CMAKE_SYSTEM MATCHES "Windows")

if (CMAKE_SYSTEM MATCHES "Linux")
  add_definitions( -DPOCO_OS_FAMILY_UNIX )
  # Standard 'must be' defines
  add_definitions( -D_XOPEN_SOURCE=500 -D_REENTRANT -D_THREAD_SAFE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64)
  set(SYSLIBS  pthread dl rta)
  message("Compiling on LINUX")
endif(CMAKE_SYSTEM MATCHES "Linux")

if(${MSVC})
#set(....
endif()


if(BUILD_SHARED_LIBS)
    #Then the static version
    add_library(${target} SHARED ${sources})
    set_property(TARGET ${target}  
                 PROPERTY  COMPILE_DEFINITIONS 
                 Foundation_EXPORTS
                 )

    if(WIN32)
        set_property(TARGET ${target}  
                     PROPERTY  COMPILE_DEFINITIONS 
                     Foundation_EXPORTS
                     POCO_DLL
                     ) 
        message("Building Poco Shared Library on Windows")
    target_link_libraries(${target} "iphlpapi")
    set_target_properties(${target} PROPERTIES OUTPUT_NAME ${target}${LIBRARY_POSTFIX})
    endif()
    install(TARGETS ${target} 
        RUNTIME DESTINATION bin 
        LIBRARY DESTINATION lib 
        ARCHIVE DESTINATION lib)
endif()

#if(BUILD_STATIC_LIBS)
#    #Then the static version
#    add_library(${target}-static STATIC ${sources})
#    set_property(TARGET ${target}-static  
#                 PROPERTY  COMPILE_DEFINITIONS 
#                           POCO_STATIC
#                           PCRE_STATIC
#                 ) 
#
#    if(WIN32)
#        set_property(TARGET ${target}-static  
#                        PROPERTY  COMPILE_DEFINITIONS 
#                        WIN32
#                 ) 
#    endif()
#    install(TARGETS ${target}-static 
#        LIBRARY DESTINATION lib 
#        ARCHIVE DESTINATION lib)
#endif()

#Install Headers ======================
if(BUILD_STATIC_LIBS OR BUILD_SHARED_LIBS)

    FILE (GLOB headers ${poco_include_folder}/Poco/*.h)
    FILE (GLOB dheaders ${poco_include_folder}/Poco/Dynamic/*.h)
    install(FILES ${headers} DESTINATION include/Poco)
    install(FILES ${dheaders} DESTINATION include/Poco/Dynamic)
endif()

