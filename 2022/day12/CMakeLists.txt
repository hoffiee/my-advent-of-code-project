get_filename_component(AOC_DAY ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set(TASK "day12")

add_executable(${TASK} ${TASK}.cpp)

aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY})
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY})
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY})

# add_custom_target(${TASK}-preprocess
#     COMMAND ./preprocess.awk ${TASK}-sample.input > ${TASK}-sample.prep.input;
#     COMMAND ./preprocess.awk ${TASK}.input > ${TASK}.prep.input;
#     WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
# )

add_custom_target(${TASK}-run
    COMMAND ./${TASK}
    DEPENDS ${TASK} # ${TASK}-preprocess
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

add_custom_target(${TASK}-bench
    COMMAND hyperfine ./${TASK}
    DEPENDS ${TASK}
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
