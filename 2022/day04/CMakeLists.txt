get_filename_component(AOC_DAY ${CMAKE_CURRENT_SOURCE_DIR} NAME)

set(TASK ${AOC_YEAR}_${AOC_DAY})

aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY})
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY}-sample)


add_definitions(
    -DAOC_TEST=year_${TASK}
    -DAOC_TASK="${TASK}"
    -DAOC_INPUT="${AOC_DAY}.input"
    -DAOC_HEADER="${AOC_DAY}.h"
)

add_executable(${TASK} ${AOC_DAY}.cpp)

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

add_custom_target(${TASK}-py-bench
    COMMAND hyperfine python3 ${CMAKE_CURRENT_SOURCE_DIR}/${TASK}.py
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

aoc_add_python_target(${TASK}-py ${AOC_DAY})
