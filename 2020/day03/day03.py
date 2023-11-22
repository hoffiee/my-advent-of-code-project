def sol1(m, p) -> int:
    c, v, h = 0, 0, 0
    while True:
        h = (h + p[0]) % len(m[0])
        v += p[1]
        if v >= len(m):
            break
        if m[v][h] == "#":
            c += 1
    return c


def sol2(m, ps) -> int:
    r = 1
    for p in ps:
        r *= sol1(m, p)
    return r

def main() -> None:
    with open("day03-sample.input", "r") as f:
        sample = list(map(str.rstrip, f.readlines()))

    with open("day03.input", "r") as f:
        puzzle = list(map(str.rstrip, f.readlines()))
    ps = [[1, 1], [3, 1], [5, 1], [7, 1], [1, 2]]

    print(f"sample 1:\ttrees:\t{sol1(sample, [3,1])}")
    print(f"solution 1:\ttrees:\t{sol1(puzzle, [3,1])}")
    print(f"sample 2:\tmult:\t{sol2(sample, ps)}")
    print(f"solution 2:\tmult:\t{sol2(puzzle, ps)}")

if __name__ == "__main__":
    main()
