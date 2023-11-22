get_filename_component(AOC_DAY ${CMAKE_CURRENT_SOURCE_DIR} NAME)
set(TASK  "day15")

add_executable(${TASK} ${TASK}.cpp)
add_executable(${TASK}-2 ${TASK}_2.cpp)

aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY})
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY}-sample)

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
