macro(aoc_copy_input_file)
    file(COPY ${PROJECT_SOURCE_DIR}/aoc-puzzle-inputs/${ARGV0}/${ARGV1}.input
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
    )
endmacro()
