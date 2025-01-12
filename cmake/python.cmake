# Usage: aoc_add_python_target(${TASK} ${AOC_DAY})
macro(aoc_add_python_target)
    add_custom_target(${ARGV0}
        COMMAND ${CMAKE_COMMAND} -E env PYTHONPATH=${PROJECT_SOURCE_DIR}:$ENV{PYTHONPATH}
        ${VENV_PYTHON} ${CMAKE_CURRENT_SOURCE_DIR}/${ARGV1}
        DEPENDS venv-update
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
endmacro()

macro(aoc_add_python_test)
    add_custom_target(${ARGV0}
        COMMAND ${VENV_PYTEST} ${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS venv-update
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
endmacro()

macro(aoc_add_python_benchmark)
    add_custom_target(${ARGV0}
        COMMAND hyperfine ${VENV_PYTHON} ${CMAKE_CURRENT_SOURCE_DIR}/${ARGV1}
        DEPENDS venv-update
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
endmacro()

# Python tooling
add_custom_target(lint-pylint
    COMMAND find . -name '*.py' | grep -v build | xargs ${PROJECT_BINARY_DIR}/venv/bin/pylint
    DEPENDS venv-update
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

# add_custom_target(lint-mypy
#     COMMAND find . -name '*.py' | grep -v build | xargs ${PROJECT_BINARY_DIR}/venv/bin/mypy --strict
#     WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
# )

add_custom_target(lint-mypy
    COMMAND git ls-files .
        | grep -E  '\\.py$$'
        | xargs -I{} ${PROJECT_BINARY_DIR}/venv/bin/mypy --explicit-package-bases --check-untyped-defs {}
        | grep -v "Success: no issues found in 1 source file"
    # COMMAND find . -name '*.py' | grep -v build | xargs ${PROJECT_BINARY_DIR}/venv/bin/mypy --strict --ignore-missing-imports
    DEPENDS venv-update
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

add_custom_target(lint-py
    DEPENDS venv-update lint-pylint lint-mypy
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

add_custom_target(format-py
    COMMAND git ls-files .
        | grep -E  '\\.py$$'
        | xargs ${PROJECT_BINARY_DIR}/venv/bin/black
    DEPENDS venv-update
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)
