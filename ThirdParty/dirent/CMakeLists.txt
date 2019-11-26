cmake_minimum_required(VERSION 2.8)
set(target dirent)

#===== General Installs
FILE (GLOB headers *.h)

install (  
FILES ${headers}			 	
DESTINATION include/dirent 
COMPONENT cxx_headers
)


