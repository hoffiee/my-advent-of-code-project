get_filename_component(AOC_DAY ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set(TASK ${AOC_YEAR}_${AOC_DAY})

aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY})
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY}-sample)

add_custom_target(${TASK}-py
    COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/${AOC_DAY}.py
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
