

# Usage: aoc_add_python_target(${TASK} ${AOC_DAY})
macro(aoc_add_go_target)
    add_custom_target(${ARGV0}
        COMMAND go run ${CMAKE_CURRENT_SOURCE_DIR}/${ARGV1}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
endmacro()

