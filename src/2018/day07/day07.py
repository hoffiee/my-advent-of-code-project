from collections import defaultdict
from typing import List
from icecream import ic
import sys

from libs.aoc_runner.python import aoc_runner


class Tree:
    def __init__(self, data):
        self.sequence = None
        graph = defaultdict(list)
        self.dependencies = defaultdict(list)
        for line in data:
            tmp = line.split()
            node = tmp[1]
            self.dependency = tmp[7]
            graph[node].append(self.dependency)
            # Create entry for all nodes, default dict enables this.
            self.dependencies[node]  # pylint: disable=pointless-statement
            self.dependencies[self.dependency].append(node)
        self.graph = {key: value[:] for key, value in self.dependencies.items()}

    def reset(self) -> None:
        self.dependencies = {key: value[:] for key, value in self.graph.items()}

    def __len__(self) -> int:
        return len(self.dependencies)

    def complete(self, node) -> None:
        assert len(self.dependencies[node]) == 0
        self.dependencies.pop(node)
        for key in self.dependencies.keys():
            if node in self.dependencies[key]:
                self.dependencies[key].remove(node)

    def get_sequence(self) -> str:
        if self.sequence is not None:
            return self.sequence

        next_candidates = self.get_available()
        self.sequence = ""
        while len(next_candidates) > 0:
            next_candidate = next_candidates.pop(0)
            self.complete(next_candidate)
            next_candidates = self.get_available()
            self.sequence += next_candidate[0]
        self.reset()
        return self.sequence

    def print(self) -> None:
        ic(self.dependencies)

    def get_available(self) -> List[str]:
        out = []
        for key, value in self.dependencies.items():
            if len(value) == 0:
                out.append(key)
        return sorted(out)


def sol1(lines):
    tree = Tree(lines)
    return tree.get_sequence()


def sol2(lines):
    tree = Tree(lines)
    sequence = tree.get_sequence()

    # Don't like doing this, but from the sequence length we see that we're doing the example where the
    # amount of workers and extra time is altered.
    nr_of_workers = 5
    extra_time = 60
    if len(sequence) == 6:
        nr_of_workers = 2
        extra_time = 0

    ongoing = []
    for step in range(2000):
        for order in ongoing.copy():
            complete_time, letter = order
            if step >= complete_time:
                ongoing.remove(order)
                tree.complete(letter)

        if len(ongoing) == 0 and len(tree) == 0:
            return step

        # If all workers are occupied, nothing to do
        if len(ongoing) == nr_of_workers or len(tree.get_available()) == 0:
            continue

        available_workers = nr_of_workers - len(ongoing)

        # get available and filter out those already in work queue
        available = tree.get_available()
        available = [
            key for key in available if key not in [value for key, value in ongoing]
        ]
        new_orders = min([available_workers, len(available)])

        for i in range(new_orders):
            letter = available[i]
            ongoing.append((ord(letter) - 64 + step + extra_time, letter))

    return 0


def samples():
    with open("day07-sample.input", "r", encoding="utf8") as f:
        sample = f.read().splitlines()
    assert sol1(sample) == "CABDFE"
    assert sol2(sample) == 15


def solve_1(x):
    res = sol1(x)
    print(f"part 1: {res}")
    assert res == "EUGJKYFQSCLTWXNIZMAPVORDBH"


def solve_2(x):
    res = sol2(x)
    print(f"part 2: {res}")
    assert res == 1014


if __name__ == "__main__":
    with open("day07.input", "r", encoding="utf8") as f:
        inp = list(map(str.rstrip, f.readlines()))
    sys.exit(
        aoc_runner.aoc_runner(
            samples,
            solve_1,
            solve_2,
            inp,
        )
    )
