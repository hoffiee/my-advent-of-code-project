get_filename_component(AOC_DAY ${CMAKE_CURRENT_SOURCE_DIR} NAME)

set(TASK ${AOC_YEAR}_${AOC_DAY})

add_definitions(
    -DAOC_TEST=year_${TASK}
    -DAOC_TASK="${TASK}"
    -DAOC_INPUT="${TASK}.input"
    -DAOC_HEADER="${TASK}.h"
)

add_library(lib-${TASK}
    EXCLUDE_FROM_ALL
    ${TASK}.cpp
)

target_include_directories(lib-${TASK}
    PUBLIC
    .
)

target_link_libraries(lib-${TASK}
    PRIVATE
    icecream
    OpenMP::OpenMP_CXX
)

add_executable(${TASK} main.cpp)

target_link_libraries(${TASK}
    lib-${TASK}
    icecream
)

aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY})

add_custom_target(${TASK}-run
    COMMAND ./${TASK}
    DEPENDS ${TASK}
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)


add_executable(${TASK}-test test_${TASK}.cpp)

target_link_libraries(${TASK}-test
    ${GTEST_LIBRARIES}
    ${GTEST_MAIN_LIBRARIES}
    pthread

    # lib under test
    lib-${TASK}
)

gtest_discover_tests(${TASK}-test)

add_custom_target(${TASK}-runtest
    COMMAND ctest --output-on-failure
    DEPENDS ${TASK}-test
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
