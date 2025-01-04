import re
from icecream import ic
import json


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
    print(part)


def sol2(lines):
    data = json.loads(lines[0])
    part, _ = solve(data, True)
    print(part)


def main() -> None:
    for filename in ["day12.input"]:
        with open(filename, "r", encoding="utf8") as f:
            lines = f.readlines()
            sol1(lines)
            sol2(lines)


if __name__ == "__main__":
    main()
