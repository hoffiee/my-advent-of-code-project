add_custom_target(status
    COMMAND python3 event_status.py
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(used-file-extensions
    COMMAND find src -type f
        | grep -vE '\(CMakeLists.txt\)'
        | cut -d"." -f2 # cut at delimeter . and print second field
        | sort | uniq -c | sort -nr
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

add_custom_target(all-runtest
    COMMAND ctest --output-on-failure -j2
    DEPENDS all
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
)

add_custom_target(format
    DEPENDS format-cpp format-py format-go
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

add_subdirectory(aoc-bench)
add_subdirectory(python-example)
