add_custom_target(aoc_bench-dev
    COMMAND go run ${CMAKE_CURRENT_SOURCE_DIR}/aoc_bench.go ./example
    DEPENDS aoc_bench-example
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_target(aoc_bench-example
    COMMAND go build -o example ${CMAKE_CURRENT_SOURCE_DIR}/example.go
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_target(aoc_bench
    COMMAND go build -o aoc_bench ${CMAKE_CURRENT_SOURCE_DIR}/aoc_bench.go
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

macro(aoc_bench_add_target TARGET_NAME)
    get_target_property(BENCH_BINARY_DIR aoc_bench BINARY_DIR)
    # message("target binary dir: ${bench_binary_dir}")
    # message("current binary dir: ${CMAKE_CURRENT_BINARY_DIR}")
    # message("target_name: ${target_name}")
    add_custom_target(${TARGET_NAME}-bench
        COMMAND ${BENCH_BINARY_DIR}/aoc_bench ./${TARGET_NAME}
        DEPENDS aoc_bench ${TARGET_NAME}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
endmacro()
