aoc_set_task_variables()

aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY})
aoc_copy_input_file(${AOC_YEAR} sample)
aoc_copy_input_file(${AOC_YEAR} invalid)
aoc_copy_input_file(${AOC_YEAR} valid)

aoc_add_python_target(${TASK}-py ${AOC_DAY}.py)

aoc_bench_add_target(${TASK}-py)
