"""
Found out python introduced structural pattern matching, so I used that for solution 1

Had some issues with my own solution for part 2, and then read some hints and found that a DFS
and assuming the first encounter of a branch weight is correct, we can continue until we find one that
doesn't meet our assumption. I then added so that my algorithm shuffles the children at each step so
that it founds it.
"""

import random
import statistics
from collections import defaultdict
import sys

from libs.python.aoc_runner import aoc_runner


def sol1(data):
    """Create a tree where each entry points to it's parent. Then look for an entry that doesn't have a parent"""
    tree = defaultdict(str)
    for datum in data:
        match datum.replace(",", "").split(" "):
            case [node, _, "->", *childrens]:
                if node not in tree:
                    tree[node] = ""
                for child in childrens:
                    tree[child] = node
            case [node, _]:
                pass
    for k, v in tree.items():
        if v == "":
            return k
    return ""


class DFS:
    def __init__(self):
        self.found = False
        self.corrected_weight = 0

    def reset(self):
        self.found = False
        self.corrected_weight = 0

    def dfs(self, children, weights, root):
        expected = None
        program_weight = weights[root]
        random.shuffle(children[root])
        for child in children[root]:
            weight = self.dfs(children, weights, child)
            program_weight += weight
            # We pick the first child as an expected weight, if any of the following children have a different weight
            # then we've identified a faulty child, it could be the one we picked as expected or it could be the
            # following ones we checked. This is why we rerun this with shuffled children in order to find the faulty
            # one, there are only 1 faulty and we often have more than one children, therefore we should more often
            # pick a non-faulty one as expected.
            if expected is None:
                expected = weight
            elif not self.found and expected != weight:
                self.corrected_weight = weights[child] - (weight - expected)
                self.found = True
        return program_weight


def sol2(data):
    root = sol1(data)

    weights = {}
    children = defaultdict(list)

    for datum in data:
        datum = datum.strip().split()

        node = datum[0]
        weights[node] = int(datum[1].strip("()"))

        if "->" in datum:
            children[node] = [child.strip(",") for child in datum[3:]]

    # Due to randomly choosing correct value, we run this a few times so that we can
    # see which value occurs more than once
    solver = DFS()
    corrected_weights = []
    for _ in range(10):
        solver.reset()
        solver.dfs(children, weights, root)
        corrected_weights.append(solver.corrected_weight)
    return int(statistics.median(corrected_weights))


def samples():
    with open("day07-sample.input", "r", encoding="utf8") as file:
        sample = file.read().splitlines()

    assert sol1(sample) == "tknk"
    assert sol2(sample) == 60


if __name__ == "__main__":
    with open("day07.input", "r", encoding="utf8") as file:
        inp = file.read().splitlines()
    sys.exit(
        aoc_runner.aoc_runner(
            samples,
            lambda x: print(f"problem 1: {sol1(x)}"),
            lambda x: print(f"problem 2: {sol2(x)}"),
            inp,
        )
    )
