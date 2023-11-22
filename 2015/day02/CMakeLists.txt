get_filename_component(AOC_DAY ${CMAKE_CURRENT_SOURCE_DIR} NAME)

set(TASK ${AOC_YEAR}_${AOC_DAY})

add_definitions(
    -DAOC_TEST=year_${TASK}
    -DAOC_TASK="${TASK}"
    -DAOC_HEADER="${TASK}.h"
)

add_executable(${TASK} ${TASK}.cpp)

aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY})

add_custom_target(${TASK}-run
    COMMAND ./${TASK}
    DEPENDS ${TASK}
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
