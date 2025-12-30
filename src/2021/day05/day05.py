import re
from typing import Dict, Tuple
import sys

from libs.aoc_runner.python import aoc_runner

DISABLE_PRINT: bool = True


def print_grid(grid, limits) -> None:
    if DISABLE_PRINT:
        return
    (min_x, max_x, min_y, max_y) = limits
    for y in range(min_y, max_y + 1, 1):
        for x in range(min_x, max_x + 1, 1):
            print(grid.get((x, y), 0), end="")
        print()


def populate_grid(entries):
    (min_x, min_y, _, _) = entries[0]
    (max_x, max_y, _, _) = entries[0]

    grid: Dict[Tuple[int, int], int] = {}
    for entry in entries:
        (x1, y1, x2, y2) = entry
        steps = max([abs(x2 - x1), abs(y2 - y1)])
        for step in range(steps + 1):
            if y2 - y1 == 0:
                x = min([x1, x2]) + step
                y = min([y1, y2])
            elif x2 - x1 == 0:
                x = min([x1, x2])
                y = min([y1, y2]) + step
            else:
                if (x1 < x2) and (y1 < y2):
                    x = x1 + step
                    y = y1 + step
                elif (x1 < x2) and (y1 > y2):
                    x = x1 + step
                    y = y1 - step
                elif (x1 > x2) and (y1 < y2):
                    x = x1 - step
                    y = y1 + step
                elif (x1 > x2) and (y1 > y2):
                    x = x1 - step
                    y = y1 - step
                else:
                    assert False

            min_x = min([min_x, x])
            max_x = max([max_x, x])
            min_y = min([min_y, y])
            max_y = max([max_y, y])

            grid[(x, y)] = grid.get((x, y), 0) + 1

    return grid, (min_x, max_x, min_y, max_y)


def sol1(lines):
    data = [list(map(int, re.findall(r"\d+", line))) for line in lines]
    only_horizontal_and_vertical = filter(
        lambda it: it[0] == it[2] or it[1] == it[3], data
    )
    grid, limits = populate_grid(list(only_horizontal_and_vertical))
    print_grid(grid, limits)
    points = [x for x in grid.values() if x > 1]
    return len(points)


def sol2(lines):
    entries = [list(map(int, re.findall(r"\d+", line))) for line in lines]
    grid, limits = populate_grid(entries)
    print_grid(grid, limits)
    points = [x for x in grid.values() if x > 1]
    return len(points)


def samples():
    with open("day05-sample.input", "r", encoding="utf8") as f:
        sample = f.readlines()
    assert sol1(sample) == 5
    assert sol2(sample) == 12


def solve_1(x):
    res = sol1(x)
    print(f"part 1: {res}")
    assert res == 8622


def solve_2(x):
    res = sol2(x)
    print(f"part 2: {res}")
    assert res == 22037


if __name__ == "__main__":
    with open("day05.input", "r", encoding="utf8") as f:
        inp = f.readlines()
    sys.exit(
        aoc_runner.aoc_runner(
            samples,
            solve_1,
            solve_2,
            inp,
        )
    )
