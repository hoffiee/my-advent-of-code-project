def read_and_parse_lines(filename):
    with open(filename, "r") as f:
        lines = f.readlines()
        f.close()
    out = list(map(str.strip, lines))
    return out


def find_seat(l):
    rows = [i for i in range(128)]
    cols = [i for i in range(8)]

    for c in l:
        ci = int(len(rows) / 2)
        ri = int(len(cols) / 2)
        if c == "F":
            rows = rows[0:ci]
        elif c == "B":
            rows = rows[ci:]
        elif c == "R":
            cols = cols[ri:]
        elif c == "L":
            cols = cols[0:ri]

    return (*rows, *cols)


def sids(lines):
    s = []
    for l in lines:
        r, c = find_seat(l)
        s.append(r * 8 + c)
    return s


def sol1(lines):
    return max(sids(lines))


def sol2(lines):
    s = sids(lines)
    seats = list(range(min(s), max(s)))
    out = list(set(seats) - set(s))
    return out[0]


def main() -> None:
    sam = read_and_parse_lines("day05-sample.input")
    inp = read_and_parse_lines("day05.input")

    print(f"sample 1: {sol1(sam)}")
    print(f"solut. 1: {sol1(inp)}")
    print(f"solut. 2: {sol2(inp)}")


if __name__ == "__main__":
    main()
