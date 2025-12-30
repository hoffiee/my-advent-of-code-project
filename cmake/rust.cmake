# Rust target helpers

# find_program(CARGO_EXECUTABLE cargo)
# if(CARGO_EXECUTABLE)
#     message(STATUS "Found cargo: ${CARGO_EXECUTABLE}")
#     set(HAVE_CARGO TRUE)
# else()
#     message(STATUS "cargo not found; Rust targets will be skipped.")
#     set(HAVE_CARGO FALSE)
# endif()
# if(HAVE_CARGO)
#     # add_custom_command / add_custom_target for your Rust code here
# endif()

# Look for 'cargo' in PATH
find_program(CARGO_EXECUTABLE cargo)

if(NOT CARGO_EXECUTABLE)
    message(FATAL_ERROR "cargo not found. Please install Rust and ensure 'cargo' is in PATH.")
endif()

message(STATUS "Found cargo: ${CARGO_EXECUTABLE}")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(RUST_PROFILE release)
    set(CARGO_BUILD_ARG --release)
else()
    set(RUST_PROFILE debug)
    set(CARGO_BUILD_ARG)
endif()

# To avoid lock on package cache define a job pool for Cargo so that only one
# of these are run at the same time
set(CMAKE_JOB_POOLS rust_cargo_pool=1 CACHE STRING "Rust Cargo pools")

macro(aoc_rust_add_target)
    add_custom_command(
        OUTPUT ${ARGV0}_
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND env CARGO_TARGET_DIR=${CMAKE_CURRENT_BINARY_DIR} cargo build ${CARGO_BUILD_ARG}
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_BINARY_DIR}/${RUST_PROFILE} ${CMAKE_CURRENT_BINARY_DIR}/
        JOB_POOL rust_cargo_pool
        COMMENT "Building Rust executable ${ARGV0} with Cargo (${RUST_PROFILE})"
        VERBATIM
    )

    add_custom_target(${ARGV0} ALL
        DEPENDS ${ARGV0}_
    )

    add_custom_target(${ARGV0}-run
        COMMAND ./${RUST_PROFILE}/${ARGV0}
        DEPENDS ${ARGV0}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
endmacro()

macro(aoc_rust_add_test)
    add_custom_command(
        OUTPUT ${ARGV0}-test_
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND env CARGO_TARGET_DIR=${CMAKE_CURRENT_BINARY_DIR} cargo test --no-run
        JOB_POOL rust_cargo_pool
        COMMENT "Building Rust test executable ${ARGV0} with Cargo (${RUST_PROFILE})"
        VERBATIM
    )

    add_custom_target(${ARGV0}-test ALL
        DEPENDS ${ARGV0}-test_
    )

    add_custom_target(${ARGV0}-runtest
        COMMAND env CARGO_TARGET_DIR=${CMAKE_CURRENT_BINARY_DIR} cargo test --verbose
        DEPENDS ${ARGV0}-test
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Running Rust test ${ARGV0} with Cargo (${RUST_PROFILE})"
        VERBATIM
    )

    add_test(
        NAME ${ARGV0}-test
        COMMAND cargo test --verbose
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
endmacro()

add_custom_target(format-rust
    COMMAND find ${CMAKE_SOURCE_DIR} -name Cargo.toml -type f
        | sed 's/Cargo.toml$$//'
        | parallel 'cd '{}' && cargo fmt'
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Rust: Formating"
)
