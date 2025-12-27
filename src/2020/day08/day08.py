import sys

from libs.aoc_runner.python import aoc_runner


def read_and_parse_lines(filename):
    with open(filename, "r", encoding="utf8") as f:
        lines = f.readlines()
        f.close()
    out = [tuple(line.strip().split()) for line in lines]
    return out


def parse_arg(arg):
    if arg[0] == "+":
        return int(arg[1:])
    return -int(arg[1:])


def solve(lines_in):
    lines = lines_in.copy()
    count = [0] * len(lines_in)
    i = 0
    acc = 0
    terminated = True
    while i < len(lines):
        if count[i] > 0:
            terminated = False
            break

        oper, arg = lines[i]
        if oper == "nop":
            count[i] += 1
            i += 1
        elif oper == "acc":
            count[i] += 1
            acc += parse_arg(arg)
            i += 1
        elif oper == "jmp":
            count[i] += 1
            i += parse_arg(arg)

    return acc, terminated


def sol1(lines_in):
    out, _ = solve(lines_in)
    return out


def sol2(lines_in):
    for i in range(len(lines_in)):
        lines = lines_in.copy()
        if lines[i][0] == "nop":
            lines[i] = ("jmp", lines[i][1])
        elif lines[i][0] == "jmp":
            lines[i] = ("nop", lines[i][1])
        acc, term = solve(lines)
        if term:
            break
    return acc


def samples() -> None:
    sam = read_and_parse_lines("day08-sample.input")
    assert sol1(sam) == 5
    assert sol2(sam) == 8


if __name__ == "__main__":
    inp = read_and_parse_lines("day08.input")
    sys.exit(
        aoc_runner.aoc_runner(
            samples,
            lambda x: print(f"problem 1: {sol1(x)}"),
            lambda x: print(f"problem 2: {sol2(x)}"),
            inp,
        )
    )
