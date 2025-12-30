find_package(Python3 REQUIRED)

set(TOOLS_DIR ${PROJECT_SOURCE_DIR}/tools)

include(CMakePrintHelpers)
cmake_print_variables(TOOLS_DIR)

function(aoc_add_python_target TARGET_NAME PYTHON_SOURCE)
    add_custom_target(${TARGET_NAME}-py
        COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/${PYTHON_SOURCE}
            ${CMAKE_CURRENT_BINARY_DIR}/solve.py
        COMMAND ${CMAKE_COMMAND} -E copy
            ${TOOLS_DIR}/aoc-bench/py_launcher
            ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}-py
        COMMENT "Copying python files for ${TARGET_NAME}-py"
        DEPENDS venv-update
    )

    add_custom_target(${TARGET_NAME}-py-run
        COMMAND ./${TARGET_NAME}-py
        DEPENDS ${TARGET_NAME}-py
    )
endfunction()

macro(aoc_add_python_test)
    add_custom_target(${ARGV0}-py-runtest
        COMMAND ${VENV_PYTEST} ${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS venv-update
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
endmacro()

# Python tooling
add_custom_target(lint-pylint
    COMMAND git ls-files src tools libs
        | grep -E "\\.py$$"
        | xargs ${PROJECT_BINARY_DIR}/venv/bin/pylint
    DEPENDS venv-update
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

add_custom_target(lint-mypy
    COMMAND git ls-files src tools libs
        | grep -E  '\\.py$$'
        | xargs -I{} ${PROJECT_BINARY_DIR}/venv/bin/mypy --explicit-package-bases --check-untyped-defs {}
        | grep -v "Success: no issues found in 1 source file"
    DEPENDS venv-update
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

add_custom_target(lint-py
    DEPENDS venv-update lint-pylint lint-mypy
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

add_custom_target(format-py
    COMMAND git ls-files src tools libs
        | grep -E  '\\.py$$'
        | xargs ${PROJECT_BINARY_DIR}/venv/bin/black
    DEPENDS venv-update
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)
