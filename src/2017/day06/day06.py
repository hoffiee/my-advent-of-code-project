import re
import sys

from libs.aoc_runner.python import aoc_runner


def cmp_list(a, b):
    """compare 2 lists, is there a better way to do this?"""
    return all(i == j for i, j in zip(a, b))


def solution(data):
    configurations = [data.copy()]
    memory = data.copy()

    while True:
        tmp = max(memory)
        ind = memory.index(tmp)
        nr_of_memory_banks = len(memory)
        memory[ind] = 0

        while tmp > 0:
            ind = (ind + 1) % nr_of_memory_banks
            memory[ind] += 1
            tmp -= 1

        for i, configuration in enumerate(configurations):
            if cmp_list(memory, configuration):
                return len(configurations), len(configurations) - i

        configurations.append(memory.copy())
    return 0, 0


def sol1(data):
    a, _ = solution(data)
    return a


def sol2(data):
    _, b = solution(data)
    return b


def samples():
    with open("day06-sample.input", "r", encoding="utf8") as file:
        line = file.readline()
        sample = list(map(int, re.findall(r"\d+", line)))
    assert sol1(sample) == 5
    assert sol2(sample) == 4


if __name__ == "__main__":
    with open("day06.input", "r", encoding="utf8") as file:
        line = file.readline()
        inp = list(map(int, re.findall(r"\d+", line)))
    sys.exit(
        aoc_runner.aoc_runner(
            samples,
            lambda x: print(f"problem 1: {sol1(x)}"),
            lambda x: print(f"problem 2: {sol2(x)}"),
            inp,
        )
    )
