import re


def read_and_parse_lines(filename):
    with open(filename, "r") as f:
        lines = f.readlines()
        f.close()
    out = list(map(str.strip, lines))
    return out


def sol1(inp):
    inp = list(map(lambda x: x.split("contain"), inp))
    inp = list(map(lambda x: [x[0], x[1].split(",")], inp))

    sr = {"shiny gold bag"}
    while True:
        sz = len(sr)
        for l in inp:
            new = set()
            for s in sr:
                if any(map(lambda x: s in x, l[1])):
                    new.add(l[0].replace("bags", "bag").rstrip())
                    break
            sr = sr.union(new)
        if sz == len(sr):
            break
    return len(sr) - 1


def sol2(inp):
    inp = list(map(lambda x: x.replace("bags", "bag"), inp))
    inp = list(map(lambda x: x.replace(".", ""), inp))
    inp = list(map(lambda x: x.split("contain"), inp))
    inp = list(map(lambda x: [x[0][:-1], x[1].split(",")], inp))

    d = dict()
    for l in inp:
        nl = dict()
        for n in l[1]:
            if "no other bag" in n:
                nl = 0
            else:
                nr = [int(s) for s in n.split() if s.isdigit()][0]
                nl.update({re.sub(r"[0-9]+", "", n).lstrip(): nr})
        d.update({l[0]: nl})

    for k, v in d.items():
        print(f"{k}: {v}")

    dnew = {}
    while True:
        for top_bag, top_content in d.items():
            if not type(top_content) == int:
                dn = dict()
                for kk, vv in top_content.items():
                    print(
                        f"top_bag: {top_bag}, top_content: {top_content}, kk: {kk}, vv: {vv}"
                    )

                    if not type(d[kk]) == int:
                        for ins_bag, ins_v in d[kk].items():
                            print(
                                f"bag: {kk}, mult: {vv}, ins_bag: {ins_bag}, ins_v: {ins_v}"
                            )

            d[top_bag] = dn

        break

    print()
    for k, v in d.items():
        print(f"{k}: {v}")

    return 0


def main() -> None:
    sam = read_and_parse_lines("day07-sample.input")
    inp = read_and_parse_lines("day07.input")

    print(f"sample 1:\t{sol1(sam)}")
    print(f"solution 1:\t{sol1(inp)}")
    print(f"sample 2:\t{sol2(sam)}")
# print(f"solution 2:\t{sol2(inp)},\tcorrect: ?")

if __name__ == "__main__":
    main()
