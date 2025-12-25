import hashlib
import sys

from libs.aoc_runner.python import aoc_runner


def solve(key: str, zeroes: int) -> int:
    for i in range(int(1e9)):
        test = hashlib.md5(f"{key}{i}".encode()).hexdigest()
        if test[:zeroes] == "0" * zeroes:
            return i
    return 0


def samples():
    assert solve("abcdef", 5) == 609043
    assert solve("pqrstuv", 5) == 1048970


if __name__ == "__main__":
    inp = "iwrupvqb"
    sys.exit(
        aoc_runner.aoc_runner(
            samples,
            lambda x: print(f"problem 1: {solve(x, 5)}"),
            lambda x: print(f"problem 2: {solve(x, 6)}"),
            inp,
        )
    )
