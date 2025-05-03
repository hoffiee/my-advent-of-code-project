add_subdirectory(2015)
add_subdirectory(2016)
add_subdirectory(2017)
add_subdirectory(2018)
add_subdirectory(2019)
add_subdirectory(2020)
add_subdirectory(2021)
add_subdirectory(2022)
add_subdirectory(2023)
add_subdirectory(2024)

add_custom_target(all-runtest
    COMMAND ctest --output-on-failure -j2
    DEPENDS all
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
)

