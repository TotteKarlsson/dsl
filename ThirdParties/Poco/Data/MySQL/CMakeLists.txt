

#add_definitions(-DTHREADSAFE -DNO_TCL)


set(MYSQL_C_HEADER_FOLDER CACHE PATH "Directory containing mysql.h")
add_subdirectory(src)

