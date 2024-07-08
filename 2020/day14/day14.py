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
    # print(lines)

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


def main() -> None:
    sam = read_and_parse_lines("day14-sample.input")
    inp = read_and_parse_lines("day14.input")

    print(f"sample 1: {sol1(sam)}\tcorrect: 165")
    print(f"solut. 1: {sol1(inp)}\tcorrect: 8566770985168")


if __name__ == "__main__":
    main()
