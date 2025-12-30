set(TASK "python-module")

aoc_add_python_target(${TASK} example_module.py)

aoc_add_python_test(${TASK})
