cmake_minimum_required(VERSION 2.8)
set(target mtrand)

#===== General Installs
FILE (GLOB headers *.h)

if(${INSTALL_CXX_LIBS})

install (  
FILES ${headers}			 	
DESTINATION include/dsl/mtrand 
COMPONENT cxx_headers
)

endif()


