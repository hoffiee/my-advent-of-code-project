import time


def read_and_parse_lines(filename):
    with open(filename, "r") as f:
        lines = f.readlines()
        f.close()
    out = list(map(int, lines))
    return out


def valid(l):
    n = l[-1]
    l = l[:-1]
    la = list(map(lambda x: n - x, l))
    if len(list(set(l) & set(la))) == 0:
        return n
    return


def sol1(lines, pre):
    for i in range(len(lines) - pre):
        n = valid(lines[i : i + pre + 1])
        if n:
            return n
    return


def sol2(lines, pre):
    xn = sol1(lines, pre)

    # caterpillar crawl or whatever it's called.
    s, e = 0, 1
    while True:
        a = sum(lines[s:e])
        if a == xn:
            return min(lines[s:e]) + max(lines[s:e])
        elif a > xn:
            s += 1
        else:
            e += 1


def main() -> None:
    sam = read_and_parse_lines("day09-sample.input")
    inp = read_and_parse_lines("day09.input")


    print(f"sample 1:\t{sol1(sam, 5)}\t\tcorrect: 127")
    print(f"solution 1:\t{sol1(inp, 25)}\tcorrect: 1124361034")
    print(f"sample 2:\t{sol2(sam, 5)},\t\tcorrect: 62")
    print(f"solution 2.1:\t{sol2(inp, 25)}\tcorrect: 129444555")


if __name__ == "__main__":
    main()
