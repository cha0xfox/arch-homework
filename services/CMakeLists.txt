cmake_minimum_required(VERSION 3.2)

project(hl_server C CXX)

SET (MAIN_BINARY "hl_mai_lab_01")
SET (CATALOG_SERVICE "catalog_service")

find_package(OpenSSL)
find_package(Threads)
find_package(ZLIB)
find_package(Poco REQUIRED COMPONENTS Foundation Util Net XML JSON Crypto NetSSL)


if(NOT ${Poco_FOUND})
    message(FATAL_ERROR "Poco C++ Libraries not found.")
endif()

include_directories(${Poco_INCLUDE_DIRS})
include_directories("/usr/include/mysql")
include_directories("/usr/local/include/mysql")
link_directories("/usr/local/lib")

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${MAIN_BINARY} main.cpp 
                                 config/config.cpp 
                                 database/database.cpp
                                 database/user.cpp)


target_include_directories(${MAIN_BINARY} PRIVATE "${CMAKE_BINARY_DIR}")
target_compile_options(${MAIN_BINARY} PRIVATE -Wall -Wextra -pedantic -Werror )
set_target_properties(${MAIN_BINARY} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${MAIN_BINARY} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

target_link_libraries(${MAIN_BINARY} PRIVATE 
                             ${CMAKE_THREAD_LIBS_INIT} 
                             ${Poco_LIBRARIES}
                             "PocoData"
                             "PocoDataMySQL"
                             "mysqlclient"
                             ZLIB::ZLIB)

add_executable(${CATALOG_SERVICE} catalog_main.cpp)
target_include_directories(${CATALOG_SERVICE} PRIVATE "${CMAKE_BINARY_DIR}")
target_compile_options(${CATALOG_SERVICE} PRIVATE -Wall -Wextra -pedantic -Werror )
set_target_properties(${CATALOG_SERVICE} PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(${CATALOG_SERVICE} PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

target_link_libraries(${CATALOG_SERVICE} PRIVATE 
                             ${CMAKE_THREAD_LIBS_INIT} 
                             ${Poco_LIBRARIES}
                             "PocoData"
                             "PocoDataMySQL"
                             "mysqlclient"
                             ZLIB::ZLIB)


