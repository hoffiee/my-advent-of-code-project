aoc_set_task_variables()
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY})
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY}-sample)

add_executable(${TASK} ${AOC_DAY}.cpp)

add_custom_target(${TASK}-preprocess
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/preprocess.awk ${AOC_DAY}-sample.input > ${AOC_DAY}-sample.preprocessed.input;
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/preprocess.awk ${AOC_DAY}.input > ${AOC_DAY}.preprocessed.input;
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

target_link_libraries(${TASK}
    PRIVATE
    icecream
    aoc_runner
    aoc_utils
)

add_custom_target(${TASK}-run
    COMMAND ./${TASK}
    DEPENDS ${TASK} ${TASK}-preprocess
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

aoc_bench_add_target(${TASK})
