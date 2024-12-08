aoc_set_task_variables()

aoc_copy_input_file(${AOC_YEAR} ${AOC_DAY})

aoc_add_python_target(${TASK}-py ${AOC_DAY}.py)
