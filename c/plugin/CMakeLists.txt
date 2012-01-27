cmake_minimum_required(VERSION 2.8)

project(FOO)

# compile flags
set(CMAKE_C_FLAGS_RELEASE "$ENV{CFLAGS} -O2 -pipe -Wall")
set(CMAKE_C_FLAGS_DEBUG "$ENV{CFLAGS} -g -pipe -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O2 -pipe -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -g -pipe -Wall")
set(LINK_FLAGS "-Wl,-E")

# options
option(VERBOSE "More output information while running" OFF)
if (VERBOSE)
    add_definitions(-DVERBOSE)
endif (VERBOSE)

option(UseClang "Use Clang C colpiler" off)
if (UseClang)
    set(CMAKE_C_COMPILER "clang")
    set(CMAKE_CXX_COMPILER "clang++")
endif()

# include and link
include_directories(SYSTEM /usr/local/include)
link_directories(/usr/local/lib)
include_directories(BEFORE public)

# build output dir
set(OUTPUT_DIR ${FOO_SOURCE_DIR}/build/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR}/plugins)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

# targets
file(GLOB_RECURSE LIB_FOO src/plus/*.cpp)
add_library(plus SHARED ${LIB_FOO})

file(GLOB_RECURSE LIB_FOO src/mul/*.cpp)
add_library(mul SHARED ${LIB_FOO})

file(GLOB_RECURSE LIB_FOO src/forfoo/*.cpp)
add_library(forfoo SHARED ${LIB_FOO})

file(GLOB_RECURSE EXE_FOO src/core/*.cpp)
add_executable(opts ${EXE_FOO})

# messages
message(STATUS "CMake:\t" ${CMAKE_VERSION})
message(STATUS "System:\t" ${CMAKE_SYSTEM})
message(STATUS "Precessor:\t" ${CMAKE_SYSTEM_PROCESSOR})
message(STATUS "C Compiler:\t" ${CMAKE_C_COMPILER})
message(STATUS "CXX Compiler:\t" ${CMAKE_CXX_COMPILER})
message(STATUS "Build type:\t" ${CMAKE_BUILD_TYPE})
message(STATUS "Project root:\t" ${FOO_SOURCE_DIR})
message(STATUS "Ouput root:\t" ${OUTPUT_DIR})
