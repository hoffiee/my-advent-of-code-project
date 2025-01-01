aoc_set_task_variables()
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY})
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY}-sample-1)
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY}-sample-2)
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY}-sample-3)
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY}-fixed)

add_executable(${TASK} ${AOC_DAY}.cpp)

target_link_libraries(${TASK}
    PRIVATE
    aoc-runner
    icecream
    string-utils
    aoc-utils
)

add_custom_target(${TASK}-run
    COMMAND ./${TASK}
    DEPENDS ${TASK}
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

add_custom_target(${TASK}-bench
    COMMAND hyperfine ./${TASK}
    DEPENDS ${TASK}
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
