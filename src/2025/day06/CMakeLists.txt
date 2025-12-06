aoc_set_task_variables()
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY})
aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY}-sample)

aoc_rust_add_target(${TASK} ${AOC_DAY}.rs)
aoc_rust_add_test(${TASK})

aoc_bench_add_target(${TASK})
