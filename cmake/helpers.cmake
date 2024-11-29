macro(aoc_copy_input_file)
    file(COPY ${PROJECT_SOURCE_DIR}/aoc-puzzle-inputs/${ARGV0}/${ARGV1}.input
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
    )
endmacro()


macro(aoc_set_task_variables)
    get_filename_component(AOC_DAY ${CMAKE_CURRENT_SOURCE_DIR} NAME)
    set(TASK ${AOC_YEAR}_${AOC_DAY})
    add_definitions(
        -DAOC_TEST=year_${TASK}
        -DAOC_TASK="${TASK}"
        -DAOC_INPUT="${AOC_DAY}.input"
        -DAOC_HEADER="${AOC_DAY}.h"
    )
endmacro()
