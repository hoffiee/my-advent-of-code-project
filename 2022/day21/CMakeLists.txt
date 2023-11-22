get_filename_component(AOC_DAY ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set(TASK "day21")

add_executable(${TASK} ${TASK}.cpp)

aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY})
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY})

add_custom_target(${TASK}-run
    COMMAND ./${TASK}
    DEPENDS ${TASK} # ${TASK}-preprocess
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

add_custom_target(${TASK}-py
    COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/${AOC_DAY}.py
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_target(${TASK}-bench
    COMMAND hyperfine ./${TASK}
    DEPENDS ${TASK}
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
