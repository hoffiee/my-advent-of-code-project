add_library(string-utils
    src/string_utils.cpp
)

target_include_directories(string-utils
    PUBLIC
    include
)

add_executable(string-utils-test test/test_string_utils.cpp)

target_link_libraries(string-utils-test
    gtest-wrapper

    # lib under test
    string-utils
)

gtest_discover_tests(string-utils-test)

add_custom_target(string-utils-runtest
    COMMAND ctest --output-on-failure
    DEPENDS string-utils-test
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
