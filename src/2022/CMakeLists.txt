set(AOC_YEAR 2022)

add_subdirectory(day01)
add_subdirectory(day02)
add_subdirectory(day03)
add_subdirectory(day04)
add_subdirectory(day05)
add_subdirectory(day06)
add_subdirectory(day07)
add_subdirectory(day08)
add_subdirectory(day09)
add_subdirectory(day10)
add_subdirectory(day11)
add_subdirectory(day12)
add_subdirectory(day14)
add_subdirectory(day15)
add_subdirectory(day18)
add_subdirectory(day21)

add_custom_target(${AOC_YEAR}-runtest
    COMMAND ctest --output-on-failure
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
