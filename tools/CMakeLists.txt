add_custom_target(status
    COMMAND python3 event_status.py
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

# TODO: move these to cmake directory?
add_custom_target(cppcheck
    COMMAND find . -name '*.cpp' -o -name '*.h'
        | grep -v ccls-cache
        | xargs cppcheck --project=compile_commands.json 1> /dev/null
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

add_custom_target(py-check
    COMMAND find . -name '*.py'
        | xargs mypy --strict --ignore-missing-imports ||
     find . -name '*.py'
        | xargs pylint
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

add_custom_target(cpp-format
    COMMAND git ls-files .
        | grep -E  '\\.cpp$$|\\.h$$'
        | xargs clang-format -Werror -i -style=file
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

add_custom_target(py-format
    COMMAND find . -name '*.py'
        | xargs black
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

add_custom_target(all-runtest
    COMMAND ctest --output-on-failure -j2
    DEPENDS all
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
)

add_subdirectory(python-example)
