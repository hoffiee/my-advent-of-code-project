# Advent of code

This is my [Advent of Code](https://adventofcode.com/) project. This has
morphed over the years as I've mainly used this to learn methods, languages,
tooling, etc. throughout the years. For now it has converged towards running
this as a CMake project focusing on C++/Python.


## How to run

Currently migrating this to have it's own work-space similar to python's
virtual environment and have all tooling available through the command `aoc`.

```bash
source tools/workspace.sh

# show usage and available commands
aoc --help

# and for example
aoc build <target>
```

## Dependencies

- Cmake
- ninja
- conan
- Probably a few more... I have not setup this properly.


## Puzzle inputs

The Advent of Code creator has requested that the puzzle input shouldn't be
shared, in order to handle that I've setup a subrepo that contains all my input
that I'm self hosting. The structure follows this pattern:

```
|-- libs  : Common libraries
|   |-- 3pp  : third party libraries
|   `-- ...
|-- aoc-puzzle-inputs
|   |-- 2015
|   |   |-- day01.input
|   |   |-- day01-sample.input
|   |   `-- ...
|   |-- 2016
|   `-- ...
|-- src
|   |-- 2015
|   |   |-- day01
|   |   |-- day02
|   |   |-- ...
    |-- 2022
    |   |-- day01
    |   `-- ...
    `-- ...
|-- cmake
|-- readme.md
`-- tools
```


## Resources

After I've completed tasks (or those days in which I won't do it or won't
manage to complete them) I often browse for inspiration. Here are a few
resources I've found:

- [Reddit r/advent of code](https://www.reddit.com/r/adventofcode/)
- [Leaderboard times, summary and stats from various years](https://aoc.xhyrom.dev/)
- [450 stars: a categorization and
  mega-guide](https://www.reddit.com/r/adventofcode/comments/1gdw4cj/450_stars_a_categorization_and_megaguide/)

**Note**: Since I have hosted this repository privately before I haven't been
strict on emphasizing which solutions are purely my own and when I took
inspiration from elsewhere. The result of this is that I may have some solutions
that are not entirely mine. With this in mind I have in the last years been
more explicit about mentioning this in the solution.
