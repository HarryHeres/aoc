cmake_minimum_required(VERSION 3.30)

project(aoc)

file(GLOB_RECURSE sources src/*.c)

set(OUTPUT_BINARY main)
set(CMAKE_C_COMPILER "clang")
set(CMAKE_OUTPUT_DIR ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/../libs/include)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_OUTPUT_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c17 -g -Wall -Wextra -Wfloat-conversion -pedantic")

include_directories(${CMAKE_INCLUDE_DIR})
add_executable(${OUTPUT_BINARY} ${sources})
target_link_libraries(${OUTPUT_BINARY} m)
