CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
project(poco_net_src)
set(target poco_net) 

# Option that allows users to build static and/or shared libraries
# ----------------------------------------------------------------
OPTION(POCO_BUILD_STATIC_LIBS "Build static libraries" OFF)
OPTION(POCO_BUILD_SHARED_LIBS "Build shared libraries" ON)

set(sources 
AbstractHTTPRequestHandler
DNS
DatagramSocket
DatagramSocketImpl
DialogSocket
FTPClientSession
FTPStreamFactory
FilePartSource
HTMLForm
HTTPAuthenticationParams
HTTPBasicCredentials
HTTPBufferAllocator
HTTPChunkedStream
HTTPClientSession
HTTPCookie
HTTPCredentials
HTTPDigestCredentials
HTTPFixedLengthStream
HTTPHeaderStream
HTTPIOStream
HTTPMessage
HTTPRequest
HTTPRequestHandler
#HTTPRequestHandlerFactory
HTTPResponse
#HTTPServer
#HTTPServerConnection
#HTTPServerConnectionFactory
#HTTPServerParams
#HTTPServerRequest
#HTTPServerRequestImpl
#HTTPServerResponse
#HTTPServerResponseImpl
#HTTPServerSession
HTTPSession
HTTPSessionFactory
HTTPSessionInstantiator
HTTPStream
HTTPStreamFactory
HostEntry
#ICMPClient
#ICMPEventArgs
#ICMPPacket
#ICMPPacketImpl
#ICMPSocket
#ICMPSocketImpl
#ICMPv4PacketImpl
IPAddress
MailMessage
MailRecipient
MailStream
MediaType
MessageHeader
MulticastSocket
MultipartReader
MultipartWriter
NameValueCollection
NetException
NetworkInterface
NullPartHandler
POP3ClientSession
PartHandler
PartSource
QuotedPrintableDecoder
QuotedPrintableEncoder
RawSocket
RawSocketImpl
RemoteSyslogChannel
RemoteSyslogListener
SMTPClientSession
ServerSocket
ServerSocketImpl
Socket
SocketAddress
SocketImpl
SocketNotification
SocketNotifier
SocketReactor
SocketStream
StreamSocket
StreamSocketImpl
StringPartSource
TCPServer
TCPServerConnection
TCPServerConnectionFactory
TCPServerDispatcher
TCPServerParams
#WebSocket
#WebSocketImpl
)

include_directories(
../../Foundation/include
../../Net/include
)

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


if(BUILD_SHARED_LIBS)
    add_library(${target} SHARED ${sources})
    target_link_libraries(${target} poco_foundation)

    if(WIN32)
        set_property(TARGET ${target}  
                     PROPERTY  COMPILE_DEFINITIONS 
                     WIN32
                     POCO_DLL
                     Net_EXPORTS
                     ) 
        message("Building Poco Shared Library on Windows")
    endif()

    target_link_libraries(${target} poco_foundation iphlpapi)

    install(TARGETS ${target} 
        RUNTIME DESTINATION bin 
        LIBRARY DESTINATION lib 
        ARCHIVE DESTINATION lib)
endif()


#INSTALLING ======================
set(poco_net_include_folder ${CMAKE_CURRENT_SOURCE_FOLDER}../include/Poco/Net)

FILE (GLOB net_headers ${poco_net_include_folder}/*.h)

#Install required files
install(FILES ${net_headers} DESTINATION include/Poco/Net)


install(TARGETS ${target} 
LIBRARY DESTINATION lib 
ARCHIVE DESTINATION lib
)

