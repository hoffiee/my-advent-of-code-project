import sys

from libs.aoc_runner.python import aoc_runner


def read_and_parse_lines(filename):
    with open(filename, "r", encoding="utf8") as f:
        lines = f.readlines()
        f.close()
    out = list(map(str.strip, lines))
    out = list(map(list, out))
    return out


def print_seats(l):
    for r in l:
        for s in r:
            print(s, end="")
        print()
    print()


class Seats:
    def __init__(self, lines):
        self.seating = list(map(list, lines))
        self.sz_y = len(self.seating)
        self.sz_x = len(self.seating[0])

    def valid(self, pos):
        x, y = pos
        if y < 0 or self.sz_y <= y:
            return False
        if x < 0 or self.sz_x <= x:
            return False
        return True

    def __getitem__(self, pos):
        assert self.valid(pos)
        return self.seating[pos[1]][pos[0]]

    def update(self, seats):
        self.seating = list(map(list, seats))


dirs = [
    (
        -1,
        -1,
    ),
    (
        0,
        -1,
    ),
    (
        1,
        -1,
    ),
    (
        -1,
        0,
    ),
    (
        1,
        0,
    ),
    (
        -1,
        1,
    ),
    (
        0,
        1,
    ),
    (
        1,
        1,
    ),
]


def count_seats_1(seats: Seats, pos):
    x, y = pos
    count = 0
    for dir in dirs:
        dx, dy = dir
        cand = (x + dx, y + dy)
        if not seats.valid(cand):
            continue

        if seats[cand] == "#":
            count += 1

    return count


def count_seats_2(seats: Seats, pos):
    x, y = pos
    count = 0
    for dir in dirs:
        dx, dy = dir
        step = 1
        while seats.valid((x + step * dx, y + step * dy)):
            cand = seats[(x + step * dx, y + step * dy)]
            if cand in ["#", "L"]:
                count += int(cand == "#")
                break
            step += 1
    return count


def change_seat(seats: Seats, counter, threshold, pos):
    if seats[pos] == ".":
        return ".", False

    (x, y) = pos
    match seats[pos]:
        case "L":
            count = counter(seats, pos)
            if count == 0:
                return "#", True
            return "L", False
        case "#":
            count = counter(seats, pos)
            if count >= threshold:
                return "L", True
            return "#", False
        case ".":
            pass
        case _:
            assert False

    return seats[pos], False


def sol1(lines):
    seats = Seats(lines)
    while True:
        stop = True
        nl = list(map(list, seats.seating))
        for y in range(seats.sz_y):
            for x in range(seats.sz_x):
                if seats[(x, y)] == ".":
                    continue

                new, changed = change_seat(seats, count_seats_1, 4, (x, y))
                nl[y][x] = new
                if changed:
                    stop = False
        seats.update(nl)
        if stop:
            break

    return sum(l.count("#") for l in seats.seating)


def sol2(lines):
    seats = Seats(lines)
    while True:
        stop = True
        nl = list(map(list, seats.seating))
        for y in range(seats.sz_y):
            for x in range(seats.sz_x):
                if seats[(x, y)] == ".":
                    continue

                new, changed = change_seat(seats, count_seats_2, 5, (x, y))
                nl[y][x] = new
                if changed:
                    stop = False
        seats.update(nl)
        if stop:
            break

    return sum(l.count("#") for l in seats.seating)


def samples() -> None:
    inp = [
        ".......#.",
        "...#.....",
        ".#.......",
        ".........",
        "..#L....#",
        "....#....",
        ".........",
        "#........",
        "...#.....",
    ]
    assert count_seats_2(Seats(inp), (3, 4)) == 8

    inp = [
        ".............",
        ".L.L.#.#.#.#.",
        ".............",
    ]
    assert count_seats_2(Seats(inp), (1, 1)) == 0
    assert count_seats_2(Seats(inp), (3, 1)) == 1

    inp = [
        ".##.##.",
        "#.#.#.#",
        "##...##",
        "...L...",
        "##...##",
        "#.#.#.#",
        ".##.##.",
    ]
    assert count_seats_2(Seats(inp), (3, 3)) == 0

    sam = read_and_parse_lines("day11-sample.input")
    assert sol1(sam) == 37
    assert sol2(sam) == 26


def solve_1(x):
    res = sol1(x)
    print(f"part 1: {res}")
    assert res == 2254


def solve_2(x):
    res = sol2(x)
    print(f"part 2: {res}")
    assert res == 2004


if __name__ == "__main__":
    inp = read_and_parse_lines("day11.input")
    sys.exit(
        aoc_runner.aoc_runner(
            samples,
            solve_1,
            solve_2,
            inp,
        )
    )
