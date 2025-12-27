import collections
from typing import List, Tuple
import sys

from libs.aoc_runner.python import aoc_runner


def sol1(data: List[Tuple[str, ...]]) -> None:
    out: str = ""
    for it in data:
        k, _ = collections.Counter(it).most_common(1)[0]
        out += k
    return out


def sol2(data: List[Tuple[str, ...]]) -> None:
    out: str = ""
    for it in data:
        d = dict(collections.Counter(it))
        out += min(d, key=d.get)
    return out


def samples():
    with open("day06-sample.input", "r", encoding="utf8") as file:
        lines = file.read().splitlines()
        transposed = list(zip(*lines))
    assert sol1(transposed) == "easter"
    assert sol2(transposed) == "advent"


if __name__ == "__main__":
    with open("day06.input", "r", encoding="utf8") as file:
        lines = file.read().splitlines()
        # neat way of transposing data
        transposed = list(zip(*lines))

    sys.exit(
        aoc_runner.aoc_runner(
            samples,
            lambda x: print(f"problem 1: {sol1(x)}"),
            lambda x: print(f"problem 2: {sol2(x)}"),
            transposed,
        )
    )
