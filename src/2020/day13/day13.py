import math as m
import numpy as np
import sys

from libs.python.aoc_runner import aoc_runner


def read_and_parse_lines(filename):
    with open(filename, "r", encoding="utf8") as f:
        lines = f.readlines()
        f.close()
    out = list(map(str.strip, lines))
    out[1] = out[1].split(",")
    return out


def sol1(lines):
    ts = int(lines[0])

    # clear out buses not in service
    buss_id = list(map(int, filter("x".__ne__, lines[1])))

    mult = list(map(lambda x: m.ceil(ts / x), buss_id))
    next_buss = [mult[i] * buss_id[i] for i in range(len(mult))]
    diff = list(map(lambda x: max(0, x), [buss - ts for buss in next_buss]))
    earliest_departure = min(diff)
    earliest_buss_id = buss_id[diff.index(earliest_departure)]

    return earliest_departure * earliest_buss_id


def sol2(lines):
    # So we're looking for
    # x     = n1*x1
    # x + 1 = n2*x2
    # x + 2 = n3*x3
    # ...
    # for all busses (excluding some)

    # Set up as linear system of Diophantine equations
    # x = ai + ni*xi   v i in [1, ..., k]
    # where ni, are pairwise coprime integers, in this case the bus id/period
    # where x is the common timestamp base
    # ai is the offset to the timestamp for each bus
    # xi is the amount of times the bus has gone.
    # And let's use the Direct construction for Chinese remainder theorem.

    # https://en.wikipedia.org/wiki/Diophantine_equation#Chinese_remainder_theorem
    # https://en.wikipedia.org/wiki/Chinese_remainder_theorem
    # https://cp-algorithms.com/algebra/linear-diophantine-equation.html
    ni = []
    ai = []
    for i in range(len(lines[1])):
        if not lines[1][i] == "x":
            ni.append(int(lines[1][i]))
            ai.append(-i)
    nvec = np.array(ni)

    # Product of all moduli
    N = np.prod(nvec)

    out = 0
    for i in range(len(ni)):
        # product of all moduli but one
        Ni = N // ni[i]

        # Find modular multiplicative inverse:
        # Ni*Mi = 1   mod m
        # https://cp-algorithms.com/algebra/module-inverse.html
        Mi = 1
        while Ni * Mi % ni[i] != 1:
            Mi += 1

        out += ai[i] * Ni * Mi

    out %= N
    return out


def samples() -> None:
    sam = read_and_parse_lines("day13-sample.input")
    assert sol1(sam) == 295

    sam1 = read_and_parse_lines("day13-sample-1.input")
    assert sol2(sam1) == 3417

    sam2 = read_and_parse_lines("day13-sample-2.input")
    assert sol2(sam2) == 754018

    sam3 = read_and_parse_lines("day13-sample-3.input")
    assert sol2(sam3) == 779210

    sam4 = read_and_parse_lines("day13-sample-4.input")
    assert sol2(sam4) == 1261476

    sam5 = read_and_parse_lines("day13-sample-5.input")
    assert sol2(sam5) == 1202161486
    assert sol2(sam) == 1068781


if __name__ == "__main__":
    inp = read_and_parse_lines("day13.input")
    sys.exit(
        aoc_runner.aoc_runner(
            samples,
            lambda x: print(f"problem 1: {sol1(x)}"),
            lambda x: print(f"problem 2: {sol2(x)}"),
            inp,
        )
    )
