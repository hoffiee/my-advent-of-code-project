set(TASK "python-module")

aoc_add_python_target(${TASK}-run example_module.py)

aoc_add_python_test(${TASK}-runtest)

aoc_add_python_benchmark(${TASK}-bench example_module.py)
