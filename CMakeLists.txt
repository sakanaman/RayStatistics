cmake_minimum_required(VERSION 3.2)

project(sampler_test)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall")

#common
include_directories(common)
file(GLOB COMMON_SOURCES
    common/*)
add_library(common ${COMMON_SOURCES})

#pybind11
add_subdirectory(extern/pybind11)

#src
include_directories(src)
add_subdirectory(src)

#projects
add_subdirectory(projects)