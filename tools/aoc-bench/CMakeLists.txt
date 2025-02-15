add_custom_target(aoc_bench
    COMMAND go build -o ${CMAKE_CURRENT_BINARY_DIR}/aoc_bench aoc_bench.go
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(aoc_bench-example
    # Set a name that matches the others.
    COMMAND go build -o 2013_day03 ${CMAKE_CURRENT_SOURCE_DIR}/example.go
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_target(aoc_bench-dev
    COMMAND go run aoc_bench.go --target=${CMAKE_CURRENT_BINARY_DIR}/2013_day03 --db=${CMAKE_SOURCE_DIR}/bench.db
    DEPENDS aoc_bench-example
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

macro(aoc_bench_add_target TARGET_NAME)
    get_target_property(BENCH_BINARY_DIR aoc_bench BINARY_DIR)
    add_custom_target(${TARGET_NAME}-bench
        COMMAND ${BENCH_BINARY_DIR}/aoc_bench --target=./${TARGET_NAME} --db=${CMAKE_SOURCE_DIR}/bench.db
        DEPENDS aoc_bench ${TARGET_NAME}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
endmacro()
