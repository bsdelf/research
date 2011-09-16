cmake_minimum_required(VERSION 2.8)

project(HELLO)

# compile flags
set(CMAKE_C_FLAGS_RELEASE "$ENV{CFLAGS} -O2 -Wall")
set(CMAKE_C_FLAGS_DEBUG "$ENV{CFLAGS} -g -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O2 -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -g -Wall")

# options
#set(CMAKE_BUILD_TYPE "Release")
option(VERBOSE "More output information while running" OFF)
if (VERBOSE)
    add_definitions(-DVERBOSE)
endif (VERBOSE)

# include and link
include_directories(SYSTEM /usr/local/include)
link_directories(/usr/local/lib)
include_directories(BEFORE public)

# build output dir
set(OUTPUT_DIR ${HELLO_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

# targets
file(GLOB_RECURSE EXE_HELLO src/*.c)
add_executable(hello ${EXE_HELLO})

# messages
message(STATUS "CMake:\t" ${CMAKE_VERSION})
message(STATUS "System:\t" ${CMAKE_SYSTEM})
message(STATUS "Precessor:\t" ${CMAKE_SYSTEM_PROCESSOR})
message(STATUS "C Compiler:\t" ${CMAKE_C_COMPILER})
message(STATUS "CXX Compiler:\t" ${CMAKE_CXX_COMPILER})
message(STATUS "Build type:\t" ${CMAKE_BUILD_TYPE})
message(STATUS "Project root:\t" ${HELLO_SOURCE_DIR})
message(STATUS "Ouput root:\t" ${OUTPUT_DIR})
