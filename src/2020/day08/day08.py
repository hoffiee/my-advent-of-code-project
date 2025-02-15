import sys

from libs.python.aoc_runner import aoc_runner


def read_and_parse_lines(filename):
    with open(filename, "r", encoding="utf8") as f:
        lines = f.readlines()
        f.close()
    out = list(map(str.strip, lines))
    out = list(map(str.split, out))
    return out


def sol1(lines):
    i = 0
    c = 0
    acc = 0
    while i < len(lines):
        c += 1
        if lines[i][0] == "nop" and len(lines[i]) < 3:
            lines[i].append("nop: " + str(c))
            i += 1
        elif lines[i][0] == "acc" and len(lines[i]) < 3:
            lines[i].append("acc: " + str(c))
            if lines[i][1][0] == "+":
                acc += int(lines[i][1][1:])
            else:
                acc -= int(lines[i][1][1:])
            i += 1
        elif lines[i][0] == "jmp" and len(lines[i]) < 3:
            lines[i].append("jmp: " + str(c))
            if lines[i][1][0] == "+":
                i += int(lines[i][1][1:])
            else:
                i -= int(lines[i][1][1:])
        elif len(lines[i]) == 3:
            break

    return acc


def sol2(lines):
    # Remains to do and investigate a bit further.

    i = 0
    ii = 0
    c = 0
    acc = 0
    while i < len(lines):
        c += 1
        if len(lines[i]) >= 3:
            break

        match lines[i][0]:
            case "nop":
                lines[i].append("nop: " + str(c))
                i += 1
            case "acc":
                lines[i].append("acc: " + str(c))
                if lines[i][1][0] == "+":
                    acc += int(lines[i][1][1:])
                else:
                    acc -= int(lines[i][1][1:])
                i += 1
            case "jmp":
                lines[i].append("jmp: " + str(c))
                if lines[i][1][0] == "+":
                    ii += int(lines[i][1][1:])
                else:
                    ii -= int(lines[i][1][1:])

                if len(lines[ii]) == 3:
                    lines[i][0] = "nop"
                else:
                    i = ii
            case _:
                assert False

    for lm in lines:
        print(lm)

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
