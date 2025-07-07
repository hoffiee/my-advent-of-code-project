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

set(CMAKE_BUILD_TYPE Debug)

set(ASAN_OPTIONS abort_on_error=1:halt_on_error=1)
set(UBSAN_OPTIONS abort_on_error=1:halt_on_error=1)

# https://stackoverflow.com/questions/59107988/correct-way-to-handle-compiler-flags-when-using-cmake
add_compile_options(
    -Wall -Werror -pedantic
    -g3 -ggdb
    # trying these out for a bit
    -Wdouble-promotion
    # -Wconversion  # external lib doesn't work with this.
    -Wnull-dereference
    -Wwrite-strings
    -Wformat=2
    -Wcast-align
    # -Wswitch-enum  # handles enums even when default is present
    $<$<CONFIG:RELEASE>:-Ofast>
    $<$<CONFIG:DEBUG>:-O0>
    $<$<CONFIG:DEBUG>:-ggdb3>
    # $<$<CONFIG:DEBUG>:-fsanitize=undefined,address>
    # $<$<CONFIG:DEBUG>:-fsanitize-undefined-trap-on-error>
)
# add_link_options(-fsanitize=undefined,address)
# execute with gdb and ASAN_OPTIONS=abort_on_error=1, see
# https://www.reddit.com/r/C_Programming/comments/ycaexu/easy_c_debugging/?utm_name=androidcss

# https://stackoverflow.com/questions/50861636/using-google-tests-with-cmake-ctest-with-the-new-command-gtest-discover-tests
include(GoogleTest)
enable_testing()
# include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

add_subdirectory(libs)
add_subdirectory(tools)
add_subdirectory(src)

