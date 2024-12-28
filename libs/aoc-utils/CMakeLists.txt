add_library(aoc-utils
    src/aoc_utils.cpp
)

target_include_directories(aoc-utils
    PUBLIC
    include
)

add_executable(aoc-utils-test test/test_aoc_utils.cpp)

target_link_libraries(aoc-utils-test
    gtest-wrapper

    # lib under test
    aoc-utils
)

gtest_discover_tests(aoc-utils-test)

add_custom_target(aoc-utils-runtest
    COMMAND ctest --output-on-failure
    DEPENDS aoc-utils-test
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
