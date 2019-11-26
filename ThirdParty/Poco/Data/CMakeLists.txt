cmake_minimum_required(VERSION 2.6)
project(poco_data)


add_subdirectory(src)

OPTION(BUILD_POCO_MYSQL "Build MySQL Connector" OFF)
OPTION(BUILD_POCO_SQLITE "Build SQLite Connector" OFF)


if (BUILD_POCO_MYSQL)
add_subdirectory(MySQL)
endif()

if (BUILD_POCO_SQLITE)
add_subdirectory(SQLite)
endif()
