set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Make Clang Debug info compatible with GDB
set(CMAKE_CXX_FLAGS_DEBUG  "-gdwarf-4")

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
    $<$<CONFIG:Debug>:-fsanitize=undefined,address>
    # $<$<CONFIG:Debug>:-fsanitize-undefined-trap-on-error>
    # $<$<CONFIG:Debug>:-fno-omit-frame-pointer>
)

add_link_options(
    $<$<CONFIG:Debug>:-fsanitize=undefined,address>
    # $<$<CONFIG:Debug>:-fsanitize-undefined-trap-on-error>
    # $<$<CONFIG:Debug>:-fno-omit-frame-pointer>
)

set(ASAN_OPTIONS abort_on_error=1:halt_on_error=1)
set(UBSAN_OPTIONS abort_on_error=1:halt_on_error=1)


add_custom_target(lint-cpp
    COMMAND xargs cppcheck --project=compile_commands.json --suppressions-list=cppcheck_suppressions.txt . 1> /dev/null
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

add_custom_target(format-cpp
    COMMAND git ls-files src libs tools
        | grep -E  '\\.cpp$$|\\.h$$'
        | xargs clang-format -Werror -i -style=file
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)
