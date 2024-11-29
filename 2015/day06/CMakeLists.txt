aoc_set_task_variables()

aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY})
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY})

add_library(lib-${TASK}
    EXCLUDE_FROM_ALL
    ${AOC_DAY}.cpp
)

# TODO Fix this override!
# Override input since we're preprocessing
# target_compile_definitions(lib-${TASK}
#     -DAOC_INPUT="${AOC_DAY}.preprocessed.input"
# )

target_include_directories(lib-${TASK}
    PUBLIC
    .
)

add_executable(${TASK} main.cpp)

target_link_libraries(${TASK}
    lib-${TASK}
)

add_custom_target(${TASK}-preprocess
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/preprocess.awk ${AOC_DAY}.input > ${AOC_DAY}.preprocessed.input
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
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
    COMMAND ctest
    DEPENDS ${TASK}-test
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
