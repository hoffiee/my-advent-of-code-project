# AoC runner

This utility allows the binary to be run with specific tasks, which allows part
1 or part 2 to be benchmarked properly. For example, to run part 1 and part 2
individually.

```bash
hyperfine ./2024_day03 -p1
hyperfine ./2024_day03 -p2
```

Then when the binary is run without any arguments it's supposed to run the
sample stage, which will bail out if any step fails inside it.
