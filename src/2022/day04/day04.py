"""After completing this in C++ I wanted to make a set based approach too"""

import re
import sys

from libs.python.aoc_runner import aoc_runner


def sol1(list_of_pairs: list[tuple[set[int], set[int]]]) -> int:
    """Counts occurences by checking if the sets are subsets to one another"""
    count = 0
    for elf_1, elf_2 in list_of_pairs:
        if elf_1.issubset(elf_2) or elf_2.issubset(elf_1):
            count += 1

    return count


def sol2(list_of_pairs: list[tuple[set[int], set[int]]]) -> int:
    """Checks if the sets intersects at any points"""
    count = 0
    for elf_1, elf_2 in list_of_pairs:
        if len(elf_1 & elf_2) > 0:
            count += 1

    return count


def read_and_parse(filename: str) -> list[tuple[set[int], set[int]]]:
    """Reads the file line by line and parses the pattern
    d_1-d_2,d_3-d_4
    into 2 sets defined by {d_1..d_2}, {d_3..d_4} and returns a list of these pairs
    """

    with open(filename, "r", encoding="utf-8") as open_file:
        lines = open_file.readlines()
        list_of_pairs = []
        for line in lines:
            d_1, d_2, d_3, d_4 = map(int, re.findall(r"\d+", line))

            elf_1 = set(range(d_1, d_2 + 1))
            elf_2 = set(range(d_3, d_4 + 1))

            list_of_pairs.append((elf_1, elf_2))
        return list_of_pairs


def samples():
    sample = read_and_parse("day04-sample.input")
    assert sol1(sample) == 2
    assert sol2(sample) == 4


if __name__ == "__main__":
    inp = read_and_parse("day04.input")
    sys.exit(
        aoc_runner.aoc_runner(
            samples,
            lambda x: print(f"problem 1: {sol1(x)}"),
            lambda x: print(f"problem 2: {sol2(x)}"),
            inp,
        )
    )
