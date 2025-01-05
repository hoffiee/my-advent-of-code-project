# Advent of code

This is my repo for [Advent of Code](https://adventofcode.com/). This project
has morphed over the years as I've mainly used this to learn methods,
languages, tooling, etc. throughout the years. For now it has converged towards
running this as a CMake project focusing on C++/Python.


## Status

To see the status of advent of code and what remains in order to reach some
targets that I've set, update `tools/event_status.py` and run `ninja status`.


## Dependencies

- Cmake
- ninja
- conan
- Probably a few more... I have not setup this properly.


## Setup

```bash
# stand in root of advent-of-code
mkdir build
conan install . --build=missing --output-folder=build
cd build
cmake -G Ninja -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake ..
```

**Note**: I'm using some external libraries, these do not build due to my
compiler flags, I brilliantly solved it by manually patching the files, but I
should look into how to handle this properly so that I don't have to patch them
locally.


### Tips and notes

- I often use icecream in both C++ and Python to do debug statements, it's
  quick and neat to use. For example in Python:

```python
from icecream import ic
a = "moo"
ic(a)
```


### Other targets than C++ or Python

This project mainly targets C++ and Python, at the moment other target
languages will have to be handled manually, and I doubt that I'll fix so that
they will run unless I aim to learn that specific language for a specific year.
At the moment running `ninja used-file-extensions` gives:

```
    164 cpp
     40 h
     30 py
      5 go
      5 awk
      3 hs
      1 sh
      1 md
      1 jl
      1 ipynb
```


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
inspiration from elsewher. The result of this is that I may have some solutions
that are not entirely mine. With this in mind I have in the last years been
more explicit about mentioning this in the solution.
