def calc_checksum(num) -> None:
    num = str(num)

    l = len(num)
    output = 0
    for i, dig in enumerate(num):
        if dig == num[(i + 1) % l]:
            output += int(dig)
    return output


def main() -> None:
    test_list = [1122, 1111, 1234, 91212129]
    print(calc_checksum(test_list))
    filename = "day01.input"
    with open(filename, "r", encoding="utf8") as f:
        num = f.read()
    print(calc_checksum(num))


if __name__ == "__main__":
    main()
