set(AOC_YEAR 2025)

add_subdirectory(day01)
add_subdirectory(day02)
add_subdirectory(day03)
add_subdirectory(day04)
add_subdirectory(day05)
add_subdirectory(day06)

add_custom_target(${AOC_YEAR}-runtest
    COMMAND ctest --output-on-failure
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
