add_library(lib-intcode-computer
    EXCLUDE_FROM_ALL
    intcode_computer.cpp
)

target_include_directories(lib-intcode-computer
    PUBLIC
    .
)

target_link_libraries(lib-intcode-computer
    icecream
)

add_executable(lib-intcode-computer-test test_intcode_computer.cpp)

target_link_libraries(lib-intcode-computer-test
    gtest-wrapper
    lib-intcode-computer
)

gtest_discover_tests(lib-intcode-computer-test)

add_custom_target(lib-intcode-computer-runtest
    COMMAND ctest
    DEPENDS lib-intcode-computer-test
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
