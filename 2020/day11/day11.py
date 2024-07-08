def read_and_parse_lines(filename):
    with open(filename, "r", encoding="utf8") as f:
        lines = f.readlines()
        f.close()
    out = list(map(str.strip, lines))
    out = list(map(list, out))
    return out


def change_seat_adj(s, r, c):
    rmax = len(s) - 1
    cmax = len(s[0]) - 1

    # Center
    if (0 < r < rmax) and (0 < c < cmax):
        adj = [
            s[r - 1][c - 1],
            s[r - 1][c],
            s[r - 1][c + 1],
            s[r][c - 1],
            s[r][c + 1],
            s[r + 1][c - 1],
            s[r + 1][c],
            s[r + 1][c + 1],
        ]

    # edges
    elif r == 0 and (0 < c < cmax):
        adj = [s[r][c - 1], s[r][c + 1], s[r + 1][c - 1], s[r + 1][c], s[r + 1][c + 1]]
    elif r == rmax and (0 < c < cmax):
        adj = [s[r - 1][c - 1], s[r - 1][c], s[r - 1][c + 1], s[r][c - 1], s[r][c + 1]]
    elif (0 < r < rmax) and c == 0:
        adj = [s[r - 1][c], s[r - 1][c + 1], s[r][c + 1], s[r + 1][c], s[r + 1][c + 1]]
    elif (0 < r < rmax) and c == cmax:
        adj = [s[r - 1][c - 1], s[r - 1][c], s[r][c - 1], s[r + 1][c - 1], s[r + 1][c]]

    # corner
    elif r == 0 and c == 0:
        adj = [s[r][c + 1], s[r + 1][c], s[r + 1][c + 1]]

    elif r == 0 and c == cmax:
        adj = [s[r][c - 1], s[r + 1][c - 1], s[r + 1][c]]
    elif r == rmax and c == 0:
        adj = [s[r - 1][c], s[r - 1][c + 1], s[r][c + 1]]
    elif r == rmax and c == cmax:
        adj = [s[r - 1][c - 1], s[r - 1][c], s[r][c - 1]]
    # faulty
    else:
        adj = ["F"]

    if s[r][c] == "L" and adj.count("#") == 0:
        return "#", True
    if s[r][c] == "#" and adj.count("#") >= 4:
        return "L", True
    return s[r][c], False


def print_seats(l):
    for r in l:
        for s in r:
            print(s, end="")
        print()

def sol1(lines):
    while True:
        cont = False
        nl = list(map(list, lines))
        for r in range(len(lines)):
            for c in range(len(lines[0])):
                nl[r][c], changed = change_seat_adj(lines, r, c)
                if changed:
                    cont = changed
        lines = list(map(list, nl))
        if not cont:
            break

    return sum(l.count("#") for l in lines)


def sol2(lines):
    while True:
        cont = False
        nl = list(map(list, lines))
        for r in range(len(lines)):
            for c in range(len(lines[0])):
                nl[r][c], changed = change_seat_adj(lines, r, c)
                if changed:
                    cont = changed
        lines = list(map(list, nl))
        print_seats(lines)
        if not cont:
            break
        break

    return sum(l.count("#") for l in lines)


def main() -> None:
    sam = read_and_parse_lines("day11-sample.input")
    inp = read_and_parse_lines("day11.input")

    print(f"sample 1: {sol1(sam)}\tcorrect: 37")
    print(f"solut. 1: {sol1(inp)}\tcorrect: 2254")
    print(f"solut. 2: {sol2(sam)}")


if __name__ == "__main__":
    main()
