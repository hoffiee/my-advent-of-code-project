import sys
from functools import reduce

from libs.aoc_runner.python import aoc_runner


def read_and_split_into_groups(filename):
    return [
        s.split("\n")
        for s in open(filename, "r", encoding="utf8").read().rstrip().split("\n\n")
    ]


def split_group_into_list(g):
    out = []
    for gi in g:
        out = out + list(gi)
    return out


def group_to_list_of_sets(grp):
    return [set(list(a)) for a in grp]


def common_ans(g):
    return list(reduce(lambda a, b: a.intersection(b), g))


def sol1(grps):
    grps_answers = [split_group_into_list(g) for g in grps]
    grps_yes_count = [len(set(g)) for g in grps_answers]
    return sum(grps_yes_count)


def sol2(grps):
    out = [group_to_list_of_sets(g) for g in grps]
    out = [len(common_ans(g)) for g in out]
    return sum(out)


def samples() -> None:
    sam = read_and_split_into_groups("day06-sample.input")
    assert sol1(sam) == 11
    assert sol2(sam) == 6


def solve_1(x):
    res = sol1(x)
    print(f"part 1: {res}")
    assert res == 6170


def solve_2(x):
    res = sol2(x)
    print(f"part 2: {res}")
    assert res == 2947


if __name__ == "__main__":
    inp = read_and_split_into_groups("day06.input")
    sys.exit(
        aoc_runner.aoc_runner(
            samples,
            solve_1,
            solve_2,
            inp,
        )
    )
