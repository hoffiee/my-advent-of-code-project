import sys

from libs.python.aoc_runner import aoc_runner


def read_and_parse_lines(filename):
    with open(filename, "r", encoding="utf8") as f:
        lines = f.readlines()
        f.close()
    out = list(map(str.strip, lines))
    return out


def maskit(val, masks):
    m1, m0 = masks
    return (val | m1) & m0


def create_mask(mask):
    mask = mask.replace("mask = ", "")
    masks = (int(mask.replace("X", "0"), 2), int(mask.replace("X", "1"), 2))
    return masks


def sol1(lines):
    mem = {}
    for l in lines:
        if "mask" in l:
            masks = create_mask(l)
        else:
            instr = l.replace("mem[", "").replace("] ", "").replace(" ", "")
            k, v = instr.split("=")
            mem.update({int(k): maskit(int(v), masks)})

    out = 0
    for _, v in mem.items():
        out += v

    return out


def sol2(lines):
    return 0


def samples() -> None:
    sam = read_and_parse_lines("day14-sample.input")
    assert sol1(sam) == 165


if __name__ == "__main__":
    inp = read_and_parse_lines("day14.input")
    sys.exit(
        aoc_runner.aoc_runner(
            samples,
            lambda x: print(f"problem 1: {sol1(x)}"),
            lambda x: print(f"problem 2: {sol2(x)}"),
            inp,
        )
    )
