# TODO: Fix setup
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
add_executable(${TASK}-2 ${AOC_DAY}_2.cpp)

# add_compile_options(-Wall -Werror -pedantic -g -O3 -pthread)

# add threading
list(APPEND CMAKE_CXX_FLAGS "-pthread")

add_custom_target(${TASK}-preprocess
    COMMAND ./preprocess.awk ${TASK}-sample.input > ${TASK}-sample.prep.input;
    COMMAND ./preprocess.awk ${TASK}.input > ${TASK}.prep.input;
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

add_custom_target(${TASK}-run
    COMMAND ./${TASK}
    DEPENDS ${TASK} ${TASK}-preprocess
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

add_custom_target(${TASK}-2-run
    COMMAND ./${TASK}-2
    DEPENDS ${TASK}-2 # ${TASK}-preprocess
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

add_custom_target(${TASK}-bench
    COMMAND hyperfine ./${TASK}
    DEPENDS ${TASK}
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
