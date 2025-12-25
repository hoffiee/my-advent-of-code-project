aoc_set_task_variables()
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY})
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY}-sample)

add_executable(${TASK} ${AOC_DAY}.cpp)

target_link_libraries(${TASK}
    PRIVATE
    icecream
    aoc_runner
    aoc_utils
)

add_custom_target(${TASK}-run
    COMMAND ./${TASK}
    DEPENDS ${TASK}
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

aoc_add_python_target(${TASK}-py ${AOC_DAY}.py)

aoc_bench_add_target(${TASK})
aoc_bench_add_target(${TASK}-py)
