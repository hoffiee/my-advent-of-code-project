aoc_set_task_variables()
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY})
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY}-sample)

aoc_add_go_target(${TASK}-go ${AOC_DAY}.go)

aoc_bench_add_target(${TASK}-go)
