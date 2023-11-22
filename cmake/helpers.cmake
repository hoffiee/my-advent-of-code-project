# TODO: Create macro for C++ targets
# TODO: Generally, reduce repetition
# TODO: Figure out if I can have declaration of variables as input?

macro(aoc_copy_input_file)
    file(COPY ${PROJECT_SOURCE_DIR}/aoc-puzzle-inputs/${ARGV0}/${ARGV1}.input
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
    )
endmacro()

# Usage: aoc_add_python_target(${TASk} ${AOC_DAY})
macro(aoc_add_python_target)
    add_custom_target(${ARGV0}
        COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/${ARGV1}.py
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
endmacro()


