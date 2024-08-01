# Advent of code

This is my repository for when I play around with [Advent of
Code](https://adventofcode.com/). This project has morphed over the years as
I've mainly used this to learn methods, languages, tooling, etc. throughout the
years. For now it has converged towards running this as a CMake project,
focusing on C++/Python. I'm doing this as a larger project to learn more about
CMake. I have a lot to learn so let's see where this goes.


## Status

To see the status of advent of code and what remains in order to reach some
targets that I've setup for myself, update `tools/tasks_left.py` and run `ninja
status`.


## Dependencies

- Cmake
- ninja
- conan
- Probably a few more... I have not setup this properly.


## Repo setup

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

- I often use icecream in both C++ and Python to do debug statements, I find it
  quick and neat to use. For example in Python:

```python
import icecream as ic
a = "moo"
ic(a)
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

The Advent of Code creator has, if I recall correctly, mentioned that puzzle
input shouldn't be shared since he spends a great time designing these puzzles
and want to keep them secret. For that purpose I have broken out my puzzle
input and placed them in their own repository which I self-host, which I then
inlude to this repository. The structure follows this pattern:

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
inspiration from elsewhere, for me Advent of code is a place to learn and only
to learn, so I more often than not look into other solutions to see how I could
improve mine. The result of this is that I may have some solutions that are not
entirelly mine. With this in mind I have in the last years been more explicit
about mentioning this in the solution.
