find_program(GOLANG_EXECUTABLE go)

if(NOT GOLANG_EXECUTABLE)
    message(FATAL_ERROR "go not found. Please install go and ensure 'go' is in PATH.")
endif()

message(STATUS "Found go: ${GOLANG_EXECUTABLE}")

# TODO Setup build/release for Go

macro(aoc_add_go_target)
    if (NOT GOLANG_EXECUTABLE)
        message(WARNING "Go not found! Won't add target: " ${ARGV0})
    else()
        add_custom_target(${ARGV0}
            COMMAND go build -v -o ${CMAKE_CURRENT_BINARY_DIR}/${ARGV0} ${ARGV1}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            VERBATIM
        )
        add_custom_target(${ARGV0}-run
            COMMAND ./${ARGV0}
            DEPENDS ${ARGV0}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        )
    endif()
endmacro()

add_custom_target(format-go
    COMMAND git ls-files src libs tools
        | grep -E  '\\.go$$'
        | xargs -I {} go fmt {}
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)
