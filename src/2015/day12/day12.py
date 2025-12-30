import json
import sys

from libs.aoc_runner.python import aoc_runner


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


def samples():
    pass


def solve_1(x):
    data = json.loads(x[0])
    res, _ = solve(data)
    print(f"part 1: {res}")
    assert res == 119433


def solve_2(x):
    data = json.loads(x[0])
    res, _ = solve(data, True)
    print(f"part 2: {res}")
    assert res == 68466


if __name__ == "__main__":
    with open("day12.input", "r", encoding="utf8") as f:
        inp = f.readlines()
    sys.exit(
        aoc_runner.aoc_runner(
            samples,
            solve_1,
            solve_2,
            inp,
        )
    )
