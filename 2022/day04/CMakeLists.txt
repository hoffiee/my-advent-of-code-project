get_filename_component(AOC_DAY ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set(TASK "day04")

add_executable(${TASK} ${TASK}.cpp)

aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY})
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY}-sample)

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

# add_custom_target(${TASK}-py
#     COMMAND python3 ${CMAKE_CURRENT_SOURCE_DIR}/${TASK}.py
#     WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
# )

add_custom_target(${TASK}-py-bench
    COMMAND hyperfine python3 ${CMAKE_CURRENT_SOURCE_DIR}/${TASK}.py
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

aoc_add_python_target(${TASK} ${AOC_DAY})
