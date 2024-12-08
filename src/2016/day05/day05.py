import hashlib


def solve(key: str, zeroes: int = 5) -> str:
    out: str = ""
    for i in range(int(1e9)):
        test = hashlib.md5(f"{key}{i}".encode()).hexdigest()
        if test[:zeroes] == "0" * zeroes:
            out += str(test[5])
            if len(out) >= 8:
                return out
    return out


def solve2(key: str, zeroes: int = 5) -> str:
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


def main():
    print(f"abc: {solve('abc')} expects: 18f47a30")
    print(f"abc: {solve2('abc')} expects: 05ace8e3")
    print(solve("ffykfhsq"))
    print(solve2("ffykfhsq"))


if __name__ == "__main__":
    main()
