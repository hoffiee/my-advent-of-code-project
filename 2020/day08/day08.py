def read_and_parse_lines(filename):
    with open(filename, "r") as f:
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
    c = 0
    acc = 0
    while i < len(lines):
        c += 1
        # print(lines[i])
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
                ii += int(lines[i][1][1:])
            else:
                ii -= int(lines[i][1][1:])

            if len(lines[ii]) == 3:
                lines[i][0] = "nop"
            else:
                i = ii
        elif len(lines[i]) == 3:
            break
        else:
            print(f"kommer jag hit? {lines[i]}")

    for lm in lines:
        print(lm)

    return acc


def main() -> None:
    sam = read_and_parse_lines("day08-sample.input")
    inp = read_and_parse_lines("day08.input")

    print(f"sample 1:\t{sol1(sam)},\tcorrect: 5")
    print(f"solution 1:\t{sol1(inp)},\tcorrect: 1810")
    print(f"sample 2:\t{sol2(sam)},\tcorrect: ?")
# print(f"solution 2:\t{sol2(inp)},\tcorrect: ?")

if __name__ == "__main__":
    main()
