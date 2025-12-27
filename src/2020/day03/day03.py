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


if __name__ == "__main__":
    with open("day03.input", "r", encoding="utf8") as f:
        inp = list(map(str.rstrip, f.readlines()))
    sys.exit(
        aoc_runner.aoc_runner(
            samples,
            lambda x: print(f"problem 1: {sol1(x, [3,1])}"),
            lambda x: print(f"problem 2: {sol2(x)}"),
            inp,
        )
    )
