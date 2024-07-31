# Usage: aoc_add_python_target(${TASK} ${AOC_DAY})
macro(aoc_add_python_target)
    add_custom_target(${ARGV0}
        COMMAND ${VENV_PYTHON} ${CMAKE_CURRENT_SOURCE_DIR}/${ARGV1}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
endmacro()

macro(aoc_add_python_test)
    add_custom_target(${ARGV0}
        COMMAND ${VENV_PYTEST} ${CMAKE_CURRENT_SOURCE_DIR}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
endmacro()

macro(aoc_add_python_benchmark)
    add_custom_target(${ARGV0}
        COMMAND hyperfine ${VENV_PYTHON} ${CMAKE_CURRENT_SOURCE_DIR}/${ARGV1}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
endmacro()

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
