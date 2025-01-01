aoc_set_task_variables()
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY})
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY}-sample)
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY}-sample-1)
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY}-sample-2)
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY}-sample-3)
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY}-sample-4)
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY}-sample-5)
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY}-sample-6)
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY}-sample-7)
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY}-sample-8)
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY}-sample-9)
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY}-sample-10)
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY}-sample-12) # <-- HARD ones for me.

add_executable(${TASK} ${AOC_DAY}.cpp)

target_link_libraries(${TASK}
    PRIVATE
    icecream
    aoc-runner
    string-utils
    aoc-utils
    openmp-wrapper
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

aoc_add_python_target(${TASK}-py ${AOC_DAY}.py)
