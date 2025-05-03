aoc_set_task_variables()

aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY})

add_library(lib-${TASK}
    EXCLUDE_FROM_ALL
    ${AOC_DAY}.cpp
)

target_include_directories(lib-${TASK}
    PUBLIC
    .
)

add_executable(${TASK} main.cpp)

target_link_libraries(${TASK}
    lib-${TASK}
    icecream
    aoc-utils
    aoc-runner
    string-utils
)

add_custom_target(${TASK}-preprocess
    COMMAND ./preprocess.sh ${CMAKE_CURRENT_BINARY_DIR}/${AOC_DAY}.input > ${CMAKE_CURRENT_BINARY_DIR}/${AOC_DAY}.preprocessed.input
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(${TASK}-run
    COMMAND ./${TASK}
    DEPENDS ${TASK} ${TASK}-preprocess
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

add_executable(${TASK}-test test_${AOC_DAY}.cpp)

target_link_libraries(${TASK}-test
    gtest-wrapper
    lib-${TASK}
)

gtest_discover_tests(${TASK}-test)

add_custom_target(${TASK}-runtest
    COMMAND ctest --output-on-failure
    DEPENDS ${TASK}-test
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

aoc_bench_add_target(${TASK})
