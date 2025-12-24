cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(aoc-cpp C CXX)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(cpp)
include(helpers)
include(jupyter)
include(python)
include(go)
include(rust)
include(venv)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(GoogleTest)
enable_testing()

add_subdirectory(libs)
add_subdirectory(tools)
add_subdirectory(src)

