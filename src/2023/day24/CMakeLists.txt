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

target_link_libraries(lib-${TASK}
    PRIVATE
    icecream
    string-utils
    openmp-wrapper
    eigen-wrapper
)

add_executable(${TASK} main.cpp)

target_link_libraries(${TASK}
    lib-${TASK}
    icecream
)

add_custom_target(${TASK}-run
    COMMAND ./${TASK}
    DEPENDS ${TASK}
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
