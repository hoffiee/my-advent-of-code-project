def calc_checksum(num) -> None:
    try:
        num = str(num)
    except:
        pass

    l = len(num)
    output = 0
    for i, dig in enumerate(num):
        if dig == num[(i + 1) % l]:
            output += int(dig)
    return output


def main() -> None:
    test_list = [1122, 1111, 1234, 91212129]
    print(calc_checksum(test_list))
    filename = "2017_day01.input"
    with open(filename, "r") as f:
        num = f.read()
    print(calc_checksum(num))


if __name__ == "__main__":
    main()
