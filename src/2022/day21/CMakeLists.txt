aoc_set_task_variables()
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY})
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY}-sample)

add_executable(${TASK} ${AOC_DAY}.cpp)

add_custom_target(${TASK}-run
    COMMAND ./${TASK}
    DEPENDS ${TASK}
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

add_custom_target(${TASK}-py
    COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/${AOC_DAY}.py
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

aoc_bench_add_target(${TASK})
