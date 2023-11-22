get_filename_component(AOC_DAY ${CMAKE_CURRENT_SOURCE_DIR} NAME)

set(TASK "day2")

# add_custom_target(${TASK}-awk
#     COMMAND ./day2.awk day2-sample.input
#     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
# )

add_executable(${TASK} ${TASK}.cpp)

aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY})
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY})
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY})

add_custom_target(${TASK}-run
    COMMAND ./${TASK}
    DEPENDS ${TASK}
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
