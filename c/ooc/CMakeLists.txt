cmake_minimum_required(VERSION 2.8)

project(FOO)

set(IS_FREEBSD "${CMAKE_SYSTEM}" MATCHES "FreeBSD")
set(IS_LINUX "${CMAKE_SYSTEM}" MATCHES "Linux")

# compile flags
set(CMAKE_C_FLAGS_RELEASE "$ENV{CFLAGS} -O2 -pipe -fno-strict-aliasing -Wall")
set(CMAKE_C_FLAGS_DEBUG "$ENV{CFLAGS} -g -pipe -fno-strict-aliasing -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O2 -pipe -fno-strict-aliasing -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -g -pipe -fno-strict-aliasing -Wall")

# options
option(UseClang "Use Clang C colpiler" off)
if (UseClang)
    set(CMAKE_C_COMPILER "clang")
    set(CMAKE_CXX_COMPILER "clang++")
endif()

option(EnableVerbose "More output information while running" OFF)
if (EnableVerbose)
    add_definitions(-DVERBOSE)
endif()

# include and link
include_directories(SYSTEM /usr/local/include)
link_directories(/usr/local/lib)
#include_directories(BEFORE public)

# build output dir
set(OUTPUT_DIR ${FOO_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

# exe
aux_source_directory(src/ EXE_FOO)
add_executable(ooc ${EXE_FOO})

# messages
message(STATUS "CMake:\t" ${CMAKE_VERSION})
message(STATUS "System:\t" ${CMAKE_SYSTEM})
message(STATUS "Processor:\t" ${CMAKE_SYSTEM_PROCESSOR})
message(STATUS "C Compiler:\t" ${CMAKE_C_COMPILER})
message(STATUS "CXX Compiler:\t" ${CMAKE_CXX_COMPILER})
message(STATUS "Build type:\t" ${CMAKE_BUILD_TYPE})
message(STATUS "Project root:\t" ${FOO_SOURCE_DIR})
message(STATUS "Ouput root:\t" ${OUTPUT_DIR})
