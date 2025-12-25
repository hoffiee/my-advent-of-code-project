add_library(aoc_utils
    src/aoc_utils.cpp
)

target_include_directories(aoc_utils
    PUBLIC
    include
)

add_executable(aoc_utils-test test/test_aoc_utils.cpp)

target_link_libraries(aoc_utils-test
    gtest-wrapper

    # lib under test
    aoc_utils
)

gtest_discover_tests(aoc_utils-test)

add_custom_target(aoc_utils-runtest
    COMMAND ctest --output-on-failure
    DEPENDS aoc_utils-test
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
