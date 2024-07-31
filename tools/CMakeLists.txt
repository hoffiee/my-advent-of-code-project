add_custom_target(status
    COMMAND python3 event_status.py
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(used-file-extensions
    COMMAND find 20* -type f
        | grep -vE '\(CMakeLists.txt\)'
        | cut -d"." -f2 # cut at delimeter . and print second field
        | sort | uniq -c | sort -nr
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

# C++ tooling
add_custom_target(lint-cpp
    COMMAND xargs cppcheck --project=compile_commands.json --suppressions-list=cppcheck_suppressions.txt . 1> /dev/null
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

# add_custom_target(lint-mypy
#     COMMAND find . -name '*.py' | grep -v build | xargs ${PROJECT_BINARY_DIR}/venv/bin/mypy --strict
#     WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
# )

add_custom_target(lint-mypy
    COMMAND git ls-files .
        | grep -E  '\\.py$$'
        | xargs ${PROJECT_BINARY_DIR}/venv/bin/mypy
    # COMMAND find . -name '*.py' | grep -v build | xargs ${PROJECT_BINARY_DIR}/venv/bin/mypy --strict --ignore-missing-imports
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

add_custom_target(lint-py
    DEPENDS lint-pylint lint-mypy
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

add_custom_target(format-py
    COMMAND git ls-files .
        | grep -E  '\\.py$$'
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
