# TODO: What Do I want as a user?
# Do I want to setup a aoc_macros for python?

set(TASK "python-module")

# add_custom_target(${TASK}-run
#     COMMAND ${VENV_PYTHON} ${CMAKE_CURRENT_SOURCE_DIR}/example_module.py
#     WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
# )
aoc_add_python_target(${TASK}-run example_module.py)

# add_custom_target(${TASK}-runtest
#     COMMAND ${VENV_PYTEST} ${CMAKE_CURRENT_SOURCE_DIR}
#     WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
# )
aoc_add_python_test(${TASK}-runtest)

# add_custom_target(${TASK}-bench
#     COMMAND hyperfine ${VENV_PYTHON} ${CMAKE_CURRENT_SOURCE_DIR}/example_module.py
#     WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
# )
aoc_add_python_benchmark(${TASK}-bench example_module.py)
