macro(aoc_add_go_target)
    add_custom_target(${ARGV0}
        COMMAND go build -o ${ARGV0} ${CMAKE_CURRENT_SOURCE_DIR}/${ARGV1}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
    add_custom_target(${ARGV0}-run
        COMMAND go run ${CMAKE_CURRENT_SOURCE_DIR}/${ARGV1}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
endmacro()

add_custom_target(format-go
    COMMAND git ls-files src libs tools
        | grep -E  '\\.go$$'
        | xargs -I {} go fmt {}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)
