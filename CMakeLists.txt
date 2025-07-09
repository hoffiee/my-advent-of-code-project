cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

project(aoc-cpp C CXX)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include(cpp)
include(helpers)
include(jupyter)
include(python)
include(go)
include(venv)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Make Clang Debug info compatible with GDB
set(CMAKE_CXX_FLAGS_DEBUG  "-gdwarf-4")

set(ASAN_OPTIONS abort_on_error=1:halt_on_error=1)
set(UBSAN_OPTIONS abort_on_error=1:halt_on_error=1)

add_compile_options(
    -Wdouble-promotion
    # -Wconversion  # external lib doesn't work with this.
    -Wnull-dereference
    -Wwrite-strings
    -Wformat=2
    -Wcast-align
    -Werror
    # -Wswitch-enum  # handles enums even when default is present

    $<$<CONFIG:Release>:-O3>
    $<$<CONFIG:Release>:-march=native>
    $<$<CONFIG:Release>:-flto>

    $<$<CONFIG:Debug>:-O0>
    $<$<CONFIG:Debug>:-Wall>
    $<$<CONFIG:Debug>:-Werror>
    $<$<CONFIG:Debug>:-pedantic>
    $<$<CONFIG:Debug>:-g3>
    $<$<CONFIG:Debug>:-ggdb>
    $<$<CONFIG:Debug>:-ggdb3>
    # $<$<CONFIG:Debug>:-fsanitize=undefined,address>
    # $<$<CONFIG:Debug>:-fsanitize-undefined-trap-on-error>
    # $<$<CONFIG:Debug>:-fno-omit-frame-pointer>
)

add_link_options(
    # $<$<CONFIG:Debug>:-fsanitize=undefined,address>
    # $<$<CONFIG:Debug>:-fsanitize-undefined-trap-on-error>
    # $<$<CONFIG:Debug>:-fno-omit-frame-pointer>
)

include(GoogleTest)
enable_testing()

add_subdirectory(libs)
add_subdirectory(tools)
add_subdirectory(src)

