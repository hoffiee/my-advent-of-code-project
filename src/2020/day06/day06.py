from functools import reduce


def read_and_split_into_groups(filename):
    return [
        s.split("\n")
        for s in open(filename, "r", encoding="utf8").read().rstrip().split("\n\n")
    ]


def split_group_into_list(g):
    out = []
    for gi in g:
        out = out + list(gi)
    return out


def group_to_list_of_sets(grp):
    return [set(list(a)) for a in grp]


def common_ans(g):
    return list(reduce(lambda a, b: a.intersection(b), g))


def sol1(grps):
    grps_answers = [split_group_into_list(g) for g in grps]
    grps_yes_count = [len(set(g)) for g in grps_answers]
    return sum(grps_yes_count)


def sol2(grps):
    out = [group_to_list_of_sets(g) for g in grps]
    out = [len(common_ans(g)) for g in out]
    return sum(out)


def main() -> None:
    sam = read_and_split_into_groups("day06-sample.input")
    inp = read_and_split_into_groups("day06.input")

    print(f"sample 1: {sol1(sam)}, correct: 11")
    print(f"solut. 1: {sol1(inp)}, correct: 6170")
    print(f"sample 2: {sol2(sam)}, correct: 6")
    print(f"solut. 2: {sol2(inp)}, correct: 2947")


if __name__ == "__main__":
    main()
