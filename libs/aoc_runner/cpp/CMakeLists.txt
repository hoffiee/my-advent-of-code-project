add_library(aoc_runner
    src/aoc_runner.cpp
)

target_include_directories(aoc_runner
    PUBLIC
    include
)

add_executable(aoc_runner-test test/test_aoc_runner.cpp)

target_link_libraries(aoc_runner-test
    gtest-wrapper
    aoc_runner
)

gtest_discover_tests(aoc_runner-test)

add_custom_target(aoc_runner-runtest
    COMMAND ctest --output-on-failure
    DEPENDS aoc_runner-test
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
