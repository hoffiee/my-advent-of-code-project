from collections import defaultdict
from typing import List
from icecream import ic


attempts_1 = [
    ("", ""),
]

attempts_2 = [
    (0, ""),
]


def suggest_solution(attempts, inp):
    for value, msg in attempts:
        if inp == value:
            print(f"{value}\t<-- {msg}")
            return
    print(inp)


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


def sol1(tree):
    return tree.get_sequence()


def sol2(tree):
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


def main() -> None:
    for filename in ["day07-sample.input", "day07.input"]:
        with open(filename, "r", encoding="utf8") as file:
            lines = file.read().splitlines()
            tree = Tree(lines)
            suggest_solution(attempts_1, sol1(tree))
            suggest_solution(attempts_2, sol2(tree))


if __name__ == "__main__":
    main()
