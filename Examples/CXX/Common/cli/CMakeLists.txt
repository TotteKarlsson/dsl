cmake_minimum_required(VERSION 2.8)
set(target rr)

add_executable(${target} 
main.cpp 
Args.cpp
)

add_definitions(
-DPOCO_STATIC
-DSTATIC_PUGI
-DLIBSBML_STATIC 
#-DSTATIC_RR
-DSTATIC_LIBSTRUCT
-DLIBLAX_STATIC  
-DSTATIC_NLEQ
)

if(WIN32)
add_definitions(
-DWIN32
)

target_link_libraries (${target} 
#roadrunner-static
roadrunner
)
endif()

#Not sure why linux linker need all libraries at linktime?? All symbols 'should' be in roadrunner-static
if(UNIX)
target_link_libraries (${target} 
roadrunner-static
nleq-static.a
rr-libstruct-static
lapack
blas
f2c
sbml-static.a
xml2
sundials_nvecserial.a
sundials_cvode.a
pthread
poco_foundation-static.a
dl
)
endif()


install (TARGETS ${target} 		
DESTINATION bin 
COMPONENT apps
)
