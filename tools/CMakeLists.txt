add_custom_target(status
    COMMAND python3 event_status.py
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

# C++ tooling
add_custom_target(check-cpp
    COMMAND find . -name '*.cpp' -o -name '*.h'
        | grep -v ccls-cache
        | xargs cppcheck --project=compile_commands.json 1> /dev/null
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

add_custom_target(format-cpp
    COMMAND git ls-files .
        | grep -E  '\\.cpp$$|\\.h$$'
        | xargs clang-format -Werror -i -style=file
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

# Python tooling
add_custom_target(lint-pylint
    COMMAND find . -name '*.py' | grep -v build | xargs ${PROJECT_BINARY_DIR}/venv/bin/pylint
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

add_custom_target(lint-mypy
    COMMAND find . -name '*.py' | grep -v build | xargs ${PROJECT_BINARY_DIR}/venv/bin/mypy --strict --ignore-missing-imports
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

add_custom_target(lint-py
    DEPENDS lint-pylint lint-mypy
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

add_custom_target(format-py
    COMMAND find . -name '*.py'
        | xargs ${PROJECT_BINARY_DIR}/venv/bin/black
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

# all
add_custom_target(all-runtest
    COMMAND ctest --output-on-failure -j2
    DEPENDS all
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
)

add_custom_target(format
    DEPENDS format-cpp format-py
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

# Add examples etc
add_subdirectory(python-example)
