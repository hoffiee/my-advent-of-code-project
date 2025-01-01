aoc_set_task_variables()
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY})
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY}-sample)
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY}-sample-1)

add_executable(${TASK} ${AOC_DAY}.cpp)

target_link_libraries(${TASK}
    PRIVATE
    icecream
    aoc-runner
    string-utils
)

add_custom_target(${TASK}-run
    COMMAND ./${TASK}
    DEPENDS ${TASK}
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

aoc_bench_add_target(${TASK})
