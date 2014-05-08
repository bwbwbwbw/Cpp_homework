cmake_minimum_required(VERSION 2.6)
project(markit CXX)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

aux_source_directory(. SRC_LIST)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_executable(markit ${SRC_LIST})
set(CMAKE_BUILD_TYPE Release)

find_package(LibNewt REQUIRED)
include_directories(${LibNewt_INCLUDE_DIRS})
target_link_libraries (markit ${LibNewt_LIBRARIES})