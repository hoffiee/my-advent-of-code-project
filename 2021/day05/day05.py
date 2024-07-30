import re
from icecream import ic
import math as m

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

    grid = {}
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
                k = (y2 - y1) // (x2 - x1)
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

            min_x = min([min_x, x])
            max_x = max([max_x, x])
            min_y = min([min_y, y])
            max_y = max([max_y, y])

            grid[(x, y)] = grid.get((x, y), 0) + 1

    return grid, (min_x, max_x, min_y, max_y)


def sol1(data):
    only_horizontal_and_vertical = filter(
        lambda it: it[0] == it[2] or it[1] == it[3], data
    )
    grid, limits = populate_grid(list(only_horizontal_and_vertical))
    print_grid(grid, limits)
    points = [x for x in grid.values() if x > 1]
    print(f"solution 1:\t{len(points)}")


def sol2(entries):
    grid, limits = populate_grid(entries)
    print_grid(grid, limits)
    points = [x for x in grid.values() if x > 1]
    print(f"solution 2:\t{len(points)}")


def main() -> None:
    for file in ["day05-sample.input", "day05.input"]:
        f = open(file, "r", encoding="utf8")
        lines = f.readlines()

        data = [list(map(int, re.findall("\d+", line))) for line in lines]
        sol1(data)
        sol2(data)


if __name__ == "__main__":
    main()
