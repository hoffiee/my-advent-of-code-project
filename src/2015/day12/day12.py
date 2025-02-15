import json
import sys

from libs.python.aoc_runner import aoc_runner


def solve(data, validate=False):
    if data == None:
        return 0

    if isinstance(data, str):
        if validate and data == "red":
            return 0, False
        return 0, True

    if isinstance(data, int):
        return data, True

    if isinstance(data, list):
        sum = 0
        for obj in data:
            value, valid = solve(obj, validate)
            sum += value
        return sum, True

    sum = 0
    for [key, val] in data.items():
        value, valid = solve(val, validate)
        if not valid:
            return 0, True
        sum += value
    return sum, True


def sol1(lines):
    data = json.loads(lines[0])
    part, _ = solve(data)
    return part


def sol2(lines):
    data = json.loads(lines[0])
    part, _ = solve(data, True)
    return part


def samples():
    pass


if __name__ == "__main__":
    with open("day12.input", "r", encoding="utf8") as f:
        inp = f.readlines()
    sys.exit(
        aoc_runner.aoc_runner(
            samples,
            lambda x: print(f"problem 1: {sol1(x)}"),
            lambda x: print(f"problem 2: {sol2(x)}"),
            inp,
        )
    )
