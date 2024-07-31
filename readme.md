# Advent of code

Here is my repository for when I play around with [Advent of
Code](https://adventofcode.com/)

This project has morphed over the years, for me advent of code has always been
a moment to learn. I've converged towards running this as a CMake project, and
are mainly using C++ with some pre-processing with awk/python at this point.
I'm doing this as a larger project to learn and improve my knowledge within
CMake and build and concepts. I have a lot to learn so let's see where this
goes :).


## Status

To see the status of advent of code and what remains in order to reach my
targets, update `tools/tasks_left.py` and run `ninja status`.


## Dependencies

- Cmake
- ninja
- conan
- probably a few more...


## Development setup

Current way of setting this repo up, still includes a lot of manual work for
python solutions and haskell solutions not included yet, I doubt that I'll add
them.

```bash
# stand in root of advent-of-code
mkdir build
conan install . --build=missing --output-folder=build
cd build
cmake -G Ninja -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake ..
```


### Other targets than C++ or Python

This project mainly targets C++ and Python, at the moment other target
languages will have to be handled manually, and I doubt that I'll fix so that
they will run unless I aim to learn that specific language for a specific year.
At the moment running `ninja used-file-extensions` gives:

```
    134 cpp
     40 h
     23 py
      5 awk
      3 hs
      1 sh
      1 md
      1 jl
      1 ipynb
```


## Puzzle inputs

The puzzle creator has, if I recall correctly, mentioned that puzzle input
shouldn't be shared since he spends a great time designing these puzzles and
want to keep them secret. For that purpose I have broken out my puzzle input
and placed them in their own repository which I self-host, which I then inlude
to this repository. The structure follows this pattern:

```
.
|-- 2015
|   |-- day01
|   |-- day02
|   |-- ...
|-- ...
|-- 2022
|   |-- day01
|   |-- ...
|-- aoc-puzzle-inputs
|   |-- 2015
|   |-- ...
|   |-- 2022
|-- libs  : Common libraries
|   |-- 3pp  : third party libraries
|-- cmake
|-- readme.md
`-- tools
```


## Inspiration

After I've completed tasks (or those days in which I won't do it or won't
manage to complete them) I often browse for inspiration and learning. Reddit
AdventOfCode solution megathreads is a very neat place to learn. Other than
that I list a few here where I've found cool solutions that I can learn from

- [Github: Happy Cerberus - moderncpp-aoc-2022](https://github.com/HappyCerberus/moderncpp-aoc-2022)

*Note*: Since I have hosted this repository privately before I haven't been
strict on emphasizing which solutions are purely my own and when I took
inspiration from elsewhere, for me Advent of code is to learn and only to
learn, so I more often than not look into other solutions to see how I could
improve mine. But the result of this is that I may have some solutions that are
actually not entirelly mine. With this in mind I have in the last years been
more explicit about mentioning this in the solution.
