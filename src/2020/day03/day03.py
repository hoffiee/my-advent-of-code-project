import sys

from libs.aoc_runner.python import aoc_runner


def sol1(m, p) -> int:
    c, v, h = 0, 0, 0
    while True:
        h = (h + p[0]) % len(m[0])
        v += p[1]
        if v >= len(m):
            break
        if m[v][h] == "#":
            c += 1
    return c


def sol2(m) -> int:
    ps = [[1, 1], [3, 1], [5, 1], [7, 1], [1, 2]]
    r = 1
    for p in ps:
        r *= sol1(m, p)
    return r


def samples():
    with open("day03-sample.input", "r", encoding="utf8") as f:
        sample = list(map(str.rstrip, f.readlines()))
    assert sol1(sample, [3, 1]) == 7
    assert sol2(sample) == 336


def solve_1(x):
    res = sol1(x, [3, 1])
    print(f"part 1: {res}")
    assert res == 244


def solve_2(x):
    res = sol2(x)
    print(f"part 2: {res}")
    assert res == 9406609920


if __name__ == "__main__":
    with open("day03.input", "r", encoding="utf8") as f:
        inp = list(map(str.rstrip, f.readlines()))
    sys.exit(
        aoc_runner.aoc_runner(
            samples,
            solve_1,
            solve_2,
            inp,
        )
    )
