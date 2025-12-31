add_custom_target(format
    DEPENDS format-cpp format-py format-go format-rust
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

add_subdirectory(aoc-bench)
add_subdirectory(python-example)
