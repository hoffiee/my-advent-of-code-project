import re
import sys
from functools import cache

from libs.python.aoc_runner import aoc_runner


def read_and_parse_lines(filename):
    with open(filename, "r", encoding="utf8") as f:
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


class Counter:
    def __init__(self, inp):
        inp = list(map(lambda x: x.replace(" bags", ""), inp))
        inp = list(map(lambda x: x.replace(" bag", ""), inp))
        inp = list(map(lambda x: x.replace(".", ""), inp))
        inp = list(map(lambda x: x.split("contain"), inp))
        inp = list(map(lambda x: [x[0][:-1], x[1].split(",")], inp))

        self.relations = {}
        for [bag, subbags] in inp:
            self.relations[bag] = []
            if "no other" in subbags[0]:
                continue
            for subbag in subbags:
                match = re.match(r".*(\d)\s+(.*)", subbag)
                if match:
                    digit = int(match.group(1))
                    rest = match.group(2)
                else:
                    assert False
                self.relations[bag] = [*self.relations[bag], (digit, rest)]


    @cache
    def count_bags(self, root_bag):
        assert root_bag in self.relations

        if len(self.relations[root_bag]) == 0:
            return 1

        count: int = 1
        for nr_of_bags, subbag in self.relations[root_bag]:
            bags = self.count_bags(subbag)
            count += nr_of_bags*self.count_bags(subbag)

        return count


def sol2(inp):
    counter = Counter(inp)
    # Each depth includes itself, question specified how many bags shiny gold
    # contains so deduct one.
    out = counter.count_bags("shiny gold") - 1
    return out


def samples() -> None:
    sam = read_and_parse_lines("day07-sample.input")
    assert sol1(sam) == 4
    assert sol2(sam) == 32

    sam1 = read_and_parse_lines("day07-sample-1.input")
    assert sol2(sam1) == 126


if __name__ == "__main__":
    inp = read_and_parse_lines("day07.input")
    sys.exit(
        aoc_runner.aoc_runner(
            samples,
            lambda x: print(f"problem 1: {sol1(x)}"),
            lambda x: print(f"problem 2: {sol2(x)}"),
            inp,
        )
    )
