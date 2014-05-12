cmake_minimum_required(VERSION 2.6)

project(markit CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(CMAKE_CXX_FLAGS                "-Wall -Werror")
set(CMAKE_CXX_FLAGS_DEBUG          "-O0 -g")
set(CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE        "-Ofast -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

include(FindCXX11)

find_package(LibNewt REQUIRED)

aux_source_directory(. SRC_LIST)
add_executable(markit ${SRC_LIST})
set(CMAKE_BUILD_TYPE Release)

include_directories(${LibNewt_INCLUDE_DIRS})
target_link_libraries (markit ${LibNewt_LIBRARIES})