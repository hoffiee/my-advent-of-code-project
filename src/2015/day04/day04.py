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


def solve_1(x):
    res = solve(x, 5)
    print(f"part 1: {res}")
    assert res == 346386


def solve_2(x):
    res = solve(x, 6)
    print(f"part 2: {res}")
    assert res == 9958218


if __name__ == "__main__":
    inp = "iwrupvqb"
    sys.exit(
        aoc_runner.aoc_runner(
            samples,
            solve_1,
            solve_2,
            inp,
        )
    )
