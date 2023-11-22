# TODO: Break out input into input file
import hashlib


def solve(key: str, zeroes: int) -> int:
    for i in range(int(1e9)):
        test = hashlib.md5(f"{key}{i}".encode()).hexdigest()
        if test[:zeroes] == "0" * zeroes:
            return i
    return 0


def main() -> None:
    print(f"abcdef: {solve('abcdef', 5)} expects: 609043")
    print(f"abcdef: {solve('pqrstuv', 5)} expects: 1048970")
    print(solve("iwrupvqb", 5))
    print(solve("iwrupvqb", 6))


if __name__ == "__main__":
    main()
