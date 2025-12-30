import hashlib
import sys

from libs.aoc_runner.python import aoc_runner


def sol1(key: str, zeroes: int = 5) -> str:
    out: str = ""
    for i in range(int(1e9)):
        test = hashlib.md5(f"{key}{i}".encode()).hexdigest()
        if test[:zeroes] == "0" * zeroes:
            out += str(test[5])
            if len(out) >= 8:
                return out
    return out


def sol2(key: str, zeroes: int = 5) -> str:
    out: str = "________"
    for i in range(int(1e9)):
        test = hashlib.md5(f"{key}{i}".encode()).hexdigest()
        if test[:zeroes] == "0" * zeroes:
            index = int(test[5], 16)
            if index > 7 or out[index] != "_":
                continue

            out = out[:index] + test[6] + out[index + 1 :]
            if "_" not in out:
                break
    return out


def samples():
    assert sol1("abc") == "18f47a30"
    assert sol2("abc") == "05ace8e3"


def solve_1(x):
    res = sol1(x)
    print(f"part 1: {res}")
    assert res == "c6697b55"


def solve_2(x):
    res = sol2(x)
    print(f"part 2: {res}")
    assert res == "8c35d1ab"


if __name__ == "__main__":
    inp = "ffykfhsq"
    sys.exit(
        aoc_runner.aoc_runner(
            samples,
            solve_1,
            solve_2,
            inp,
        )
    )
