add_library(string_utils
    src/string_utils.cpp
)

target_include_directories(string_utils
    PUBLIC
    include
)

add_executable(string_utils-test test/test_string_utils.cpp)

target_link_libraries(string_utils-test
    gtest-wrapper

    # lib under test
    string_utils
)

gtest_discover_tests(string_utils-test)

add_custom_target(string_utils-runtest
    COMMAND ctest --output-on-failure
    DEPENDS string_utils-test
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
