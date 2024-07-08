# TODO: Create macro for C++ targets
# TODO: Generally, reduce repetition
# TODO: Figure out if I can have declaration of variables as input?

macro(aoc_copy_input_file)
    file(COPY ${PROJECT_SOURCE_DIR}/aoc-puzzle-inputs/${ARGV0}/${ARGV1}.input
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
    )
endmacro()

# Usage: aoc_add_python_target(${TASK} ${AOC_DAY})
# macro(aoc_add_python_target)
#     add_custom_target(${ARGV0}-py
#         COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/${ARGV1}.py
#         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#     )
# endmacro()


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
