import sys

from libs.aoc_runner.python import aoc_runner


def update(td, turn, num):
    n = td.get(num)

    if n:
        # does not exist
        td.update({num: turn})
    elif len(n) == 1:
        # only one item exist, append item.
        td[num].append(turn)
    elif len(n) == 2:
        # two exists, remove first and append
        td[num].append(turn)
        td[num].pop()

    return td


def sol(l, turns):
    td = {}
    new_n = 0
    for i in range(1, turns + 1):
        if i <= len(l):
            td.update({l[i - 1]: [i]})
            last_num = l[i - 1]
        else:
            n = td.get(last_num)

            if n is None:
                # first time, new number is 0
                new_n = 0
            elif len(n) == 1:
                # first time, new number is 0
                new_n = 0
            elif len(n) == 2:
                # second time, new number is difference
                new_n = td[last_num][1] - td[last_num][0]

            curr = td.get(new_n)
            if curr is None:
                td.update({new_n: [i]})
            elif len(curr) == 1:
                td[new_n].append(i)
            elif len(curr) == 2:
                td[new_n].append(i)
                td[new_n].pop(0)

            last_num = new_n

            if i == turns:
                return new_n
    return new_n


def samples() -> None:
    assert sol([0, 3, 6], 2020) == 436
    assert sol([1, 3, 2], 2020) == 1
    assert sol([2, 1, 3], 2020) == 10
    assert sol([1, 2, 3], 2020) == 27
    assert sol([2, 3, 1], 2020) == 78
    assert sol([3, 2, 1], 2020) == 438
    assert sol([3, 1, 2], 2020) == 1836

    assert sol([0, 3, 6], 30000000) == 175594
    assert sol([1, 3, 2], 30000000) == 2578
    assert sol([2, 1, 3], 30000000) == 3544142
    assert sol([1, 2, 3], 30000000) == 261214
    assert sol([2, 3, 1], 30000000) == 6895259
    assert sol([3, 2, 1], 30000000) == 18
    assert sol([3, 1, 2], 30000000) == 362


def solve_1(x):
    res = sol(x, 2020)
    print(f"part 1: {res}")
    assert res == 232


def solve_2(x):
    res = sol(x, 30000000)
    print(f"part 2: {res}")
    assert res == 18929178


if __name__ == "__main__":
    inp = [2, 1, 10, 11, 0, 6]
    sys.exit(
        aoc_runner.aoc_runner(
            samples,
            solve_1,
            solve_2,
            inp,
        )
    )
