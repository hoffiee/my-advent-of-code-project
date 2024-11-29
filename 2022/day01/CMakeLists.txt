aoc_set_task_variables()
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY})
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY}-sample)

add_executable(${TASK} ${AOC_DAY}.cpp)

add_custom_target(${TASK}-run
    COMMAND ./${TASK}
    DEPENDS ${TASK}
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
