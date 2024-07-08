import math as m
import numpy as np


def read_and_parse_lines(filename):
    with open(filename, "r", encoding="utf8") as f:
        lines = f.readlines()
        f.close()
    out = list(map(str.strip, lines))
    out[1] = out[1].split(",")
    return out


def sol1(lines):
    ts = int(lines[0])

    # clear out buses not in service
    buss_id = list(map(int, filter("x".__ne__, lines[1])))

    mult = list(map(lambda x: m.ceil(ts / x), buss_id))
    next_buss = [mult[i] * buss_id[i] for i in range(len(mult))]
    diff = list(map(lambda x: max(0, x), [buss - ts for buss in next_buss]))
    earliest_departure = min(diff)
    earliest_buss_id = buss_id[diff.index(earliest_departure)]

    return earliest_departure * earliest_buss_id


def sol2(lines):
    bi = []
    tf = []
    for i in range(len(lines[1])):
        if not lines[1][i] == "x":
            bi.append(int(lines[1][i]))
            tf.append(i)

    print(bi)
    print(tf)

    bi_vec = np.array(bi)
    tf_vec = np.array(tf)

    print(tf_vec / bi_vec)


def main() -> None:
    sam = read_and_parse_lines("day13-sample.input")
    inp = read_and_parse_lines("day13.input")

    print(f"sample 1: {sol1(sam)}\tcorrect: 295")
    print(f"solut. 1: {sol1(inp)}\tcorrect: 2305")
    print(f"sample 1: {sol2(sam)}\tcorrect: 286")


if __name__ == "__main__":
    main()
