import sys

from libs.aoc_runner.python import aoc_runner


def read_and_parse_lines(filename):
    with open(filename, "r", encoding="utf8") as f:
        lines = f.readlines()
        f.close()
    out = list(map(int, lines))
    return out


def valid(l):
    n = l[-1]
    l = l[:-1]
    la = list(map(lambda x: n - x, l))
    if len(list(set(l) & set(la))) == 0:
        return n
    return None


def sol1(lines, pre):
    for i in range(len(lines) - pre):
        n = valid(lines[i : i + pre + 1])
        if n:
            return n
    return None


def sol2(lines, pre):
    xn = sol1(lines, pre)

    # caterpillar crawl or whatever it's called.
    s, e = 0, 1
    while True:
        a = sum(lines[s:e])
        if a == xn:
            return min(lines[s:e]) + max(lines[s:e])
        if a > xn:
            s += 1
        else:
            e += 1


def samples() -> None:
    sam = read_and_parse_lines("day09-sample.input")
    assert sol1(sam, 5) == 127
    assert sol2(sam, 5) == 62


if __name__ == "__main__":
    inp = read_and_parse_lines("day09.input")
    sys.exit(
        aoc_runner.aoc_runner(
            samples,
            lambda x: print(f"problem 1: {sol1(x, 25)}"),
            lambda x: print(f"problem 2: {sol2(x, 25)}"),
            inp,
        )
    )
