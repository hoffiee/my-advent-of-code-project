import sys

from libs.aoc_runner.python import aoc_runner


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


def expand_masks(mask: str):
    results = [""]
    for char in mask:
        if char == "X":
            results = [r + bit for r in results for bit in "01"]
        else:
            results = [r + char for r in results]
    results = list(map(lambda x: int(x, 2), results))
    return results


def apply_mask(addr, mask):
    addr_bin = f"{addr:0{len(mask)}b}"
    masked = []
    for m, a in zip(mask, addr_bin):
        if m == "X":
            masked.append("X")  # Placeholder for expansion
        elif m in "1":
            masked.append(m)
        else:
            masked.append(a)
    return expand_masks("".join(masked))


def sol2(lines):
    mem = {}
    for l in lines:
        if "mask" in l:
            masks = l.split(" = ")[1]
        else:
            instr = l.replace("mem[", "").replace("] ", "").replace(" ", "")
            k, v = instr.split("=")
            for addr in apply_mask(int(k), masks):
                mem.update({addr: int(v)})

    out = 0
    for _, v in mem.items():
        out += v

    return out


def samples() -> None:
    sam = read_and_parse_lines("day14-sample.input")
    assert sol1(sam) == 165

    sam1 = read_and_parse_lines("day14-sample-1.input")
    assert sol2(sam1) == 208


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
