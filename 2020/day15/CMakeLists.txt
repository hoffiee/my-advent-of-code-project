get_filename_component(AOC_DAY ${CMAKE_CURRENT_SOURCE_DIR} NAME)

set(TASK "${AOC_YEAR}_${AOC_DAY}")

add_definitions(
    -DAOC_TEST=year_${TASK}
    -DAOC_TASK="${TASK}"
    -DAOC_HEADER="${TASK}.h"
)

aoc_add_python_target(${TASK}-run ${AOC_DAY}.py)
