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


if __name__ == "__main__":
    inp = "ffykfhsq"
    sys.exit(
        aoc_runner.aoc_runner(
            samples,
            lambda x: print(f"problem 1: {sol1(x)}"),
            lambda x: print(f"problem 2: {sol2(x)}"),
            inp,
        )
    )
