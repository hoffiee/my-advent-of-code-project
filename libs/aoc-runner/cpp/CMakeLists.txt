add_library(aoc-runner
    src/aoc_runner.cpp
)

target_include_directories(aoc-runner
    PUBLIC
    include
)

add_executable(aoc-runner-test test/test_aoc_runner.cpp)

target_link_libraries(aoc-runner-test
    gtest-wrapper
    aoc-runner
)

gtest_discover_tests(aoc-runner-test)

add_custom_target(aoc-runner-runtest
    COMMAND ctest --output-on-failure
    DEPENDS aoc-runner-test
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
